#include <cstdint>

struct CRC {
    CRC() {
        for (uint8_t i = 0; i < 256; i++) {
            uint32_t num = i;
            for (uint8_t j = 0; j < 8; j++) {
                if (((int)(num) & 1) != 0) {
                    num = (num >> 1) ^ 0xEDB88320;
                } else {
                    num >>= 1;
                }
            }
            crc32[i] = num;
        }
    }

    void Reset() {
        crc = 0xFFFFFFFF;
    }

    void Add(uint8_t * data, uint32_t length) {
        for (uint32_t i = 0; i < length; i++) {
            crc = crc32[(crc & 0xFF) ^ data[i]] ^ (crc >> 8);
        }
    }

    void Assign(uint8_t * message_end) {
        uint32_t crc_comp = ~crc;
        message_end[0] = crc_comp & 0xFF;
        message_end[1] = (crc_comp >> 8) & 0xFF;
        message_end[2] = (crc_comp >> 16) & 0xFF;
        message_end[3] = (crc_comp >> 24) & 0xFF;
    }

    uint32_t crc = 0xFFFFFFFF;
    uint32_t crc32[256];
};