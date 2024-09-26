#ifndef _010EDITOR
#include <cstdint>
#include "fardriver_message.hpp"
#endif

// Pins with PINInvalid3 assigned to it disables the feature, except for PausePin, which requires NC to disable
enum PIN {
    NC = 0, // Normally Closed
    PIN24 = 1,
    PIN15 = 2, // Actually P4, CAN RX
    PIN5 = 3, // Actually P5, CAN TX
    PIN17 = 4, // Used by encoder units
    PIN14 = 5, // Actually P17
    PIN3 = 6, // Actually P7
    PIN8 = 7, // Actually P8
    PB4 = 8,
    PINInvalid1 = 9,
    PIN2 = 10,
    PIN18 = 11, // Not available in YJCAN
    PIN9 = 12, // Not available in YJCAN
    PD1 = 13,
    PINInvalid2 = 14,
    PINInvalid3 = 15
};

typedef struct {
    uint32_t byte_0 : 8;
    uint32_t byte_1 : 8;
    uint32_t byte_2 : 8;
#ifndef _010EDITOR
    float value(void) {
        return 1.953125 * sqrt(byte_0 << 16 + byte_1 << 8 + byte_2);
    }
#endif
} big_end_24b;

struct FardriverData {
#ifndef _010EDITOR
    uint8_t * GetAddr(uint16_t addr) {
        return (uint8_t*)this + (addr << 1);
    }

    uint16_t GetWord(uint16_t addr) {
        return *((uint16_t*)this + addr);
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
        for (uint8_t pos = 0; pos < length; ++pos) {
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
#endif

// 0x00
struct Addr00 {
    int16_t VolCoeff;
    int16_t Voltage2Coeff;
    int16_t PhaseACoeff;
    int16_t LineCoeff;
    int16_t PhaseCCoeff;
    int16_t SaveNum;
} addr00;

// 0x06
struct Addr06 {
    // 2
    uint8_t Arg2 : 1;
    enum EAntiTheftPulse {
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
    enum EBrakeConfig {
        StopWhenGround = 0,
        StopWhenFloat = 1,
        P_StopGnd = 2,
        P_StopFloat = 3,
        BrakeDisabled = 4
    } BrakeConfig : 4;
    enum ETempSensor {
        NoTempSensor = 0,
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
    // CurrFD, Current Anti-Theft
    // 0: provide resistance to motor, does not consume battery
    // 1: lock motor, consumes battery
    uint8_t CurrAntiTheft : 1;
    enum EParkConfig {
        ReversePark = 0,
        SwitchPark = 1,
        SlowDownPark = 2,
        ParkDisabled = 3
    } ParkConfig : 2;
    uint8_t Direction : 1; // Send(0x12, 0x07)
} addr06;

// 0x0C
struct Addr0C {
    int16_t PhaseOffset; // / 10.0, Send(0x0A, 0x07)
    int16_t ZeroBattCoeff;
    int16_t FullBattCoeff;
    uint8_t StartKI;
    uint8_t MidKI;
    uint8_t MaxKI;
    uint8_t StartKP;
    uint8_t MidKP;
    uint8_t MaxKP;
};

// 0x12
struct Addr12 {
    int16_t LD;
    uint16_t AlarmDelay;
    uint8_t PolePairs; // Send(0x12, 0x01)
    uint8_t unk14b; // alway_s sent 0x59?
    uint16_t MaxSpeed; // Send(0x12, 0x02)
    uint16_t RatedPower; // Send(0x12, 0x03)
    uint16_t RatedVoltage; // / 10, Send(0x12, 0x04)
};

// 0x18
struct Addr18 {
    // 2-3
    uint16_t RatedSpeed; // Send(0x12, 0x05)

    // 4-5
    uint16_t MaxLineCurr; // / 4, Send(0x12, 0x1B)

    // 6 cfg26l
    enum EFollowConfig {
        FollowEnabled = 0,
        FollowDisabled = 1,
        EABSWhenBreakValid = 2,
        EABSWhenReleaseThrottle = 3
    } FollowConfig : 2;
    enum EThrottleResponse {
        Line = 0,
        Sport = 1,
        ECO = 2
    } ThrottleResponse : 2; // ECOConfig
    uint8_t WeakA : 2;
    enum ERXD {
        AF = 0,
        OD = 1,
        PP = 2
    } RXD : 2;

    // 7 cfg26h
    uint8_t SpeedPulse : 5;
    enum EGearConfig {
        DefaultN = 0,
        DefaultD = 1,
        GearConfig = 2,
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
};

// 0x1E
struct Addr1E {
    uint16_t FwReRatio;
    uint16_t LowVolProtect; // / 10
    // local float LowVolRestore = LowVolProtect / 10.0 + 2.0;
    char CustomCode[2];

    // 8
    // uint16_t RelayDelay; // ms
    uint8_t BCState : 1; // Edge support
    uint8_t SeatEnable : 1; // Zuotong, "bucket"
    uint8_t PEnable : 1; // PGear, "P file"
    uint8_t AutoBackPEnable : 1; // AutoBackPStat
    uint8_t CruiseEnable : 1; // XHStat
    uint8_t EABSEnable : 1;
    uint8_t PushEnable : 1; // TuixingS, "Power implementation function", enabling cancels PEnable
    uint8_t ForceAntiTheft : 1;

    // 9
    uint8_t OverSpeedAlarm : 1;
    uint8_t BrakeStillPark : 1; // ParkDisableBrake
    uint8_t RememberGear : 1; // GearRememberS
    uint8_t unk21a : 1; // default 1
    uint8_t unk21b : 1; // default 1
    uint8_t unk21c : 1; // default 0
    uint8_t BackEnable : 1; // REGear
    uint8_t RelayDelay1S : 1;

    uint8_t ModelYear; // + 2000
    uint8_t ModelMonth;
    uint8_t ModelDay;
    uint8_t TimeHour;
};

// 0x24
struct Addr24 {
    uint8_t TimeMin;
    uint8_t TimeSecond;
    uint16_t HighVolProtect; // / 10
    uint16_t CustomMaxLineCurr; // / 4
    uint16_t CustomMaxPhaseCurr; // / 4
    uint16_t BackSpeed; // Send(0x11, 0x03)
    uint16_t LowSpeed; // Send(0x11, 0x02)
};

// 0x2A
struct Addr2A {
    uint16_t MidSpeed;
    uint16_t Max_Dec;
    uint8_t FreeThrottle; 
    uint8_t unk2Cb;
    uint16_t MaxPhaseCurr; // / 4, Send(0x12, 0x1A)
    uint16_t SpeedAnalog;
    uint16_t Max_Acc;
};

// 0x30
struct Addr30 {
    uint16_t StopBackCurr; // Send(0x12, 0x18)
    uint16_t MaxBackCurr; // Send(0x12, 0x19)
    // (all * 100) / 128.0 + 0.5
    uint8_t LowSpeedLineCurr;
    uint8_t MidSpeedLineCurr;
    uint8_t LowSpeedPhaseCurr;
    uint8_t MidSppedPhaseCurr;
    uint16_t BlockTime;
    uint16_t SpdPulseNum;
};

// skip 78 bytes (0x27 addresses)
    uint16_t unk36[6];
    uint16_t unk3A[6];
    uint16_t unk42[6];
    uint16_t unk48[6];
    uint16_t unk4E[6];
    uint16_t unk54[6];
    uint16_t unk5A[3];

// 0x5D
struct Addr5D {
    uint16_t unk5D;
    uint16_t unk5E;
    uint16_t unk5F; 
    uint16_t unk60;
    uint16_t unk61;
    uint16_t unk62;
};
    
// 0x63
struct Addr63 {
    uint16_t MaxLineCurr2;
    uint16_t MaxPhaseCurr2; // 0x64
    uint8_t MotorDia;  // 65
    uint8_t unk65b;
    uint16_t TempCoeff; // 66
    uint16_t ProdMaxVol; // / 10.0 67, paracnt_0
    uint16_t ISMax; // 68, paracnt_1
    // uint16_t paracnt_2; // / 4.0 69
    // uint16_t paracnt_4; // / 4.0 6A
    // uint8_t paracnt_5;
    // uint8_t unk68b;
};

// 0x69
struct Addr69 {
    // uint16_t BstXhBcp;
    PIN PausePin : 4; // PPin, park? NC disables this feature
    PIN SideStandPin : 4; // BCPin
    PIN CruisePin : 4; // XHPin
    PIN BoostPin : 4; // Boost Pin
    // uint16_t FrWeSdhSdl;
    PIN LowSpeedPin : 4; // SDLPin Low Speed Pin
    PIN HighSpeedPin : 4; // SDHPin
    PIN ReversePin : 4; // REPin
    PIN ForwardPin : 4; // FWPin
    // uint16_t ChgFdSeatVol;
    PIN SwitchVolPin : 4; // Switch Voltage Pin
    PIN SeatPin : 4; // ZuotongPin
    PIN AntiTheftPin : 4; // FDPin, "Steel" Pin
    PIN ChargePin : 4; // CHGPin
    uint16_t LmtSpeed; // LmtSpeed 6C
    uint16_t DistanceLSB; // / 10 6D
    uint8_t ParaIndex; // ParaIndex 6E
    char SpecialCode;
};
    // local char ParaIndex3 = SpecialCode < '0' || SpecialCode >= 0x7F ? '_' : SpecialCode;
    // if (ParaIndex < 10) {
    //     local char ParaIndex2 = ParaIndex + 48;
    // } else if (ParaIndex < 20) {
    //     local char ParaIndex2 = ParaIndex + 48 - 10;
    // } else {
    //     local char ParaIndex2 = ParaIndex;
    // }

// skip 26 bytes (0x0D addresses)
    uint16_t unk6F; // 6F
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
struct Addr7C {
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
    uint8_t unk7Cc : 1;
    uint8_t MOE : 1;
    uint8_t SpeedMeterConfig3 : 1; // Analog

    // 4
    uint32_t TotalTime; // minutes, infoc0, wktime
    uint32_t infoc1;
    uint16_t DistanceMSB; // this << 16 / 10, km
};    

// 0x82
struct Addr82 {
    uint16_t ThrottleVoltage; // * 0.01, 0x82
    uint16_t HighVolRestore; // / 10.0, 0x83
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
};

// 0x88
struct Addr88 {
    // Current % for each RPM
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
};

// 0x8E
struct Addr8E {
    uint8_t Ratio6000;
    uint8_t Ratio6500;
    uint8_t Ratio7000;
    uint8_t Ratio7500;
    uint8_t Ratio8000;
    uint8_t Ratio8500;
    uint8_t Ratio9000;
    uint8_t RatioMax;

    // Energy regen % for each RPM
    int8_t nratio_0;
    int8_t nratio_1;
    int8_t nratio_2;
    int8_t nratio_3;
};

// 0x94
struct Addr94 {
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
};

// 0x9A
struct Addr9A {
    int8_t nratio_16; // 9A
    int8_t nratio_17;
    int8_t nratio_18; // 9B
    int8_t nratio_19;

    // AlarmRecord
    // 6, cfg156l, 0x9C

    // AN (Wave Type - Magnetic field weakening)
    // This function is used to control motor vibration and change the wave type used for magnetic field weakening. You can change this number from 0-16 for best results. We have found that it is best to use a low number if you are using a high power system. An example of this is one of the test bikes we have using 300amps dc in and 800 phase we use AN set to 2 to limit motor vibration across the whole RPM range. Where as a stock Sur-Ron bike would use a value of around 4. This setting should generally not be changed from the stock setting for a particular firmware but they can be adjusted in certain circumstances. 
    // - KO MOTO
    uint8_t AN : 4;
    uint8_t AlarmRecord_1 : 1;
    uint8_t RelayOut : 1; 
    uint8_t EmptySpeed : 2;
    
    // 7, cfg156h

    // LM (Wave interval - Magnetic field weakening)
    // This setting works in conjunction with AM and changes the interval of the waves being sent. This can also be used to prevent motor vibration in your set up but should be used after AM has been adjusted and has not had the desired effect. This setting should generally not be changed from the stock setting for a particular firmware but they can be adjusted in certain circumstances. 
    // - KO MOTO
    uint8_t LM : 5;
    uint8_t unk9Db : 3;

    int16_t InitVol; // 9D
    int16_t Stage1Curr; // TurtleSpeedCurrCoeff
    uint8_t VolSelectRatio; // 9F
    uint8_t unk9Fb;
};

// 0xA0
struct AddrA0 {
    uint8_t unkA0; // 0x88 usually?
    uint8_t SysCmd;
    // 01 non-following status
    // 02 self-learning/balance status
    // 03 self-learning/balance status
    // 05 non-ISOLATE_
    // 06 gather data
    // 0F ISOLATE_
    char ModelName[10]; 
};

// 0xA6
struct AddrA6 { 
    char ModelName[10];
    uint16_t unkAB; // where password is stored?
};

// 0xAC
struct AddrAC {
    uint16_t unkAC; // more password
    uint16_t unkAD; // phone number start1[14]
    uint16_t unkAE; // phone number start0[14] 
    uint16_t unkAF;
    uint16_t unkB0;
    uint16_t unkB1;
};

// 0xB2
struct AddrB2 {
    uint16_t unkB2;
    uint16_t unkB3;
    uint8_t OneCommSec_0; // SEC0
    uint8_t OneCommSec_1; // SEC1
    uint8_t OneCommSec_2; // SEC2
    uint8_t OneCommSec_3; // SEC3
    uint8_t OneCommSec_4; // SEC4
    uint8_t OneCommSec_5; // SEC5
    uint8_t OneCommSec_6; // SEC6
    uint8_t OneCommSec_7; // SEC7
};

// 0xB8
struct AddrB8 {
    // 2-3, 0xB8, OneCommPos

    // One-Line Communication Byte Positions
    uint8_t PausePosition : 4; // PPosition
    uint8_t SideStandPosition : 4; // BCPosition
    uint8_t HBarPosition : 4;
    uint8_t AntiTheftPosition : 4; // FDPosition

    // 4-5 B9
    uint16_t unkB9;

    // 6-7, 0xBA, OneCommPS
    uint8_t Pulse;
    uint8_t SQH;

    // 8-9 BB
    uint16_t OnelineCurrCoeff; // CurrentCoeff

    // 10-11, 0xBC, GPara0
    uint8_t BackPTime : 5; // ReleasePTime, ReleaseToPTime, * 10, seconds
    uint8_t ReleaseToSeat : 3; // SeatDelay, seconds
    enum ECANBaud {
        Baud250K = 0,
        Baud500K = 1,
        Baud1M = 2
    } CANBaud : 2; // CanSel
    uint8_t unkBC : 2;
    enum EPasswordStatus {
        PasswordProtected = 0,
        AlsoPasswordProtected = 1,
        NoPassword = 2
    } PasswordStatus : 2;

    // 12
    uint8_t Stage1Soc;

    // 13
    uint8_t Stage2Soc; // paracnt_3 : 4, LINECURR?
};

// 0xBE
struct AddrBE {
    enum ELowVolWay {
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
    } LowVolWay : 8; // cfg190l, CurrLimitWay

    // 3, cfg190h
    uint8_t unkBEb : 4; 
    uint8_t AccCoeff : 4; 

    uint16_t BstTime; // / 500, seconds
    uint16_t BstRelease; // / 500, seconds
    uint16_t ParkTime; // / 500, seconds
    uint16_t InverseTime;
    uint16_t TorqueCoff;
};

// 0xC4
struct AddrC4 {
    uint16_t LearnVolLow; // LearnVol
    uint16_t LearnVolHigh; // LearnVoh
    uint16_t SlowDownRpm; // ParkDiff
    uint16_t StartIs; // IsInStart
    uint16_t ThrottleInsert; // & 0x20 TCS
    uint8_t ExitFollowSpeed;
    uint8_t ReCurrRatio;
};

// 0xCA
struct AddrCA {
    uint8_t AngleLearn;
    PIN SpeedLimitPin : 4;
    PIN RepairPin : 4; // OneKeyPin
    uint8_t NoCanCnt; // CAN Detect, ms, if >= 6 then * 2 else * 500

#ifndef _010EDITOR
    uint16_t GetCanDetectMS() {
        if (NoCanCnt >= 6) {
            return NoCanCnt * 2;
        } else {
            return NoCanCnt * 500;
        }
    }
#endif
    
    // uint8_t TaRlB9D0SP; 
    enum ESPMode {    
        HighOnly = 0, // Only high speed
        AddDec = 1, // Increment/Decrement by button
        ButtonHighLow = 2, // "Point moving", 2 speed, High & Low
        ButtonLowMid = 3, // 2 speed, Low & Mid
        Button3SpeedLow = 4,
        Button3SpeedMid = 5,
        Button3SpeedHigh = 6,
        Button4SpeedLow = 7,
        Button4Speed2 = 8,
        Button4Speed3 = 9, 
        Button4SpeedHigh = 10,
        Line3Speed = 11, // Also mentions "Dial"
        CommGear = 12, // Over One Line?
        CANGear = 13,
        HighLowDisabled = 14
    } SPModeConfig : 4; // HighLowSpeed, SDHDs/SDLDs
    uint8_t Temp70 : 2;
    uint8_t LongBack : 1; // Push RE, toggle vs momentary?
    uint8_t ThrottleLost : 1;

    uint8_t LearnThrottle;
    uint8_t SpeedLowCap; // LmtSpdMinCap
    uint8_t MidSpeedCap; // LmtSpdStartCap
    uint8_t SpeedLimitByCap;
    uint8_t MinSpeedCapCoeff; // LmtSpdMaxCoeff
    uint8_t ParkCoeff : 4; // SlowDownCoeff
    enum EBattSignal {
        OneLineComm = 0,
        SerialComm = 1,
        CAN = 2,
        LithiumBattery = 3,
        LeadAcidBattery = 4,
        LFPBattery = 5
    } BattSignal : 4; // BatSel
    uint16_t ReIsinAcc;
};

// 0xD0
struct AddrD0 {
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
    enum EIdle {
        Idle0_5ms = 0,
        Idle0_9ms = 1,
        Idle1_5ms = 2,
        Idle1_9ms = 3
    } Idle : 2;
    enum EStop {
        Stop24ms = 0,
        Stop55ms = 1,
        Stop124ms = 2,
        Stop216ms = 3
    } Stop : 2;
    uint8_t ByteOption : 4; // Byte89Sel
    enum ESpecialFrame {
        SpeedPulse = 0,
        ReadyLamp = 1,
        FanControl = 2,
        Reserved = 3,
        GeneralLink2 = 16,
        // No One-Line communication
        // Other One-Line Params are invalid
        Bluetooth_TBIT = 32, 
        Bluetooth_XZ_CONTROL = 33,
        Bluetooth_XMZSBXX = 34,
        Bluetooth_XM3SPEED = 35,
        Bluetooth_M2S = 36,
        Bluetooth_CN = 37,
        // For InternalSEC & ExternalSEC, You can add these numbers to get the configuration you want
        // bits 0-1
        // 0  DATA10: power
        // 1  DATA10: current percentage
        // 2  DATA10: voltage in volts
        // 3  DATA10: use ByteOption
        // bits 2-3
        // 0  DATA9: voltage in volts
        // 4  DATA9: power
        // 8  DATA9: voltage in half-volts
        // 12 DATA9: use ByteOption
        // Different DATA0 values
        InternalSEC_08 = 48,
        InternalSEC_07 = 64,
        InternalSEC_30 = 80,
        InternalSEC_27 = 96,
        InternalSEC_10 = 112,
        InternalSEC_2B = 128,
        InternalSEC_05 = 144,
        InternalSEC_052 = 160,
        InternalSEC_25 = 176,
        InternalSEC_0A = 192,
        InternalSEC_1F = 208,
        ExternalSEC = 224,
        SpecialFrames = 240,
        RS485 = 246,
        NOSQH = 249,
        YJOneLine = 250,
        DYOneLine = 253,
        PIN24_SelectPulseOneLine = 255
    } SpecialFrame : 8; // ESQH
};

// 0xD6
struct AddrD6 {
    int16_t unkD6;

    // 4
    uint8_t Global_state1a : 1;
    uint8_t RunDir1 : 1;
    uint8_t HallPosError : 1;
    uint8_t Global_state1b : 1;
    uint8_t AutoLearn : 1;
    uint8_t NeedAutoLearn : 1;
    uint8_t Global_state1c : 1;
    uint8_t HallError : 1; // Seated
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
    uint8_t FDStart : 1; // Relay
    uint8_t FDClose : 1; // Boost
    uint8_t FDWay : 1;  // Charge
    uint8_t SpeedLimitEnabled : 1; 
    uint8_t PhaseCZero : 1; 
    uint8_t FDWork : 1;  // StlWork
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
};

// 0xDC
struct AddrDC {
    // all formatted as %d
    int16_t unkDC;
    int16_t unkDD;
    int16_t unkDE; 
    int16_t unkDF; // changed from 0x57 00 to 0x01 40
    int16_t unkE0;
    int16_t unkE1;
};

// 0xE2
struct AddrE2 {
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
    uint8_t passOK : 2; // = 2
    uint8_t Bmq_Hall : 1;
    uint8_t LowVolRem : 1;
    uint8_t MosfetCheck : 1;

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
};

// 0xE8
struct AddrE8 {
    // 2-3
    int16_t deci_volts; 
    // 4-5
    int16_t per_mille; // * 3.3 * 1.5 / 4096.0
    // 6-7
    int16_t lineCurrent; // / 4   
    // 8-9
    int16_t unk3;
    // 10-11
    int16_t unk4; // something throttle?
    // 12-13
    int16_t throttle_depth;
};

// 0xEE
struct AddrEE {
    // 2-3 pin states?
    // analyzetype:
    // P = 0
    // BC = 1
    // RE = 2
    // SDH = 3
    // SDL = 4
    // XH = 5
    // SEAT = 6
    // analyzetype written to unkEE[0] and anaylzenum (bit index) written to unkEE[1]
    // H97 later support
    int8_t unkEE[2];
    int16_t unkEF; // 4-5
    // 0xF0 - 0x8A, xx written to not enter non-following status
    big_end_24b PhaseACurr; // 1.953125 * Math.Sqrt(num)
    big_end_24b PhaseCCurr; // 1.953125 * Math.Sqrt(num)
    int16_t volts; // mabe / 16
};

// 0xF4
struct AddrF4 {
    int16_t motor_temp;
    int8_t unkF5; // * 3600 / 256
    int8_t batt_cap; // SOC
    uint8_t unkF6;
    uint8_t ModifyYear; // + 2000, paracnt_6
    uint8_t ModifyMonth; // paracnt_7
    uint8_t ModifyDay; // paracnt_8
    uint16_t EXETotal; // F8 / 8.0, us, paracnt_17
    uint16_t EXESingle; // F9 / 8.0, us, paracnt_16
};

    //  0 "ProdMaxVol",
    //  1 "ISMax",
    //  2 "ProdMaxLine",
    //  3 "LINECURR",
    //  4 "ProdMaxPhase",
    //  5 "ISG",
    //  6 "ModifyYear",
    //  7 "ModifyMonth",
    //  8 "ModifyDay",
    //  9 "P_Position",
    //  10 "B_Position",
    //  11 "",
    //  12 "Line Zero",
    //  13 "PhaseA Zero",
    //  14 "PhaseC Zero",
    //  15 " ",
    //  16 "EXESingle",
    //  17 "EXETotal"

// 0xFA
struct AddrFA {
    int16_t PhaseAZero2; // FA
    int16_t PhaseCZero2; // FB
    uint8_t motor_stop_state; // FC
    uint8_t unkFCa : 1;
    uint8_t old_blue : 1;
    uint8_t unkFCb : 6;
    
    uint8_t unkFD; // FD
    uint8_t unkFD;

    uint8_t motor_running_state; // FE
    uint8_t unkFEb;

    uint16_t unkFF;
};

};

#ifndef _010EDITOR

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
#endif