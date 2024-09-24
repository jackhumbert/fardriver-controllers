#include <cstdint>

#pragma pack(push, 1)
typedef struct {
    uint32_t byte_0 : 8;
    uint32_t byte_1 : 8;
    uint32_t byte_2 : 8;

    float value(void) {
        return 1.953125 * sqrt(byte_0 << 16 + byte_1 << 8 + byte_2);
    }
} big_end_24b;
#pragma pack(pop)

#pragma pack(push, 1)
struct FardriverMessage {
    static constexpr const uint8_t crcTableLo[256] = {
        0, 192, 193, 1, 195, 3, 2, 194, 198, 6, 7, 199, 5, 197, 196, 4, 204, 12, 13, 205, 15, 207, 206, 14, 10, 202, 203, 11, 201, 9, 8, 200, 216, 24, 25, 217, 27, 219, 218, 26, 30, 222, 223, 31, 221, 29, 28, 220, 20, 212, 213, 21, 215, 23, 22, 214, 210, 18, 19, 211, 17, 209, 208, 16, 240, 48, 49, 241, 51, 243, 242, 50, 54, 246, 247, 55, 245, 53, 52, 244, 60, 252, 253, 61, 255, 63, 62, 254, 250, 58, 59, 251, 57, 249, 248, 56, 40, 232, 233, 41, 235, 43, 42, 234, 238, 46, 47, 239, 45, 237, 236, 44, 228, 36, 37, 229, 39, 231, 230, 38, 34, 226, 227, 35, 225, 33, 32, 224, 160, 96, 97, 161, 99, 163, 162, 98, 102, 166, 167, 103, 165, 101, 100, 164, 108, 172, 173, 109, 175, 111, 110, 174, 170, 106, 107, 171, 105, 169, 168, 104, 120, 184, 185, 121, 187, 123, 122, 186, 190, 126, 127, 191, 125, 189, 188, 124, 180, 116, 117, 181, 119, 183, 182, 118, 114, 178, 179, 115, 177, 113, 112, 176, 80, 144, 145, 81, 147, 83, 82, 146, 150, 86, 87, 151, 85, 149, 148, 84, 156, 92, 93, 157, 95, 159, 158, 94, 90, 154, 155, 91, 153, 89, 88, 152, 136, 72, 73, 137, 75, 139, 138, 74, 78, 142, 143, 79, 141, 77, 76, 140, 68, 132, 133, 69, 135, 71, 70, 134, 130, 66, 67, 131, 65, 129, 128, 64
    };
    static constexpr const uint8_t crcTableHi[256] = {
        0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64, 0, 193, 129, 64, 1, 192, 128, 65, 0, 193, 129, 64, 1, 192, 128, 65, 1, 192, 128, 65, 0, 193, 129, 64
    };

    uint8_t * GetRaw() {
        return (uint8_t *)(this);
    }

    bool VerifyCRC() {
        uint8_t a = 0x3C; // 60
        uint8_t b = 0x7F; // 127
        uint8_t index;
        for (index = 0; index < 14; ++index) {
            auto crc_i = a ^ this->GetRaw()[index];
            a = b ^ this->crcTableHi[crc_i];
            b = this->crcTableLo[crc_i];
        }
        return this->crc[0] == a && this->crc[1] == b;
    }

    uint8_t start = 0xAA;
    struct Header {
        uint8_t id : 6;
        uint8_t flag : 2;
    } header;
    uint8_t data[12];
    uint8_t crc[2];

};
#pragma pack(pop)

constexpr const uint8_t FardriverMessage::crcTableLo[256];
constexpr const uint8_t FardriverMessage::crcTableHi[256];

#pragma pack(push, 1)
struct FardriverData {

    uint8_t * GetAddr(uint16_t addr) {
        return (uint8_t*)this + (addr << 1);
    }

    uint16_t GetWord(uint16_t addr) {
        return (uint16_t*)this + addr;
    }

    // used when App.NewVersion
    void WriteAddr(uint8_t * data, uint8_t addr, uint8_t length) {
        length += 4;
        data[0] = 0xAA; // 170
        data[1] = 0xC0 + length; // 192
        data[2] = addr;
        data[3] = addr;
        uint8_t a = 0x3C; // 60
        uint8_t b = 0x7F; // 127
        uint8_t index;
        for (pos = 0; pos < length; ++pos) {
            auto crc_i = a ^ data[pos];
            a = b ^ FardriverMessage::crcTableHi[crc_i];
            b = FardriverMessage::crcTableLo[crc_i];
        }
        data[length] = a;
        data[length + 1] = b;
    // send data
    }

    void UpdateWord(uint8_t addr, uint8_t first, uint8_t second) {
        uint8_t data[8];
        data[4] = first;
        data[5] = second;
        this->WriteAddr(data, addr, 2);
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
    // send data
    }

// 0x00
    int16_t VolCoeff;
    int16_t Voltage2Coeff;
    int16_t PhaseACoeff;
    int16_t LineCoeff;
    int16_t PhaseCCoeff;
    int16_t SaveNum;

// 0x06
    // 2
    uint8_t Arg2 : 1;
    enum class EAntiTheftPulse {
        Invalid = 0,
        Type1 = 1,
        Type2 = 2,
        Type3 = 3
    } AntiTheftPulse : 2; // PulseFD
    uint8_t unk02a : 1;
    uint8_t Protocol485 : 4;

    uint8_t MorseCode;
    uint8_t SpeedKI;
    uint8_t SppedKP;
    uint8_t ThrottleLow; // / 20
    uint8_t ThrottleHigh; // / 20

    // 8-9
    int16_t FAIF;

    // 10-11
    int16_t CurveTime;
    
    // 12 cfg11l
    enum class EBrakeConfig {
        StopWhenGround = 0,
        StopWhenFloat = 1,
        P_StopGnd = 2,
        P_StopFloat = 3,
        Disabled = 4
    } BrakeConfig : 4;
    enum class ETempSensor {
        None = 0,
        PTC = 1,
        NTC230K = 2,
        KTY84_130 = 3,
        CACU = 4,
        KTY83_122 = 5,
        NTC10K = 6,
        NTC100K = 7
    } TempSensor : 3; // NTC_PTC, Send(0x11, 0x01)
    uint8_t PhaseExchange : 1;

    // 13 cfg11h
    uint8_t SlowDown : 3;
    uint8_t PC13Config : 1; // RaceResponse
    uint8_t CurrAntiTheft : 1; // CurrFD Valid = 1
    enum class EParkConfig {
        ReversePark = 0,
        SwitchPark = 1,
        SlowDownPark = 2,
        Disabled = 3
    } ParkConfig : 2;
    uint8_t Direction : 1; // Send(0x12, 0x07)

// 0x0C
    int16_t PhaseOffset; // / 10.0, Send(0x0A, 0x07)
    int16_t ZeroBattCoeff;
    int16_t FullBattCoeff;
    uint8_t StartKI;
    uint8_t MidKI;
    uint8_t MaxKI;
    uint8_t StartKP;
    uint8_t MidKP;
    uint8_t MaxKP;

// 0x12
    int16_t LD;
    uint16_t AlarmDelay;
    uint8_t PolePairs; // Send(0x12, 0x01)
    uint8_t unk14b; // alway_s sent 0x59?
    uint16_t MaxSpeed; // Send(0x12, 0x02)
    uint16_t RatedPower; // Send(0x12, 0x03)
    uint16_t RatedVoltage; // / 10, Send(0x12, 0x04)

// 0x18
    // 2-3
    uint16_t RatedSpeed; // Send(0x12, 0x05)

    // 4-5
    uint16_t MaxLineCurr; // / 4, Send(0x12, 0x1B)

    // 6 cfg26l
    enum class EFollowConfig {
        FollowEnabled = 0,
        Disabled = 1,
        EABSWhenBreakValid = 2,
        EABSWhenReleaseThrottle = 3
    } FollowConfig : 2;
    enum class EThrottleResponse {
        Line = 0,
        Sport = 1,
        ECO = 2
    } ThrottleResponse : 2; // ECOConfig
    uint8_t WeakA : 2;
    enum class ERXD {
        AF = 0,
        OD = 1,
        PP = 2
    } RXD : 2;

    // 7 cfg26h
    uint8_t SpeedPulse : 5;
    enum class EGearConfig {
        DefaultN = 0
        DefaultD = 1,
        Disabled = 2,
        DefaultAntiTheft = 3, // DefaultLow in old
        DefaultButtonHigh = 4,
        DefaultButtonMiddle = 5
    } GearConfig : 3;

    // 8-9
    uint16_t LQ;

    // 10-11
    uint16_t BattRatedCap;

    // 12-13
    uint16_t IntRes; // Send(0x0F, 0x08)

// 0x1E
    uint16_t FwReRatio;
    uint16_t LowVolProtect; // / 10
    // local float LowVolRestore = LowVolProtect / 10.0 + 2.0;
    char CustomCode[2];

    // 8
    // uint16_t RelayDelay; // ms
    uint8_t BCState : 1;
    uint8_t SeatEnable : 1; // Zuotong
    uint8_t PEnable : 1; // PGear
    uint8_t AutoBackPEnable : 1; // AutoBackPStat
    uint8_t CruiseEnable : 1; // XHStat
    uint8_t EABSEnable : 1;
    uint8_t PushEnable : 1; // TuixingS
    uint8_t ForseAntiTheft : 1;

    // 9
    uint8_t OverSpeedAlarm : 1;
    uint8_t BrakeStillPark : 1; // ParkDisableBrake
    uint8_t RememberGear : 1; // GearRememberS
    uint8_t unk21c : 3;
    uint8_t BackEnable : 1; // REGear
    uint8_t RelayDelay1S : 1;

    uint8_t ModelYear; // + 2000
    uint8_t ModelMonth;
    uint8_t ModelDay;
    uint8_t TimeHour;

// 0x24
    uint8_t TimeMin;
    uint8_t TimeSecond;
    uint16_t HighVolProtect; // / 10
    uint16_t CustomMaxLineCurr; // / 4
    uint16_t CustomMaxPhaseCurr; // / 4
    uint16_t BackSpeed; // Send(0x11, 0x03)
    uint16_t LowSpeed; // Send(0x11, 0x02)

// 0x2A
    uint16_t MidSpeed;
    uint16_t Max_Dec;
    uint8_t FreeThrottle; 
    uint8_t unk2Cb;
    uint16_t MaxPhaseCurr; // / 4, Send(0x12, 0x1A)
    uint16_t SpeedAnalog;
    uint16_t Max_Acc;

// 0x30
    uint16_t StopBackCurr; // Send(0x12, 0x18)
    uint16_t MaxBackCurr; // Send(0x12, 0x19)
    // (all * 100) / 128.0 + 0.5
    uint8_t LowSpeedLineCurr;
    uint8_t MidSpeedLineCurr;
    uint8_t LowSpeedPhaseCurr;
    uint8_t MidSppedPhaseCurr;
    uint16_t BlockTime;
    uint16_t SpdPulseNum;

    uint16_t unk36[6];
    uint16_t unk3A[6];
    uint16_t unk42[6];
    uint16_t unk48[6];
    uint16_t unk4E[6];
    uint16_t unk54[6];
    uint16_t unk5A[3];

// 0x5D
    uint16_t unk5D;
    uint16_t unk5E;
    uint16_t unk5F; 
    uint16_t unk60;
    uint16_t unk61;
    uint16_t unk62;
    
// 0x63
    uint16_t MaxLineCurr2;
    uint16_t MaxPhaseCurr2; // 0x64
    uint8_t MotorDia;  // 65
    uint8_t unk65b;
    uint16_t TempCoeff; // 66
    uint16_t paracnt_0; // / 10.0 67
    uint16_t paracnt_1; // 68
    // uint16_t paracnt_2; // / 4.0 69
    // uint16_t paracnt_4; // / 4.0 6A
    // uint8_t paracnt_5;
    // uint8_t unk68b;

// 0x69
    // uint16_t BstXhBcp; // BstXhBcp
    uint8_t PPin : 4; // 69
    uint8_t BCPin : 4;
    uint8_t XHPin : 4;
    uint8_t BoostPin : 4;
    // uint16_t FrWeSdhSdl; // FrWeSdhSdl
    uint8_t SDLPin : 4; // 6A
    uint8_t SDHPin : 4;
    uint8_t REPin : 4;
    uint8_t FWPin : 4;
    // uint16_t ChgFdSeatVol; // ChgFdSeatVol
    uint8_t SwitchVolPin : 4; // 6B
    uint8_t SeatPin : 4; // ZuotongPin
    uint8_t FDPin : 4;
    uint8_t CHGPin : 4;
    uint16_t LmtSpeed; // LmtSpeed 6C
    uint16_t DistanceL; // / 10 6D
    uint8_t ParaIndex; // ParaIndex 6E
    char SpecialCode;
    uint8_t unk6Fa; // 6F
    // local char ParaIndex3 = SpecialCode < '0' || SpecialCode >= 0x7F ? '_' : SpecialCode;
    // if (ParaIndex < 10) {
    //     local char ParaIndex2 = ParaIndex + 48;
    // } else if (ParaIndex < 20) {
    //     local char ParaIndex2 = ParaIndex + 48 - 10;
    // } else {
    //     local char ParaIndex2 = ParaIndex;
    // }
    uint8_t unk6Fb;
    uint16_t unk70;
    uint16_t unk71;
    uint16_t unk72;
    uint16_t unk73;
    uint16_t unk74;
    uint16_t unk75;
    uint16_t unk76;
    uint16_t unk77;
    uint16_t unk78;
    uint16_t unk79;
    uint16_t unk7A;
    uint16_t unk7B;

// 0x7C
    // 2 config_word0
    uint8_t unk7Ca : 1;
    uint8_t WeakTime : 3;
    uint8_t unk7Cb : 1;
    uint8_t QuickDown : 3;

    // 3 config_word1
    // SpeedMeterConfig has a weird configuration that looks at the 3 variables & computes them to an enum
    // 0 Pulse none
    // 1 Analog: 1 & 3
    // 2 IsolatedPulse: 1 & 2
    uint8_t SpeedMeterConfig1 : 1; // Pulse
    uint8_t SpeedMeterConfig2 : 1; // IsolatedPulse
    uint8_t FastRE : 1;
    uint8_t SpecialWeak : 1; // DeepWeak Special
    uint8_t ZeroSwitch : 1; // SpeedSwitch Valid
    uint8_t unk7Cc;
    uint8_t MOE : 1;
    uint8_t SpeedMeterConfig3 : 1; // Analog

    // 4
    uint TotalTime; // minutes, infoc0, wktime
    uint infoc1;
    uint16_t DistanceH; // this << 16 / 10, km
           
// 0x82
    uint16_t ThrottleVoltage; // * 0.01, 0x82
    uint16_t HighVolRestore; // / 10.0)>; 0x83
    uint8_t MotorTempProtect; // 0x84
    uint8_t MotorTempRestore; 
    uint8_t MosTempProtect; // 0x85
    uint8_t MosTempRestore;
    
    // 10
    uint8_t CANConfig : 6; // 0x86
    uint8_t unk86b : 2;

    uint8_t Version0; // HardVer
    uint8_t Version1; // SoftVer0
    uint8_t SoftVer; // SoftVer1

// 0x88
    uint8_t RatioMin;
    uint8_t Ratio500;
    uint8_t Ratio1000;
    uint8_t Ratio1500;
    uint8_t Ratio2000;
    uint8_t Ratio2500;
    uint8_t Ratio3000;
    uint8_t Ratio3500;
    uint8_t Ratio4000;
    uint8_t Ratio4500;
    uint8_t Ratio5000;
    uint8_t Ratio5500;

// 0x8E
    uint8_t Ratio6000;
    uint8_t Ratio6500;
    uint8_t Ratio7000;
    uint8_t Ratio7500;
    uint8_t Ratio8000;
    uint8_t Ratio8500;
    uint8_t Ratio9000;
    uint8_t RatioMax;
    int8_t nratio_0;
    int8_t nratio_1;
    int8_t nratio_2;
    int8_t nratio_3;

// 0x94
    int8_t nratio_4;
    int8_t nratio_5;
    int8_t nratio_6;
    int8_t nratio_7;
    int8_t nratio_8;
    int8_t nratio_9;
    int8_t nratio_10;
    int8_t nratio_11;
    int8_t nratio_12;
    int8_t nratio_13;
    int8_t nratio_14;
    int8_t nratio_15;

// 0x9A
    int8_t nratio_16; // 9A
    int8_t nratio_17;
    int8_t nratio_18; // 9B
    int8_t nratio_19;

    // AlarmRecord
    // 6
    uint8_t AN : 4; // 9C, cfg156l
    uint8_t AlarmRecord_1 : 1;
    uint8_t RelayOut : 1; 
    uint8_t EmptySpeed : 2;
    
    // 7
    uint8_t LM : 5; // cfg156h
    uint8_t unk9Db : 3;

    int16_t InitVol; // 9D
    int16_t Stage1Curr; // 9E
    uint8_t VolSelectRatio; // 9F
    uint8_t unk9Fb;

// 0xA0 / 0xA6
    uint8_t unkA0; // 0x88 usually?
    uint8_t SysCmd;
    // 01 non-following status
    // 02 self-learning/balance status
    // 03 self-learning/balance status
    // 05 non-ISOLATE_
    // 06 gather data
    // 0F ISOLATE_
    char ModelName[22]; 

    // AB - where password is stored?

// 0xAC
    uint16_t unkAC; // more password
    uint16_t unkAD; // phone number start1[14]
    uint16_t unkAE; // phone number start0[14] 
    uint16_t unkAF;
    uint16_t unkB0;
    uint16_t unkB1;

// 0xB2
    uint16_t unkB2;
    uint16_t unkB3;
    uint8_t OneCommSec_0;
    uint8_t OneCommSec_1;
    uint8_t OneCommSec_2; 
    uint8_t OneCommSec_3;
    uint8_t OneCommSec_4;
    uint8_t OneCommSec_5;
    uint8_t OneCommSec_6;
    uint8_t OneCommSec_7;

// 0xB8
    // 2-3 B8
    // uint16_t OneCommPos; 
    uint8_t PPosition : 4;
    uint8_t BCPosition : 4;
    uint8_t HBarPosition : 4;
    uint8_t FDPosition : 4;
    // 4-5 B9
    uint16_t unkB9;
    // 6-7 BA
    // uint16_t OneCommPS; 
    uint8_t Pulse;
    uint8_t SQH;
    // 8-9 BB
    uint16_t OnelineCurrCoeff;
    // 10-11 GPara0, BC
    uint8_t BackPTime : 5; // ReleasePTime, ReleaseToPTime, * 10, seconds
    uint8_t ReleaseToSeat : 3; // SeatDelay, seconds
    enum class ECANBaud {
        Baud250K = 0,
        Baud500K = 1,
        Baud1M = 2
    } CANBaud : 4; // CanSel
    enum class EPasswordStatus {
        PasswordProtected = 0,
        AlsoPasswordProtected = 1,
        NoPassword = 2
    } PasswordStatus : 2;
    // 12
    uint8_t Stage1Soc;
    // 13
    uint8_t Stage2Soc; // paracnt_3 : 4

// 0xBE
    enum class ELowVolWay {
        Vol2V = 0,
        Vol4V = 1,
        Vol8V = 2,
        Vol12V = 3,
        Vol16V = 4,
        Soc5Perc = 5,
        Soc6Perc = 6,
        Soc7Perc = 7,
        Soc8Perc = 8,
        Soc9Perc = 9,
        Soc10Perc = 10,
        SOP = 11,
        Other = 12
    } LowVolWay; // cfg190l, CurrLimitWay

    // 3, cfg190h
    uint8_t unkBEb : 4; 
    uint8_t AccCoeff : 4; 

    uint16_t BstTime; // / 500, seconds
    uint16_t BstRelease; // / 500, seconds
    uint16_t ParkTime; // / 500, seconds
    uint16_t InverseTime;
    uint16_t TorqueCoff;

// 0xC4
    uint16_t LearnVolLow; // LearnVol
    uint16_t LearnVolHigh; // LearnVoh
    uint16_t SlowDownRpm; // ParkDiff
    uint16_t StartIs; // IsInStart
    uint16_t ThrottleInsert; // & 0x20 TCS
    uint8_t ExitFollowSpeed;
    uint8_t ReCurrRatio;

// 0xCA
    uint8_t AngleLearn;
    uint8_t SpdLmt_sel : 4;
    uint8_t OneKey_sel : 4;
    uint8_t NoCanCnt; // CAN Detect, ms, if >= 6 then * 2 else * 500

    uint16_t GetCanDetectMS() {
        if (NoCanCnt >= 6) {
            return NoCanCnt * 2;
        } else {
            return NoCanCnt * 500;
        }
    }
    
    // uint8_t TaRlB9D0SP; 
    enum class ESPMode {    
        HighOnly = 0,
        AddDec,
        ButtonHighLow,
        ButtonLowMid,
        Button3SpeedLow,
        Button3SpeedMid,
        Button3SpeedHigh,
        Button4SpeedLow,
        Button4Speed2,
        Button4Speed3,
        Button4SpeedHigh,
        Line3Speed,
        SpecialGear,
        Invalid = 13
    };

    ESPMode SPModeConfig : 4; // HighLowSpeed, SDHDs/SDLDs
    uint8_t Temp70 : 2;
    uint8_t LongBack : 1; // Push RE
    uint8_t ThrottleLost : 1;

    uint8_t LearnThrottle;
    uint8_t SpeedLowCap;
    uint8_t MidSpeedCap;
    uint8_t SpeedLimitByCap;
    uint8_t MinSpeedCapCoeff;
    uint8_t ParkCoeff : 4;
    enum class EBattSignal {
        OneLineComm = 0,
        SerialComm = 1,
        CAN = 2,
        LithiumBattery = 3,
        LeadAcidBattery = 4,
        LFPBattery = 5
    } BattSignal : 4; // BatSel
    uint16_t ReIsinAcc;

// 0xD0
    // uint16_t OneCommHead;
    uint8_t Data0;
    uint8_t Data1;
    uint8_t BMQHALL;
    uint8_t AVGPower; // * 4, Wh/km, DataVoltage1
    uint8_t WheelRatio;
    uint8_t WheelRadius;
    uint8_t AVGSpeed; // km/h, DataVoltage4
    uint8_t WheelWidth;
    uint16_t RateRatio; // SpeedRatio
    // speed = MeasureSpeed * (0.00376991136 * (WheelRadius * 1270 + WheelWidth * WheelRatio) / RateRatio)
    // uint16_t OneCommCfg
    enum class EIdle {
        Idle0_5ms = 0,
        Idle0_9ms = 1,
        Idle1_5ms = 2,
        Idle1_9ms = 3
    } Idle : 2;
    enum class EStop {
        Stop24ms = 0,
        Stop55ms = 1,
        Stop124ms = 2,
        Stop216ms = 3
    } Stop : 2;
    uint8_t ByteOption : 4; // Byte89Sel
    uint8_t SpecialFrame; // ESQH

// 0xD6
    int16_t unkD6;

    // 4
    uint8_t Global_state1a : 1;
    uint8_t RunDir1 : 1;
    uint8_t HallPosError : 1;
    uint8_t Global_state1b : 1;
    uint8_t AutoLearn : 1;
    uint8_t NeedAutoLearn : 1;
    uint8_t Global_state1c : 1;
    uint8_t HallError : 1;
    uint8_t MotorRun : 1; // else MotorStop
    uint8_t Global_state1d : 1;
    uint8_t Global_state1e : 1;
    uint8_t PhaseLostAlarm : 1;
    uint8_t MotorCloseEnable : 1;
    uint8_t MotorRun2 : 1;
    uint8_t VoltageReport : 1;
    uint8_t AngleFix : 1;
    
    // 6
    uint8_t FlashWay : 1;
    uint8_t Global_state_2a : 1;
    uint8_t INVControl : 1;
    uint8_t WeakStat : 1;
    uint8_t LowVolStop : 1; // also DataError
    uint8_t LowVolControl : 1;
    uint8_t EABSStart : 1;
    uint8_t Exchange : 1;
    uint8_t Global_state_2b : 1;
    uint8_t GearDisable : 1;
    uint8_t DefaultFW : 1;
    uint8_t SpeedLimit : 1;
    uint8_t MidSpeedEnabled : 1;
    uint8_t HighSpeedEnabled : 1;
    uint8_t FDEnable : 1;
    uint8_t FDBrake : 1;

    // 8
    uint8_t Global_state3 : 1;
    uint8_t FDStart : 1;
    uint8_t FDClose : 1;
    uint8_t FDWay : 1;  
    uint8_t SpeedLimitEnabled : 1; 
    uint8_t PhaseCZero : 1; 
    uint8_t FDWork : 1; 
    uint8_t WUVD : 1;   
    uint8_t PhaseAZero : 1; 
    uint8_t ShouldBeStat : 1;   
    uint8_t ZeroUseable : 1;
    uint8_t VUWD : 1;   
    uint8_t WUUD : 1;   
    uint8_t UUWD : 1;   
    uint8_t VUUD : 1;   
    uint8_t UUVD : 1;

    // 10
    // Global_state4;    
    uint8_t VolFlash : 1;
    uint8_t FlashError : 1;
    uint8_t DeadZone : 1;
    uint8_t CANType : 1; // CommEnable
    uint8_t unkDAa : 1;
    uint8_t unkDAb : 1;
    uint8_t unkDAc : 1;
    uint8_t Zsignal : 1;
    uint8_t ABError : 1; // also SyncCount
    uint8_t ZError : 1;
    uint8_t PError : 1;
    uint8_t MagnetError : 1;
    uint8_t ZABError : 1;
    uint8_t PABError : 1;
    uint8_t AngleError : 1;

    int16_t MosTemp;

// 0xDC
    uint16_t unkDC;
    uint16_t unkDD;
    uint16_t unkDE; 
    uint16_t unkDF; // changed from 0x57 00 to 0x01 40
    uint16_t unkE0;
    uint16_t unkE1;

// 0xE2
    // 0
    // uint8_t xsControl : 2;
    // uint8_t gear : 2;
    // uint8_t reversing : 1;
    // uint8_t rollingV : 1;
    // uint8_t pad1 : 1;
    // uint8_t compPhoneOK : 1;
    uint8_t forward : 1;
    uint8_t reverse : 1;
    uint8_t gear : 2;
    uint8_t sliding_backwards : 1; // Reversing
    uint8_t motion : 1; // rollingV
    uint8_t unkE2a : 1;
    uint8_t compPhoneOK : 1; // 1

    // 1 function state?
    uint8_t phaseA_active : 1;
    uint8_t phaseB_active : 1;
    uint8_t phaseC_active : 1;
    uint8_t passOK : 2; // 2
    uint8_t Bmq_Hall : 1;
    uint8_t unkE2b : 1;
    uint8_t function_state128 : 1;

    // 2
    uint8_t motor_hall_error : 1; // E3
    uint8_t throttle_error : 1;
    uint8_t current_protect_restart : 1;
    uint8_t phase_current_surge_protect : 1;
    uint8_t voltage_protect : 1;
    uint8_t alarm_protect : 1;
    uint8_t motor_temp_protect : 1;
    uint8_t controller_temp_protect : 1;

    // 3
    uint8_t phase_current_overflow_protect : 1;
    uint8_t phase_zero_error : 1;
    uint8_t phase_int16_t_protect : 1;
    uint8_t line_current_zero_error : 1;
    uint8_t mosfet_high_side_error : 1;
    uint8_t mosfet_low_side_error : 1;
    uint8_t moe_current_protect : 1;
    uint8_t brake : 1;

    // 4
    uint8_t modulation; // / , E4

    // 5
    uint8_t pad;

    // 6-7
    uint16_t speed; // E5

    // 8-9
    int16_t unk1;

    // 10-11
    int16_t unk2; // throttle request?

// 0xE8
    int16_t deci_volts; 
    int16_t per_mille;
    int16_t lineCurrent; // / 4   
    int16_t unk3;
    int16_t unk4; // something throttle?
    int16_t throttle_depth;

// 0xEE
    int16_t unkEE; // 2-3 pins states? something discovery
    int16_t unkEF; // 4-5
// 0xF0 - 0x8A, xx written to not enter non-following status
    big_end_24b phase_Acurr; // 1.953125 * Math.Sqrt(num)
    big_end_24b phase_Ccurr; // 1.953125 * Math.Sqrt(num)
    int16_t volts; // mabe

// 0xF4
    int16_t motor_temp;
    int8_t unkF5;
    int8_t batt_cap; // SOC
    uint8_t unkF6;
    uint8_t ManufYear; // + 2000, paracnt_6
    uint8_t ManuMonth; // paracnt_7
    uint8_t ManuDay; // paracnt_8
    uint16_t paracnt_17;  
    uint16_t paracnt_16;  
    
// 0xFA
    int16_t PhaseAZero2;
    int16_t PhaseCZero2;
    uint8_t motor_stop_state;

    // 8
    uint8_t unkFC : 1;
    uint8_t old_blue : 1;
    uint8_t unkFD : 6;
    
    uint8_t unkFEa;
    uint8_t unkFEb;
    uint8_t motor_running_state;

};
#pragma pack(pop)

#define PRINT_OFFSETOF(A, B) char (*__daniel_kleinstein_is_cool)[sizeof(char[offsetof(A, B)])] = 1

static_assert(offsetof(FardriverData, MaxLineCurr2) == (0x63 << 1));
static_assert(offsetof(FardriverData, LmtSpeed) == (0x6C << 1));
// static_assert(offsetof(FardriverData, PPin) == (0x69 << 1));
static_assert(offsetof(FardriverData, unk7Ca) == (0x7C << 1));
static_assert(offsetof(FardriverData, ThrottleVoltage) == (0x82 << 1));
static_assert(offsetof(FardriverData, RatioMin) == (0x88 << 1));
static_assert(offsetof(FardriverData, Ratio6000) == (0x8E << 1));
static_assert(offsetof(FardriverData, nratio_4) == (0x94 << 1));
static_assert(offsetof(FardriverData, nratio_16) == (0x9A << 1));
static_assert(offsetof(FardriverData, unkA0) == (0xA0 << 1));
static_assert(offsetof(FardriverData, unkAC) == (0xAC << 1));
static_assert(offsetof(FardriverData, unkB2) == (0xB2 << 1));
// static_assert(offsetof(FardriverData, OneCommPos) == (0xB8 << 1));
static_assert(offsetof(FardriverData, unkD6) == (0xD6 << 1));
static_assert(offsetof(FardriverData, unkDC) == (0xDC << 1));
static_assert(offsetof(FardriverData, speed) == (0xE5 << 1));
static_assert(offsetof(FardriverData, deci_volts) == (0xE8 << 1));
static_assert(offsetof(FardriverData, unkEE) == (0xEE << 1));
static_assert(offsetof(FardriverData, motor_temp) == (0xF4 << 1));
static_assert(offsetof(FardriverData, PhaseAZero2) == (0xFA << 1));
