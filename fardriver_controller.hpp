#include "fardriver.hpp"
#include "fardriver_crc.hpp"
#include <string.h>

struct FardriverSerial {
    uint32_t (*write)(const uint8_t * data, uint32_t length);
    uint32_t (*read)(uint8_t * data, uint32_t length);
    uint32_t (*available)(void);
};

struct FardriverController {
    FardriverController(FardriverSerial * _serial) : serial(_serial) {

    }

    // used when App.NewVersion
    void WriteAddr(uint8_t * data, uint8_t addr, uint16_t length) {
        length += 4;
        data[0] = 0xAA; // 170
        if (length == 0x184) {
            // CAN Data, 0x180 bytes long
            // addr is 0
            data[1] = 0xFF; 
        } else if (length == 0x13C) {
            // All params?, 0x138 bytes long
            // addr is 0 or 1
            data[1] = 0xFE;
        } else if (length == 0x8C) {
            // idk, not used in mobile
            data[1] = 0xFD;
        } else {
            // Normal flash memory
            data[1] = 0xC0 + length; 
        }
        data[2] = addr;
        data[3] = addr;
        uint8_t a = 0x3C; // 60
        uint8_t b = 0x7F; // 127
        for (uint8_t pos = 0; pos < length; ++pos) {
            auto crc_i = a ^ data[pos];
            a = b ^ FardriverMessage::crcTableHi[crc_i];
            b = FardriverMessage::crcTableLo[crc_i];
        }
        data[length] = a;
        data[length + 1] = b;
        serial->write(data, length + 2);
    }

    void UpdateWord(uint8_t addr, uint8_t first, uint8_t second) {
        uint8_t data[8];
        data[4] = first;
        data[5] = second;
        WriteAddr(data, addr, 2);
    }

    // used when !App.NewVersion
    void SendRS323Data(uint8_t command, uint8_t sub_command, uint8_t value_1, uint8_t value_2) {
        uint8_t data[8];
        data[0] = 0xAA; // 170
        data[1] = command;
        data[2] = ~command;
        data[3] = sub_command;
        data[4] = value_1;
        data[5] = value_2;
        data[6] = data[0] + data[1] + data[2] + data[3] + data[4] + data[5];
        data[7] = ~data[6];
        serial->write(data, 8);
    }

    void WriteSysCmd(uint8_t command) {
        uint8_t data[8];
        data[4] = 0x88;
        data[5] = command;
        WriteAddr(data, 0xA0, 2);
    }

    // sent immediately after opening port
    void Open(void) {
       SendRS323Data(0x13, 0x07, 0x01, 0xF1);
    }

#ifndef __GNUC__
    // saves "cflash"
    void SaveCANParameters(FardriverData * fd) {
        uint8_t data[0x180 + 4];
        uint8_t * pos = data + 4;
        uint16_t size = (0x180) * 2;
        memcpy(pos, fd->GetAddr(0x100), size);
        WriteAddr(data, 0x00, 0x180);
    }

    // saves "wflash"
    void SaveParameters(FardriverData * fd) {
        uint8_t data[0x138 + 4];
        uint8_t * pos = data + 4;
        uint16_t size = (0x36) * 2;
        memcpy(pos, fd->GetAddr(0x00), size);
        pos += size;
        size = (0x6F - 0x63) * 2;
        memcpy(pos, fd->GetAddr(0x63), size);
        pos += size;
        size = (0xD6 - 0x7C) * 2;
        memcpy(pos, fd->GetAddr(0x7C), size);
        pos += size;
        WriteAddr(data, 0x01, 0x138);
    }
#endif

    void SendDetectPacket(void) {
        uint8_t message[8];
        message[0] = 0x5A;
        message[1] = 0xAA;
        message[2] = 0x33;
        message[3] = 0x03;
        message[4] = 0x33;
        message[5] = 0x3C;
        message[6] = 0xFD;
        message[7] = 0xFE;
        serial->write(message, 8);
    }

    void SendACK(uint8_t index) {
        uint8_t message[8];
        message[0] = 0x5A;
        message[1] = 0xBB;
        message[2] = index;
        message[3] = 0x72;
        message[4] = 0x73;
        message[5] = 0x74;
        message[6] = 0x75;
        message[7] = 0x76;
        serial->write(message, 8);
    }

    // can be used for regular packets & crc packet
    bool SendPacket(uint8_t index, const uint8_t * data, uint32_t length) {
        if (length > 2048)
            return false;
        uint8_t message[2048 + 3 + 4];
        message[0] = 0x5A;
        message[1] = 0xA5;
        message[2] = index;
        printf("  Copying packet data\n");
        memcpy(&message[3], data, length);
        if (2048 - length > 0) {
            memset(&message[3 + length], 0xFF, 2048 - length);
        }
        crc.Reset();
        crc.Add(&message[2], 1 + 2048);
        crc.Assign(&message[3 + 2048]);
        printf("  Writing message\n");
        serial->write(message, 3 + 2048 + 4);
        return true;
    }

    bool VerifyCRCMessage(uint32_t index, const uint8_t * file_crc) {
        // wait for 0xaa 0x1f <error> <index> <packet_crc[8]> <crc[2]>
        // no error if error < 0x7E && error == index
        while(serial->available() < 16);
        uint8_t message[16] = { 0 };
        serial->read(message, 16);
        if (message[0] != 0xAA)
            return false;
        if (message[1] != 0x1F)
            return false;
        if (message[2] != message[3])
            return false;
        uint8_t * read_crc = &message[3];
        for (uint8_t index = 0; index < 8; index++) {
            if (file_crc[index] != read_crc[index]) {
                return false;
            }
        }
        return true;
    }

    CRC crc;
    FardriverSerial * serial;
};