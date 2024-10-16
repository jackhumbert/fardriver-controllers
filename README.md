# Nanjing Fardriver Controllers

## Serial Protocol

You can interact with Fardriver controllers on a computer using the serial port (2x2 connector) with a RS232-USB adapter, provided you don't connect the 5V line (so only TX, RX & GND are connected), and your adapter uses 3.3V logic. [Termite](https://www.compuphase.com/software_termite.htm) works well to interact with the controller, as long as you have enabled the `Hex View` plugin under settings.

Little-endian, unless otherwise specified.

### Receiving messages

Status messages sent by the controller are usually 16 bytes in length. They rotate through nearly all of the internal memory addresses, with more important sections being repeated throughout, every 3-4 normal messages. If you plugin your controller to your computer after initializing it via a Bluetooth adapter, you should see these. Otherwise, you'll need to send some of the commands mentioned later on.

```cpp
struct {
    // B0
    uint8_t magic = 0xAA; // 170

    // B1
    uint8_t id : 6; // less than 0x37 when receiving updates
    uint8_t flags : 2; // generally set to 2 when receiving

    // B2-13
    uint8_t data[12];

    // B14-15
    uint8_t crc[2];
};
```

The `crc` values are calculated with two tables, available in [fardriver.hpp](/fardriver.hpp), where `length` is the length of the entire message (`16` in the above scenario):

```cpp
void ComputeCRC(uint8_t * data, uint16_t length) {
    uint8_t a = 0x3C; // 60
    uint8_t b = 0x7F; // 127
    uint8_t pos;
    for (pos = 0; pos < length - 2; ++pos) {
        auto i = a ^ data[pos];
        a = b ^ crcTableHi[i];
        b = crcTableLo[i];
    }
    data[length - 2] = a;
    data[length - 1] = b;
}
```

If `id` is less than `0x37` (`55`), it can be used to lookup the address of the data:

```cpp
const uint8_t flash_read_addr[55] = {
  0xE2, 0xE8, 0xEE, 0x00, 0x06, 0x0C, 0x12, 
  0xE2, 0xE8, 0xEE, 0x18, 0x1E, 0x24, 0x2A, 
  0xE2, 0xE8, 0xEE, 0x30, 0x5D, 0x63, 0x69, 
  0xE2, 0xE8, 0xEE, 0x7C, 0x82, 0x88, 0x8E, 
  0xE2, 0xE8, 0xEE, 0x94, 0x9A, 0xA0, 0xA6, 
  0xE2, 0xE8, 0xEE, 0xAC, 0xB2, 0xB8, 0xBE, 
  0xE2, 0xE8, 0xEE, 0xC4, 0xCA, 0xD0,
  0xE2, 0xE8, 0xEE, 0xD6, 0xDC, 0xF4, 0xFA
};
```

Each address stores 16bits. The addresses range from `0x00` to `0xFA`, and the data structs can be referenced in [the `FardriverData` struct in fardriver.hpp](/fardriver.hpp).

When `id` is equal to `0x37` (`55`), a data gathering format is used (unknown at the moment).

You can use [010 Editor](https://www.sweetscape.com/010editor/) with [fardriver.bt](/fardriver.bt) and a dump of the received data to interactively explore the structures (there are some small differences between the .hpp & .bt structs and names).

### Writing addresses directly

This is the "new" way the apps interact with the controller, and allows for variable packet sizes, but most that are sent are 8 bytes total.

```cpp
struct {
    // B0
    uint8_t magic = 0xAA; // 170

    // B1
    uint8_t compute_length : 6; // length of entire message minus 2 for crc
    uint8_t flags : 2; // set to 1 for writing addresses

    // B2-3
    uint8_t addr;
    uint8_t addr_confirm;

    // B4...
    uint8_t data[compute_length - 4]; // usually 2 bytes

    // Last two bytes
    uint8_t crc[2];
};
```

The CRC is calculated and assigned to the last two bytes using the `ComputeCRC` method mentioned earlier, passing in `8` for the length, instead of `16`. 

System commands can be sent by writing `0x88 XX` to the address `0xA0`:

* `0x01` enters non-following status
* `0x02` starts self-learning/balance?
* `0x03` stops balancing
* `0x04` gets CAN parameters?
* `0x05` related to `0x0F`, resets
* `0x06` starts data gathering
* `0x07` stops something?
* `0x08` unknown, phase_active?
* `0x0F` same as `0x05` if Version0 == 73 or filename contains `ISOLATE_`

### Sending commands

These are less commonly used, mainly with "old" configs. Commands are sent in 8 byte packets with the following format:

```cpp
struct {
    uint8_t magic = 0xAA; // 170
    uint8_t command;
    uint8_t command_comp; // ~command
    uint8_t sub_command;
    uint8_t value_1;
    uint8_t value_2;
    uint8_t crc; // magic + command + command_comp + sub_command + value_1 + value_2
    uint8_t crc_comp; // ~crc
};
```

CRCs are computed differently than the other messages

Some valid `command` values I've seen - children to each list item are `sub_command` values:

* `0x01` ??
* `0x02` ?? sets some variable
* `0x03`
* `0x04` balance, BMS, shutdown
    * `0x02` system shutdown, non-following status
    * `0x6F` related to starting/stopping balance and MOS charging/discharging
* `0x05` sent after updating date & time
    * `0x01 0x5F 0x5F` may get CAN params
* `0x06` gets:
    * `0x41 AT+BAUD=19200`
* `0x07` starts the gathering of data and returns 300 frames of recent data logging?
* `0x08` Starts USART3 (21/22) maybe? with 19200 baud, with other stuff
* `0x09` sets the CAN number
* `0x0A` gets name? `AT+NAME=CONTROLDM` + something - 02 does same, sets some variable
    * `0x41 AT+NAME=CONTROLDM <unk1> <unk2> <unk3>`
* `0x0B`
* `0x0C` ??
* `0x0D`
* `0x0E` ??
* `0x0F`
* `0x10` gets controller TUUID? `AT+TUUID=FFEC` + something - 04, 0C, 06, 0E do the same
    * `0x41 AT+TUUID=FFEC`
* `0x11` may be used to update params
* `0x12` updates params with 0x14 something
* `0x13` interacts with the login/binding system, can set password, phone number
    * `0x07` seems to be related to the login/status update system, any values seem to start status updates for a little while
    * `0x08` seems to be sent on serial connection close
    * `0x10`-`0x13` are related to updating the password
    * `0x14`-`0x24` are related to updating the phone number
* `0x14` sets the date
* `0x15` sets the time
* `0x17`

### Other messages

* `xx 0xFF 0x01 0x01 <data[0x180]>`
* `xx 0xFE 0x01 0x01 <data[0x138ish]>`
* `xx 0xFD 0x01 0x01 <password[30]>`

### CAN messages

* `0xCFE55B0` 6 & 7 set MaxLineCurr
* `0xCFE55B1` 6 & 7 set additional MaxLineCurr (adds)
* `0xCFF55B0` sets battery cap

### Updating Firmware

When loading the firmware .bin file, a crc array is created with the bytes at 0x3E000, populated in the array from 4 to 124.

For the 32303, the first 0x2000 (4 packets) aren't important, so they're skipped.

During "Detect Controller", where something (at +0x448dc, based on file size/format?) is 0x7e2f / 32303: (GD32F303?)

* `0x55 0xaa 0x33 0x30 0x33 0x3c 0xfd 0xfe`

0x7d67 / 32103: (GD32F103?)

* `0x55 0xaa 0x11 0x12 0x13 0x00 0xfd 0xfe`

0x3778 / 14200: ??

* `0x55 0xaa 0x65 0x8b 0xcf 0x31 0x48 0xf3`

0x0115 / 277: ??

* `0x55 0xaa 0x31 0x32 0x33 0x00 0xfd 0xfe`

else: ??

* `0x55 0xaa 0x01 0x02 0x03 0x00 0xfd 0xfe`

mobile app also handles 32071

This may be sent first, or this follows after a 50 loop delay, or if "NewApp", SysCmd 0x5 or 0xF (when filename contains "ISOLATE_", or hardware version is `I`):

* `0xAA 0x04 0xFB 0x01 0x55 0x55 0x54 0xAB`

* SysCmd 0x5: `0xAA 0xC6 0xA0 0xA0 0x88 0x05 0x04 0xCC`
* SysCmd 0xF: `0xAA 0xC6 0xA0 0xA0 0x88 0x0F 0x84 0xCB`

followed by `0xAA 0x04 0xFB 0x01 0x26 0x26 0xF6 0x09` (only on the mobile app apparently, after 10ms)

then packets are sent, tracking an index. If a variable is 1, it starts at index `54`, 2: `58`, and otherwise starts at `0`.

controller should send some sort of response with the crc of the packet sent:

* `0xAA 0x1F <index or error> <index> <crc_packet[8]> <crc_msg[2]>`

with error codes `0x7C`, `0x7D` or `0x7E`. index will be `0x1` for first packet (packet_crc should be mapped to crc_table[4])

if 32303:

if packet_crc matches && (not at the end or func == 0), send this confirming the packet_crc:

* `0x5a 0xbb <index + 1> 0x72 0x73 0x74 0x75 0x76`

if the second half of the packet_crc doesn't match, this is sent, and index isn't incremented:

* `0x5a 0xbb <index> 0x72 0x73 0x74 0x75 0x76`

otherwise, packet info, total length 0x807, separated into 0x403 & 0x404 packages:

* `0x5a 0xa5 <index> <data[2048]> <crc[4]>`

crc is calculated by:

```
uint32_t crc = 0xFFFFFFFF;
crc = crc32[crc & 0xFF ^ index] ^ crc >> 8;
for (i=0..2048) {
    crc = crc32[crc & 0xFF ^ data[i]] ^ crc >> 8;
}
crc = ~crc;
```

crc32 is created by:

```
for (i=0..256) {
    uint num = i;
    for (0..8) {
        if (((int) num & 1) != 0)
            num = num >> 1 ^ 0xedb88320;
        else
            num >>= 1;
    }
    this.crc32[i] = num;
}
```

mobile app does 2055 (0x807) length packets:

```
for (;i<102) {
    send 20;
    sleep(10);
}
send 15;
sleep(10);
```

last packet is all the crcs that start at 0x3E000 (without the 0xaa 0x55, which is added manually), handled differently:

* `0x5a 0xa5 <data[484]> 0xaa 0x55 0xFF[2048-486] <crc[4]>`

### Other messages sent from controller

* `xx xx xx xx xx xx 0x01 <temp >> 3>`
* `0x55 0xAA 0x00 <var> 0x00 0x0D 0x6F 0x76 0x31 0x33 0x64 0x65 0x77 0x77 <hardware> <softwareMajor> 0x2E <softwareMinor + '0'>`

when something is `0xD`, full model number is received with extension code `X`:

* `xx xx xx xx xx 0x16 0x67 0x03 0x00 0x12 <model_number>`


## Hardware Info:

### .BIN files

* 32303:
    * uses crc_filetable
    * takes .bin files larger than 131072
    * crc starts at 253952
* 32071: 
    * uses crc_filetable
    * takes .bin files less than or equal to 131072
    * crc starts at 126976
* 32101:
    * uses crc_total
    * filename contains BMS
    * crc starts at 60410
* 32103:
    * uses crc_total
    * filename doesn't contain BMS
    * crc starts at 64506

### Hardware `H`

Pins definitions:

* `1` ADC0 > 0x7FF, A2? related to A10 somewhere
* `4` A15
* `5` C13
* `6` C14
* `7` C15

* `0`   NC                   Normally Closed
* `1`   PIN24        ADC       
* `2`   PIN15            P4  CAN RX, High speed
* `3`   PIN5             P5  CAN TX, Low speed
* `4`   PIN17        A15     Used by encoder units
* `5`   PIN14        C13 P17
* `6`   PIN3         C14 P7
* `7`   PIN8         C15 P8  Reverse
* `8`   PB4             
* `9`   PINInvalid1             
* `10`  PIN2                
* `11`  PIN18        D0      Not available in YJCAN
* `12`  PIN9                 Not available in YJCAN
* `13`  PD1             
* `14`  PINInvalid2             
* `15`  PINInvalid3             


A14? Out_PP
B11 used by SpecialCode X
B10 uses OneLine, ReverseOneLine affects via B2?
A12 is serial RTS
B6,7,8 used by Hall?

Mode_AF_PP:

* A8
* A9
* A10
* B13
* B14
* B15

Another setup:
* A8, A9, A10: Out_PP
* B13, B14, B15: Out_PP
* A2, A14: Out_PP
* SpecialFrame == 14
    * D1: IPU
* else
    * D1: Out_PP
* If no inputs using pin 11:
    * D0: Out_PP
* else
    * D0: IPU
* B0, B1: AIN
* if (sensorType < 4)
    * B3, B4, B5, B6, B7, B8, B12: IN_FLOATING
* else if (sensorType < 8)
    * B3, B4, B6, B7, B8, B12: IN_FLOATING
* else
    * B2, B4, B7, B12: IN_FLOATING
    * B3, B5: AF_99
    * B6: Out_PP
* SpecialCodes A-G:
    * B9, B2: Out_PP
* else 
    * B2: Out_PP
* B2, B10: AF_PP
* B11: IPU
* A15: IN_FLOATING
* C13: IPU
* C14, C15: IN_FLOATING
* if (SpecialCode == 'Y')
    * A11: Out_PP
* else
    * A11: IPU
* A12: IPU

RXD:
* `0` B10: AF_PP
* `1` B10: Out_OD
* `2` B10: Out_PP
* `3` B10: AF_PP

Also makes A12 Out_PP or AF_PP

Possible Interrupts (AntiTheft checked on started I think):

* A15
* C13
* C14
* C15

SpeedLimitPin:
* 4 A15
* 5 C13
* 

SwitchVolPin:


### Wiring

#### ND84530_24_ABH64

GigaDevice GD32F303CCT6A

##### 30 Pin plug:

Pin | Color        | FD Name | Description
---|---|---|---|
 1  | Brown/Red    | U       | Anti-theft phase wire
 2  | Brown/Green  | BW5V    | Serial power (5V)
 3  | Red/White    | ACC+    | Throttle power (5V)
 4  | Black        | GND     | Throttle GND
 5  | White        | TEMP    | Motor temperature sensor
 6  | Red          | HALL+   | 12V for motor
 7  | Blue         | HC      | Motor C sensor
 8  | Green        | HB      | Motor B sensor
 9  | Yellow       | HA      | Motor A sensor
10  | NC           | -       | -

11  | Orange       | KEY     | Ignition that accepts battery plus (72V, etc)
12  | Brown/Blue   | TXD     | Serial TX (3.3V)
13  | Black        | GND     | Reverse/Serial GND
14  | Green/White  | SV      | Throttle signal (5V)
15  | Black        | GND     | Anti-theft GND
16  | Black        | GND     | Motor GND
17  | Red/Blue     | XH      | Cruise
18  | Black        | GND     | Brake/Speed selection GND
19  | Grey         | BH      | Brake, pull-up to enable (12V)
20  | Yellow/Green | BL      | Brake, pull-down to enable (3.3V)

21  | Orange       | KEY     | Ignition for Anti-theft
22  | Pink         | 60VC    | Anti-theft power (+72V)
23  | Red/Black    | RXD     | Serial RX (3.3V)
24  | Yellow/White | SDH     | High speed, pull-down to enable (3.3V)
25  | Blue/White   | SDL     | Low speed, pull-down to enable (3.3V)
26  | Brown        | BOOST   | Boost, pull-down to enable
27  | Black/white  | FW/FD   | Anti-theft signal, pull-down to enable
28  | Brown/white  | RE      | Reverse, pull-down to enable
29  | Light Blue   | SPD     | Speed pulse/one wire (12V)
30  | Purple       | SPA     | Speedometer PWM (72V)

##### Daughter board

LEFT:

Pin| Daughterboard | Mainboard
---|---|---|
1  | 20K to U                                   | 
2  | Key, 72V in                                | 
3  | Key, 72V in                                | 
4  | 7.6K to GND, 10.4K to 12V, 2.7k to H*      | 14V
5  | 60VC, 72V out                              | 
6  | BM5V, 5V out                               | 
7  | RXD, 3.3V                                  | 
8  | TXD, 3.3V                                  | 
9  | FW/FD, 3.3V                                | 
10 | GND                                        | 1k to 3.3V

CENTER:

Pin| Daughterboard | Mainboard
---|---|---|
1  | 4K to BW5V                                 | 6.5k to 5V
2  | 15K to BW5V, 7.1K to GND                   | 
3  | GND, 8K to BW5V                            | 
4  | 10K to HALL+, 7.1K to GND, 13.3K to SPD    | 
5  | NC, Speaker maybe?                         | 
6  | 10K to HALL+                               | 
7  | BH, 12V in                                 | 
8  | NC                                         | 
9  | BH, 12V in                                 | 
10 | BL, 3.3V                                   | 

RIGHT:

Pin| Daughterboard | Mainboard
---|---|---|
1  | TEMP                                       | 
2  | SPA                                        | 
3  | 12K to GND, 12R to SPD                     | 
4  | SV, 5V in,5K to GND                      | 
5  | NC                                         | 
6  | SERIAL:1                                   | 
7  | RE                                         | 
8  | 7K to GND, 5k to 5V                        | 
9  | GND, 3k to 12V, 8k to 5V                   | 
10 | 10k to 12V, 7k to GND                      | 

SERIAL header in upper right:

Pin| Description
---|---|
1  | RIGHT:6
2  | GND, 8k to BM5V
3  | RXD
4  | TXD