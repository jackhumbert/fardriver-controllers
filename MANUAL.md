# Fardriver Controller Parameter Description

## 2023 08 08

## Editor notes:

* 12-tube refers to the number of transistors in the controller - I don't think this is labeled anywhere on the device (at least on mine)

# 1 PC Software Interface

When the serial port and CAN analyzer are not connected, the following screen is displayed:

![image](/images/0.jpg)

When you connect the serial port or turn on CAN, the following screen is displayed:

![image](/images/1.jpg)

Once connected to the controller, the data is uploaded from the controller to the host computer page:

![image](/images/2.jpg)

**The view contains a dashboard page to dynamically view the working
parameters, a statistics page to view the dynamic characteristics of the
controller work in real time, a status table to view the controller work
status in real time, you can also click "Collect" to view the 2048 groups of
samples after the first refueling door of the running data, without turning off the power, it has been saved in the controller. For example, 0. 1 second
sampling**

**For one set of data, the controller can record 205 seconds of data to analyze the vehicle's driving characteristics.**

![image](/images/3.jpg)
![image](/images/5.jpg)
![image](/images/6.jpg)

# 2 Parameters

![image](/images/7.jpg)

## 2.1 Basic motor parameters

### 2.1.1 Position Sensor

`AngleDetect` in the app.

The controller is divided into 4 types of hardware according to different position sensors:

1. Hall Edition
2. Incremental encoder version
3. Differential encoder version
4. Absolute encoder version
5. Rotary encoder version

| Serial number | Options | Controller Hardware |  Extension Code | Version |
|---|---|---|---|---|
| 0 | 120° Hall | Hall Version Controller | | H,R,I |
| 1 | Conventional incremental encoders | Encoder Version Controller | | H,R,I |
| 2 | Conventional incremental encoder 4096 | Encoder Version Controller | | H,R,I |
| 3 | Conventional incremental encoder 8192 | Encoder Version Controller | | H,R,I |
| 4 | Differential Encoder 2048 | Differential Encoder Controller | Internal J, External Q | H,R,I |
| 5 | Differential Encoder 4096 | Differential Encoder Controller | Internal J, External Q | H,R,I |
| 6 | Differential Encoder 8192 | Differential Encoder Controller | Internal J, External Q | H,R,I |
| 7 | Differential Encoder 16384 | Differential Encoder Controller | Internal J, External Q | H,R,I |
| 8 - 12 | | | | |
| 13 | Absolute encoders 13 | Absolute encoder control tool | Built-in H, External P | H,R,I |
| 14 | Absolute encoders 14 Absolute encoder control tool | Built-in H, External P | H,R,I |
| 15 | Reserved | | | |
| 16 | 60° Hall | Hall Version Controller | | H,R,I |
| 2 - 15 | 2-15 Corresponding rotation to pole number | Rotary Controller |  | X, U | 

Modify the sensor and click Save to make it effective. Hxx and above versions support this option. Old versions cannot select this option.

| Hardware Version | Description |
|---|---|
| 7 | Controller version from some years ago, single function, relatively solidified |
| G | Earlier versions of the controller, single-function and relatively solidified |
| A | New version, support some parameter settings, single function, relatively solidified |
| B | New version, support some parameter settings, single function, relatively solidified |
| H | Newest, universal, 30P, rich parameters |
| L | Newest, universal, dual-band, 30P, rich parameters |
| R | Latest, national standard, dual-band, 6-pole + 8-pole + 16-pole socket, rich in  |parameters
| Q | Newest, national standard, 6-pole+8-pole+16-pole socket, rich parameters |
| I | Newest, isolated, 30P, rich parameters |
| J | Newest, isolated, dual-band, 30P, rich parameters |
| X | Newest, rotary change, 30P, rich parameters |
| U | Newest, isolated rotary, 30P, rich parameters |
| M | 2024 New version, general purpose, 30P, rich in parameters. |
| N | 2024 new version, universal, dual band, 30P, rich parameters. |

There are many types of software programs, so I won’t list them all.

Special codes can tell whether it is a special program:

| Code | Meaning |
|---|---|
| 0 - 7 | Hall Vector Starting Velocity |
| + 8 | 8x PID |
| + 16 | deep weak magnetic field program |
| + 32 | Brake Inspection |
| + 64 | Old controller |
| +128 | No Bluetooth RS485 communication program |
| +256 | Customized programs for Series 8 |
| +512 | Customized programs for series 12 |
| +1024 | Customized programs for series 16 |
| +2048 | Isolated version of the program |
| +4096 | 120M high speed version of the program |

There are also various specific programs with special user requirements that are not reflected in the code.

### 2.1.2 Temperature Sensor

`TempSensor` in the app.

| Options | Hxx Version | Old version |
|---|---|---|
| None | √ | √ |
| PTC-1000 | √ | √ |
| NTC-230K | √ | √ |
| KTY84-130 | √ | Program fixing KTY84-130/KTY83-122 |
| theoretical | √ | √ |
| KTY83-122 | √ | × |
| NTC-10K | √ | × |
| NTC-100K | √ | × |

### 2.1.3 Phase Shift

`PhaseOffset` in the app.

The angular position of the motor is a key characteristic, which is usually indicated by the motor manufacturer. Most of the hub motors on the market are 30°, 210° and 90°, but there are some special motors. Note that the motor factory labeling method is different from the far drive logo, if you are not sure about the angle, you can find this value through self-learning methods.

Generally, the error of phase shift between two operations is not more than 2°, which proves that there is no problem in the operation method and the phase shift is not a problem.

#### 2.1.3.1 Start Self-learning With a Host

Click the self-learning button on the host (computer, phone), and you will hear 2 short and 1 long sounds inside the controller, prompting that self-learning has been started.

In addition, click the cancel self-learning button on the host, and the prompt sound disappears, indicating that self-learning has been canceled.

#### 2.1.3.2 Start Self-learning Without a Host

This method is applicable to all controllers with brake line function installed, ND series, CN series, BN series controllers with software version 783 or above. Version A01 and above requires that you hold the handlebars before turning on the machine, and do not let go, following these operations:

1. Keep the brake connected, the controller is off and the motor is stationary.
2. Turn the throttle wide open and turn on the machine. At this time, the controller alarms and the motor does not rotate.
3. Enter self-learning sequence, Morse code 8 bits: `11000000`:
    * 1: Long squeeze brake 0.5 sec-2 sec
    * 0: Short squeeze brake less than 0.5 sec

When you hear 2 short and 1 long, you are in self-learning mode. If you don't hear it, consider that you have made a mistake and try to re-enter the Morse code.

#### 2.1.3.3 Self-learning Process

After entering the self-learning state, suspend the wheel off the ground and hold the throttle wide open. At this time, the motor should start to rotate. If it does not rotate, it may be that the Hall line has been swapped or the motor line has been swapped. At this time, you only need to swap the blue and green large lines to make it rotate.

After it rotates, the speed will be close to the motor fixed speed, and then the phase shift will be automatically adjusted to adapt to the motor. Then the motor will reverse and adapt to the motor. After the automatic completion, the motor stops. You can release the throttle. The self-learning is completed.

A well-trained motor will remain quiet.

#### 2.1.3.4 Changing the direction of the motor via Morse code

After the self-learning is completed, if you find that the normal startup motor is reversed, then you can modify the motor direction through a host, you can also change the motor direction through the Morse code sequence `11110000`. If you find that the motor is reversed after the motor self-learning, you can correct the direction of the motor through this instruction.

#### 2.1.3.5 Limit the speed via Morse code:

`MorseCode` in the app.

The Morse code can be changed through a host to set 6 digits to release the speed limit. There is no restriction when the value is `000000` (default). When enabled, you must enter the Morse code every time the unit is powered on in order to release the speed limit.

Setting the 7-digit Morse code is the speed limit, which is also the 6-digit number after the operation. The speed limit will be converted once after each operation: if it is originally a speed-limited state, it will become a non-speed-limited state, and vice versa. This conversion is saved inside the controller, and it will switch to this state every time it is turned on.

### 2.1.4 Pole Pairs

Hall motors default to 4 and does not need to change. The pole pair setting for encoder motors must be accurate otherwise it can not rotate. Selectable values 3, 4, 5, 6, 7, 8, 10, 12, 14, 16-30, Encoder: 3-8 Pole Pairs display the actual rotation speed, above 10 pole pairs display the rotation speed according to 4 poles pairs. To modify the number of pole pairs, you have to click save to make it effective.

### 2.1.5 Motor Direction

Specifies the motor direction when moving forward.

* 0: Sprocket is on the right
* 1: Sprocket is on the left

Only effective after reset and save.

### 2.1.6 Rated Speed

The speed of the motor at the rated voltage, referred to as the rated speed, is often referred to as the fixed speed in the electric motorcycle industry. This fixed speed determines the highest motor speed. Generally speaking, a common controller can drive the motor to the maximum speed near the fixed speed under the rated voltage. The controller will recognize the rated speed at the current voltage during self-learning.

### 2.1.7 Rated Voltage

The maximum number of strings of batteries for the NJ Far Drive Controller for different voltages is as follows:

| Voltage | Lead-acid | Lithium Ion | Lithium Iron Phosphate |
|---|---|---|---|
| 48V | 4 | 13-14 | 16 |
| 60V | 5 | 17 | 20 |
| 72V | 6 | 21 | 24 |
| 75V | 6 | 22 | 25 |
| 84V | 7 | 24 | 28  |
| 96V | 8 | 28 | 32 |
| 108V | 9 | 32 | 35-36 |

🎧 Factory Settings 72 Series=72V,75 Series=75V,84 Series=84V,96 Series=96V, Series=108V

Note that the rated voltage affects the power display, the setting can not be higher than 🎧factory voltage, after setting the parameters, you have to tap save again, valid after reset.

### 2.1.8 Rated Power

The rated power of the motor, please set it according to the actual condition of the motor.

### 2.1.9 Maximum Speed

Limits the maximum motor speed. In the EV market, the maximum speed is usually not limited, but the maximum speed is limited by the current limiting parameter at the back. After the speed exceeds the fixed speed, it automatically enters the weak magnetization state. The more the speed exceeds the fixed speed, the greater the depth of weak magnetization.

Depth of weak magnetization: `(Maximum speed - Fixed speed) / Fixed speed * 100%`. Generally, hub motors can be weakly magnetized up to 50%.

Some hub motors can have a weak magnetic depth of more than 100%. Therefore, we stipulate that the weak magnetic depth of surface-mounted motors should not exceed 50%, while the weak magnetic depth of embedded motors should not exceed 150%.

### 2.1.10 Maximum Phase Current

Maximum value of phase line current of the operating motor. Determines the motor output 🎧 maximum torque at standstill to rated speed.

The maximum phase current has a maximum limit on the controller hardware, and the set value is not allowed to exceed 🎧🎧 factory setting. Failure to do so will result in a much higher probability of the controller burning out.

Different types of motors will exhibit different output 🎧 torque for the same maximum phase current setting. The torque version of the motor has a high output 🎧 torque, the balanced version has a slightly lower output 🎧 torque, and the speed version of the motor has the smallest output 🎧 torque. The motor with low fixed speed has a high loss 🎧 torque and the motor with high fixed speed has a low loss 🎧 torque.

### 2.1.11 Maximum Line Current

The maximum value of the controller's working battery bus current. Determines the maximum power output of the motor. Controller maximum input power = battery voltage * maximum line current. This current is limited to the customer's maximum line current. This value determines the maximum output power, and thus the maximum speed.

### 2.1.12 Reverse Speed

Maximum RPM for reverse.

### 2.1.13 Swap Phase Wires

`PhaseExchange` in the app.

Default is 0, if the blue and green lines are swapped, it is 1. Note that if this parameter is incorrect, the motor will not rotate.

This parameter is valid after reset and is automatically modified by the Hxx version self-learning.

### 2.1.14 Weak magnetic properties

General fast, high speed jitter big change to medium, generally do not use slow, easy to overcurrent

### 2.1.15 Weak magnetic response

0-6, none means no weak magnetization. Default weak magnetic response 0 Speed Expansion: Pushing the motor speed to a higher speed than the fixed speed is called speed expansion.

1. Increase the working voltage, the higher the voltage, the higher the motor speed.
2. Do not increase the working voltage, through the weak magnetization, increase the speed of the motor.

Without changing the battery voltage, the motor speed is increased directly by controlling the current limiting parameter.

## 2.2 Acceleration and deceleration characteristics

### 2.2.1 Acceleration sensitivity

Acceleration speed, 8-224, the higher the number, the faster the throttle response.

An electric car is usually a gas pedal, while an electric motorcycle is a gas turn knob or center control.

While an electric car should have a moderate response to the gas pedal, the requirements of an electric motorcycle are different; some customers require it to be light, slow, and steady, while others require it to be responsive and ready at the touch of a button.

Acceleration sensitivity refers to how fast or slow the throttle response is. This parameter ranges from 16 to 224. The larger the number, the more sensitive the throttle acceleration. 16 is already slow, and a setting of 32 is generally appropriate for electric vehicles, rarely exceeding 64.

For electric motorcycle, besides setting at 32, many users prefer fast response, so setting at 64, 128. track race even set at 224.

### 2.2.2 Deceleration sensitivity

Deceleration speed: 16-224, the higher the number the shorter the return throttle lag.

### 2.2.3 Motor position

Non-set value, display of motor angle

### 2.2.4 Throttle Return

Default 0

### 2.2.5 Throttle Response

According to different user preferences, the throttle characteristics have three configurations: linear, sporty, and economical.

### 2.2.6 Economic acceleration parameters

Default 8

### 2.3 Throttle Threshold

Throttles on the market are uneven, and the voltage value will vary from throttle to throttle or gas pedal to gas pedal.

| | Idle voltage | High voltage |
|---|---|---|
| Electric Motorcycle | 0.8V-0.9V | 4.1-4.3V |
| Central control handle | 0.8V-0.9V | 4.5-4.95V |
| 12V Accelerator pedal | 0.0V-0.2V | 4.6-4.8V |

### 2.3.1 Low Threshold

We set the low throttle threshold based on the idle voltage. Considering the fluctuation of the throttle voltage, setting the low throttle threshold should generally be 0.2-0.3V higher than the idle voltage, in order to ensure that the motor is working in the idle state when stopping. For example, the low throttle threshold for an electric motorcycle throttle would be set to 1.1V, while the low throttle threshold for a 12V gas pedal would be set to 0.5V.

### 2.3.2 High Threshold

We set the high throttle threshold based on the full bar voltage. In order to make the controller capable of delivering 🎧full power in the full bar state rate, we need to get the setting below the full handle voltage. But here we have to be careful not to set it too low. In order to automatically detect whether there is any damage to the electronic throttle, we set a value 0.6V higher than the high throttle threshold as the alarm limit, once exceeded, it is considered that the throttle is damaged, and the controller immediately stops the power loss 🎧 to avoid the vehicle from flying, to avoid causing a flying safety accident.

So when we set a high throttle threshold, for example, 4 .1-4.3V for an electric motorcycle throttle full handle, we would set the 3.9V as the high throttle threshold. For a 12V gas pedal we would set the high throttle threshold at 4.3V.

The 742 and above versions add a throttle self-learning function. When turning to the bottom during self-learning, the controller automatically recognizes the maximum voltage of the throttle signal from the throttle/pedal and generates a throttle high threshold based on this voltage.

## 2.4 Product Model

### 2.4.1 Date

### 2.4.2 Duration

### 2.4.3 Model: Controller Model

# 3 Current Limit

![image](/images/8.jpg)

## 3.1 Motor current limiting protection factor

Conversion of 500RPM, 1000RPM,...8500RPM, and 9000RPM in current limit.

These speeds are based on the number of poles calibrated in the parameters. For motors with an actual pole pair number greater than or equal to 16, a conversion is required. 

Usually the pole pair number of the hub motor is 16, 20, 24, 28, 30 pole pairs.

And usually the mid-mounted motor is 3, 4, 5, 7, 8, 14 pole pairs.

If the number of pole pairs = 4 in the parameter, the motor speed = the speed on the host computer * 4 / the actual number of pole pairs of the motor. For example, if the pole pair number of the hub motor is 16:

|Listed RPM|Actual RPM|
|---|---|
| 500RPM | 125RPM |
| 1000RPM | 250RPM |
| 4000RPM | 1000RPM |
| 5000RPM | 1250RPM |
| 5500RPM | 1375RPM |
| 6000RPM | 1500RPM |
| 6500RPM | 1625RPM |
| 8000RPM | 2000RPM |

Weak magnetism limitation: gradual increase of current limiting parameters. 

The setting of the current limit value starts from the safe value and gradually increases the speed. It is necessary to ensure that the weak magnetic field is not excessive. Once the idling speed is found to be unstable or even MOE or OVER protection is triggered, it means that the speed is too high and the weak magnetic field is excessive. The parameters should be changed back.

The current limit value we set should be considered according to the actual demand. For a motor with a fixed speed of 1000RPM, the depth of weak magnetization is considered to be 50%. The maximum speed is also considered to be 1500RPM, and it is hoped that the motor will not operate above 1625RPM. Therefore, the current limit value is set at 30% for 6000RPM and less than 5% for 6500RPM and above.

This ensures that the motor is only 50% weakly magnetized when idling. This ensures that the motor is only 50% weak when idling, and that it will not be too weakly magnetized, causing the motor to jitter or even burn out.

In many motors, the depth of weak magnetization can reach 100%, and 1000RPM motors can operate at high speeds of 2000RPM. For this type of motor, the current limiting factor can be expanded in order to maximize performance. The current limiting parameter can be set above the normal value of 70 for 8000RPM, 30 for 8500, and below 5 for 9000RPM.

## 3.2 Speed Control Rating

Speed Control Levels: Default 4 levels: BOOST, HIGH, MEDIUM, LOW.

1. BOOST file: Bst is displayed on the mobile APP/computer, it is valid when the BOOST function is on and the BOOST time is set by the 4.3 Parameter control, BOOST operates at 🎧 factory customer maximum line current, maximum phase current, and current limiting factor limits.
2. HIGH SPEED: Displayed on mobile APP/computer D. High speed is subject to maximum line current, maximum phase current, current limiting factor and maximum speed limiting conditions.
3. Medium speed: The DM is displayed on the mobile APP/computer. medium speed is limited by the medium speed line current ratio, medium speed phase current ratio, and by the medium speed RPM.
4. LOW SPEED: DL is displayed on the mobile APP/computer. low speed is limited by low-speed line current ratio, low-speed phase current ratio, and by low-speed RPM.

### 3.2.1 Low-speed gear parameters

Low-speed line current scaling, low-speed phase current scaling, low-speed speeds

### 3.2.2 Parameters of medium-speed gear

Medium-speed line current scaling, medium-speed phase current scaling, medium-speed speeds

### 3.2.3 LDVOL

200-900, default 900

Matching of idling noise in high speed section and balance between power and power saving at the highest speed

### 3.2.4 LQVOL

1) Middle throttle voltage (mV, VQH+4, middle throttle enabled, 0~4000).
2) Speed ​​limit current, (0~4000, unit 1/4A)

### 3.2.5 FAIF

|||
|---|---|
| 0 | Starting Resonance Characteristic Matching Option 1. Note that when the vehicle motor is performing well, VQH+64 = six times the speed Hall detection energy. Further reduces resonance noise. |
| 16-63 | Starting Resonance Characteristic Matching Option 2 |
| 64-256 | General Vehicle Motor Hall Characteristics |
| 384,512 | Select 384/512 when the jumping car AB15 is prone to reporting errors. |
| 513 | The AB15 alarm is ignored in the case of CN controller absolute encoders. Other controllers: easy to use when AB15 reports an error. |
| +1024 | Fixed Bluetooth password is product number related |
| | (Do not use other options) |


### 3.2.6 L2, L4: reserved

### 3.2.7 Speed Limit RPM: The RPM used for Morse code speed limiting.

# 4 Energy Regeneration

![image](/images/9.jpg)

For the throttle return brake function, during riding, the electronic brake state will be entered after the throttle is returned.

For the electronic brake function, when braking, the whole vehicle sends a brake signal to the controller, and the controller enters the electronic brake state after detecting the brake signal.

Note that when using the electronic brake function, you must select electronic brake or throttle return brake in the follow item to enable this function. And set the return current. Note that when setting parameters, the maximum return current is generally 25%~50% larger than the stop return current.

## 4.1 Brake current limitation

### 4.1.1 Brake current

Brake current for e-brake. Default 2A, change to 5A-20A as needed when you need e-brake strength, for the large capacity battery of 4-wheeler, its back-charging current is allowed to be bigger, it can be set to 20A-60A.

### 4.1.2 Maximum brake current:

Peak braking current of electronic brake: 4A by default, can be set to 10A-40A when strong braking is required, and 40A-80A can be considered for four-wheel vehicles.

### 4.1.3 Throttle return brake point

Default is 0, the faster the throttle return speed, the smaller the braking force. Slow speed, light braking force. 

1: The braking force is the greatest when the throttle is returned. Above this speed, turning the handlebar back halfway is a constant speed without acceleration or deceleration. For example, 4000 means that the higher the speed from 0 to 4000, the closer it is to half the throttle value. The middle throttle value above 4000 is a constant speed without acceleration or deceleration. When the handlebar is higher than the middle value, it accelerates, and when it is lower than the middle value, it decelerates. The more you turn the handlebar back, the stronger the brakes.

## 4.2 Negative current coefficient

The scale factor that controls the reverse charge current is controlled at 500rpm, 1000rpm,...,9000rpm. The maximum value of the coefficient is 0 and the minimum value is -100. The closer to -100, the more negative the current.

For ordinary two-wheeled vehicles, for the controller about 400A, negative current factor -10%--30% is enough. Other controllers should be adjusted according to the situation. For the sake of driving safety, you can start from -10% to debug, if you think it is not enough, then change it to -15%, -20%, don't set it to -50%--100% all of a sudden, as this kind of operation is easy to bring the danger of braking sharply.

Older versions of the controller do not come with a negative current factor.

# 5 Functions

![image](/images/10.jpg)

## 5.1 Function input pin

* 5.1.1 BOOST: Select the BOOST function button input pin, an invalid selection will not enable this function.
* 5.1.2 Cruise: select the cruise function button input foot, selection of invalid will not enable this function
* 5.1.3 P-Phase: Select the P-Phase function button input pin, selecting **normally closed** will not enable this function.
* 5.1.4 Forward: select the forward gear function line input pin, the selection is invalid will not enable this function
* 5.1.5 Backward: Select the input pin of the backward gear function line, invalid selection will not enable this function
* 5.1.6 High-speed: select the high-speed gear function line/button input pin, the selection is invalid will not enable this function
* 5.1.7 Low speed: select the low speed gear function line input pin, the selection is invalid will not enable this function
* 5.1.8 Charging: select the charging protection function line input pin, the selection is invalid will not enable this function
* 5.1.9 Anti-theft: select the anti-theft function line input pin, the selection is invalid will not enable this function
* 5.1.10 Seat bucket: Select the seat bucket function line input pin. When someone is sitting, release the P gear and drive normally, otherwise it cannot drive. If the push function is enabled, the push assist is activated when no one is sitting. If normally closed is selected, the seat bucket signal and push function are recognized according to the VCU command. If invalid is selected, this function will not be enabled.
* 5.1.11 Speed Limit: Select the speed limit function line input pin, invalid selection will not enable this function
* 5.1.12 Voltage switching: select the rated voltage switching function line input pin, selection of invalid will not enable this function voltage switching pin = PIN8 when the national standard speed limit for the voltage pin switching, speed pin special definition
* 5.1.13 One Touch Repair: Select the One Touch Repair function line input pin, an invalid selection will not enable this function. Note that when selecting to turn on the Park function, the One Touch Repair pin serves as the switch for this function.

Note that the other pins are generally not selected to be normally closed, except for the P-pin which may be selected to be normally closed, otherwise it will affect the use of the function. The optional pin definitions are described here

| Options | 6/12 Tube NS Series | Universal Hall Connection for older controller | 18G+ 485 | YJCAN | YJBMQ CAN | Old encoder interfaces | Note |
|---|---|---|---|---|---|---|---|
| PIN2 | 2 | - | - | - | - | |
| PIN3 | 3 | 7 | 24 | 3 | 3 | 3 | |
| PIN5 | 5 | 5 | 3 | - | - | 5 | CAN Version unavailable |
| PIN8 | 8 | 8 | 14 | 8 | 8 | |
| PIN9 | 9 | - | - | | - | |
| PIN14 | 14 | 17 | 18 | 2 | 2 | |
| PIN15 | 15 | 4 | 2 | - | - | 4 | CAN Version unavailable |
| PIN17 | 17 | 30 | - | 17 | - | - | Encoder Edition It wouldn't have worked. |
| PIN18 | 18 | - | - | 14 | 14 | - | |
| PIN24 | 24 | 25 | 15 | 24 | 24 |
| PD0 | | | | | | |

## 5.2 Special feature

### 5.2.1 High and low speeds

1. High-speed only: High-speed gears only
2. Up and down gears: push button up and down gears
3. Tap High/Low: Tap 2 speeds: High + Low
4. High speed on tap: 2 speeds on tap: low + medium, (H58 version)
5. Tap 3-speed low: Tap 3-speed, default low gears
6. Tap 3-Speed Medium: Tap 3-speed, defaults to Medium Gear
7. Tap 3-speed high: Tap 3-speed, default high speed gears
8. Tap 4-speed low: Tap 4-speed, default low gears
9. Tap 4-speed 2: Tap 4-speed, default 2-speed gears
10.  Tap 4-speed 3: Tap 4-speed, default 3-speed gears
11.  Tap 4-speed high: Tap 4-speed, default high gears
12.  Toggle 3-speed: Toggle 3-speed
13.  Serial Gear: serial control gear, default serial meter for low gear booster. xm.
14.  CAN Gear: CAN controlled gear, default low speed gears
15.  null

### 5.2.2 Long press to reverse

When valid, you must long press the reverse button to toggle to backward. Invalid by default, toggles backward according to the backward line.

### 5.2.3 Gearing

| Gear | Description |
|---|---|
| 0-Default Neutral | Startup defaults to N, FW ground = forward, RE ground = reverse. |
| 1-Default forward | Startup default forward gear, RE ground = reverse, can have P gear (same as N) |
| 2-Reverse Gap | FW grounded = neutral, otherwise RE grounded = reverse, RE overhang = forward |
| 3-Default Tap Low |  Series H: FW enters burglar alarm lockout while suspended. Grounding allows traveling. Other series: default forward low speed |
| 4-Default Points in Motion | Other series: default forward medium speed, pointing |
| 5-Default point movement height | Other series: default forward high speed, pointing |

### 5.2.4 Brakes

* Brake function: you can travel when you don't squeeze the brake, and disconnect the throttle when you squeeze the brake.
* FLOATING: Pinch brake with high brake wire connected to 12V or battery voltage. Or the low brake leg is connected to battery ground. Note that the brake line signals are not isolated. When the brakes are not pinched, both wires should be floating.
* Floatation disconnection: When the brake is pinched, both high brake and low brake wires are floating. When the brake is not pinched, the high brake wire is connected to 12V or battery voltage, or the low brake foot is connected to battery ground, note that the brake wire signal is not isolated.
* P+Floating: In addition to the function of floating, release the P-gear state at the same time when squeezing the brake. P+Float
* Power-off: In addition to the float power-off function, squeeze the brake to release the P gear at the same time. Invalid: Default float traveler.

### 5.2.5 PC13

Parameters of the old controller: float travel, float disconnect, float cruise, ground cruise, invalid.

H series controller parameters: Normal response and track response.

### 5.2.6 Morse Code

1. The Morse code can be changed through the host computer to set 6 digits to release the speed, no restriction when 000000, restriction when any other code: it is necessary to operate the Morse code every time the power is turned on in order to release the speed limit.

2. Setting the 7-digit Morse code is the speed limit switch, which also operates the last 6 digits, and the speed limit will be changed once: if it was a speed limit state, it will be changed to a non-speed limit state, and vice versa. This switch is saved inside the controller, and it will be switched to this state when the controller is turned on in the future.

### 5.2.7 Incline braking

Shift into gear and hold on an incline: When moving forward or backward, releasing the accelerator will cause the car to hold on a slope. In neutral, the car will not hold, and the steep slope descent function is invalid. Hold the hill in P gear: Hold the hill in P gear. In other states, the steep slope descent function is enabled according to the steep slope descent parameter setting.

Invalid: The hold hill function and steep slope descent function are invalid.

### 5.2.8 Follow

* Follow: The motor starts at a certain idle speed
* Invalid: Block follow and electronic brake
* Electronic brake: Start the electronic brake when you squeeze the brake.
* Throttle brake: Start the electronic brake when you release the throttle

### 5.2.9 Hill Descent Control

* None: Hill Descent Control is not enabled.
* 1~7: The smaller the number, the slower the hill descent control response, and the larger the number, the faster the hill descent control response.

Parking effect: A small hill descent control number will cause more back movement but be stable, while a large number will cause less back movement but too much forward movement.

## 5.3 BOOST

### 5.3.1 BOOST Duration

Duration after BOOST startup defaults to 45 seconds, maximum 131 seconds;

### 5.3.2 BOOST Cooldown

The amount of time it takes to start BOOST again after BOOST has finished, default 90 seconds, maximum 131 seconds;

# 6 Instruments

![image](/images/11.jpg)

## 6.1 Instrumentation

The controller has 3 signal output pins.
For 12-tube controller and NS series controller: 
* 13-pin RXD
* 18-pin ALARM/SPD
* 9-pin SPA 

Old version controller: 
* 3-pin RXD
* 9-pin SPD
* 10-pin SPA

The extension code of H series controller will be marked with characters A-G.

###  6.1.1 Speed Pulse

This value, 1-31, affects the pulse speed input 🎧 and the One-Wire Speed display. The higher the number, the higher the meter display speed.

### 6.1.2 Velocity pulse base

The calibration base for the speed pulse meter. Changing this value only affects the speed display of the speed pulse meter. Hub default 40459, Center default 26043

### 6.1.3 Speedometer way

Pulse/Analog/Isolated Pulse

### 6.1.4 Analog speedometer

The phase line meter voltage indicates the coefficient used by the meter for speed, and adjusting this coefficient changes the displayed speed.

### 6.1.5 CAN

Command number, Hxx version defaults to 60, previous versions have different command numbers according to different protocols

CAN=59: supports autonomous driving system, requires dedicated CAN configuration parameters

CAN=48: (H80 version) switch from serial port to CAN analyzer debugging

### 6.1.6 CAN detection delay

Default 150ms Individual customer request 1900ms

## 6.2 One Line Parameter

When displaying the one-line communication, please be careful not to use the wrong pins.: For devices with less than 12 tubes, the 18-pin one-line connection is generally used. For configurations shared by individual drivers, the 13-pin one-line connection is used. NS series controllers with more than 18 tubes are the same as 12 tubes. Old version controllers with more than 18 tubes generally use 9-pin one-wire.

### 6.2.1 Step length

Most one-line passes are either 0.5 or 0.9. Default 0.5, optional 0.9, 1.2, 1.9.

### 6.2.2 Interval length

Most of One Line supports 55ms, default 55ms, optional 24 ms, 144 ms, 216ms.

### 6.2.3 PULSE

Default 0, non-zero for customization

### 6.2.4 SQH

Default 0: not 0 when customized

### 6.2.5 Special Frames

#### 0-1 Not connected by a single thread  

0. Speed pulse, (display adjustment: the larger the speed pulse base, the slower the display speed) 500-65530, V39 and earlier versions are 5000-65530)
1. READY Lamp: (READY status is Loss🎧High, otherwise Loss🎧Low)
2. Fan control: (Temperature below 40° is output 🎧 high, above 40° is output 🎧 low)
3. Special Serial Command BF_ZHULI
4. Special serial port command ZHULI assists pulse detection (PIN3)
5. Special Serial Command KM5
6. Special serial port command UK1
7. Special serial port commands Step length, interval duration, PULSE=0, SQH=0,DATA0-DATA1 SEC0-SEC7 Invalid

#### 16-31 General One Line 2

Different meters, DATA6/DATA9/DATA10 need to send 🎧 different content, refer to the communication protocol to select the first content:
* DATA6: Byte Option = 3 to output 🎧 0, otherwise to output 🎧
current value. Refer to the following table
* DATA9 option: refer to the DATA9/DATA10 option table below DATA10 option : refer to the DATA9/DATA10 option table below

`Special frame = 16 + DATA9 option + DATA10 option`

general one line pass = 21

| parameter group | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|
| PULSE | 0 | 0 | 0 | 0 | 10 | 0 | 0 |
| SQH | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| DATA0 | (8) 0x08 | (89) 0x59 | (24) 0x18 | (3) 0x03 | (16) 0x10 | (81) 0x51 | (16) 0x10 | 
| DATA1 | (97) 0x61 | (66) 0x42 | (2) 0x02 | (1) 0x01 | (18) 0x12 | (0) 0x00 | (149) 0x95 |

Recommended step length is 0.9ms, recommended interval
length is 144ms, some need 216ms to be normal, SEC0-SEC7
all 0 by default.

#### 32-40 No one-line pass, built-in Bluetooth

Special Frames: 
* 32 TBIT
* 33 XZ_CONTROL
* 34 XMZSBXX
* 35 XM3SPEED
* 36 M2S
* 37 CN

Step length, interval duration, PULSE=0, SQH=0,DATA0-DATA1,SEC0-SEC7 Invalid

List of 6 groups of parameters, which
vary from one One Line meter to
another.
Same, commonly used for the first set
of parameters

#### 48-223

Encryption One-Touch, Internal SEC
Different meters, DATA6/DATA9/DATA10 need to send 🎧
different content, refer to the communication protocol to select
the first content:

`Base = 48 64 80 96 112 128 144 160 176 192 208`

| Base | DATA0 | SEC0 |
|---|---|---|
| 48 |  0X08 | 0X6B |
| 64 |  0X07 | 0X9C |
| 80 |  0X30 | 0X73 |
| 96 |  0X27 | 0X0E |
| 112 |  0X10 | 0XBA |
| 128 |  0X2B | 0X2C |
| 144 |  0X5 | 0XB2 |
| 160 |  0X5 | 0X2B |
| 176 |  0X25 | 0XEA |
| 192 |  0X0A | 0X2C |
| 208 |  0X1F | 0X9E |

* DATA6: **Byte option** = 3 to 🎧 0, otherwise to 🎧
current value. **DATA9 option** : **refer to
* DATA9/DATA10 option table below DATA10
option** : **refer to DATA9/DATA10 option table
below 

`Special Frame** = Base + DATA9 option + DATA10 option`

**Suggested step length is 0.9ms, suggested interval length
is 144ms, some need 216ms to be normal, PULSE=0,SQH=0.
DATA0-DATA1,SEC0-SEC7 are invalid.
SQH Hold Invalid at SQH=255 (Protocol Specific Requirements-H43
Edition)**

#### 224-239 Encryption One-Touch, External SEC

* DATA6: **Byte option** = 3 to 🎧0, otherwise to
🎧current value. **DATA9 option** : **refer to
* DATA9/DATA10 option table below 
* DATA10 option** : **refer to DATA9/DATA10 option table
below 

`Special frame** = 224 + DATA9 option + DATA10 option`

**For professional use, all parameters can be modified:
The recommended step size is 0.9ms, the recommended
interval time is 144ms, some need 216ms to be normal.
PULSE,SQH,DATA0-DATA1,SEC0-SEC7 can be modified.**


#### 240-255 Special Frames

* 241: ATN15 bytes (PULSE,SQH,DATA0-DATA1,SEC0-SEC7 invalid)
* 242: No. 30 One-Way, P gear at DATA4
* 243: First line pass: 0x52,0x51
* 244: F2 one line through, SEC0 = 0 said F0, other numbers said F2
* 245: warning lamps synchronized to lose 🎧.
* 246: Must be specially framed when using the 485 interface = 246
Convenient PC 485 connection
* 247: 15 Byte One-Wire Pass, SQH Hold Invalid with SQH=255
(Protocol Specific Requirements - Version H43)
* 248: 13 Bytes One-Wire, SQH Hold Invalid with SQH=255
(Protocol Specific Requirements - Version H43)
* 249: NOSQH.
* 250: YJ one-wire-through, SEC0=255 allows pin 24 to select pulse/one-
wire-through
* 251: PD0 detects a line through.
* 252: PA15 Detecting One Line
* 253: DY First Line.
* 254: Without Bluetooth 485

All parameters can be modified.

| Parameter group code | 31 | 26 | 5 |
|---|---|---|---|
| pacemaker | 0.9 | 0.9 | 0.9 |
| Interval frame ms | 144 | 216 | 144 |
| Special frame | 248 | 247 | 247 |
| PULSE | 0 | 0 | 0 |
| SQH | 0 | 0 | 0 |
| DATA0 | (84) 0x54 | 0 | 7 |
| DATA1 | (83) 0x53 | 0 | 0 |
| SEC0 | 0 | 0 | 156 |
| SEC1 | 0 | 0 | 247 |
| SEC2 | 0 | 0 | 207 |
| SEC3 | 0 | 0 | 202 |
| SEC4 | 0 | 0 | 187 |
| SEC5 | 0 | 0 | 11 |
| SEC6 | 0 | 0 | 170 |
| SEC7 | 0 | 0 | 127 |
| P Position | 3 | 1 | 1 |
| Position of side supports | 2 | 1 | 8 |
| Turning handle | 0 | 8 | 8 |
| Position anti-theft location | 8 | 0 | 8 |
| Current factor | 64 | 64 | 64 |
| Byte Options | 3 | 3 | 3 |

#### Byte Options

| Byte Options | 0 | 1 | 2 | 3 |
|---|---|---|---|---|
| DATA6 | 0 | amps | amps | amps |
| DATA9 | 0-voltage | quantity of electric charge or current | quantity of electric charge or current | 0
| DATA10 | quantity of electric charge or current | Percentage of current | input voltage | 0 |

#### DATA9/DATA10 Configuration Options Table

`Special Frames = Base + DATA9 option + DATA10 option`

| DATA9 option | Byte Options |
|---|---|
| 0 | 0: Voltage unit 1V <br />1: -<br />2: Voltage unit 1V <br />3: -
| 4 | 0: Power <br />1: Power + 0x80 <br />2: First battery level <br />3: -
| 8 | 0: Voltage Unit 0.5V <br /> 1: - <br /> 2: - <br /> 3: -
| 12 | 0: Group A voltage rating <br /> 1: Group B rated voltage <br /> 2: Group C voltage rating <br /> 3: 0 |


| DATA10 option | Byte Options |
|---|---|
| 0 | 0:Power <br /> 1: - <br /> 2: Second battery level <br /> 3: - |
| 1 | 0: Current ratio <br /> 1: - <br> 2: - <br /> 3: -
| 2 | 0: Voltage unit 1V <br /> 1: - <br> 2:- <br /> 3: -
| 3 | 0: Group A voltage rating <br /> 1: Group B rated voltage <br /> 2: Group C voltage rating |

#### P Position
* 0-3: BIT position of byte 2
* 8: Not shown.
* 11: BIT position 3 of byte 4 (H40 increase)
* 13: Byte 2 = 0x0a/0x08 (H40 added)
* 14: Byte 2 = 0X0E (H40 added)
* 15: Byte 2 = 1/8 switching (H40 increase)

#### Side Stand Position
* 0-3: BIT position of byte 2
* 7: BIT7 of byte 3
* 8: Not shown.

#### Grip position
* 0-3: BIT position of byte 2
* 8: Not shown.

#### Anti-Theft location
* 0-3: BIT position of byte 2
* 8: Not shown.

### 6.2.6 SPA Transmission 🎧 Signal Description

1. Special Frames <16 Transmission 🎧 Analog Voltage
2. Special frame >=16, OBD is valid. For OBD warning light indication
3. Special Frames >= 16, OBD Invalid, New Country Marked speeding alerts are effective. Lose 🎧 high voltage when speeding
4. Special Frames >= 16,OBD Invalid, New Country Invalid speeding alerts.  When there is an alarm, lose 🎧 alarm
pulse. Without alarm, output 🎧voltage at P-
pitch


### 6.2.7 DATA0

HEAD Default 8, use other value for customization.

### 6.2.8 DATA1

HEAD2, default 97, when using SEC0-SEC7=0

### 6.2.9 SEC0-SEC7

Default 0, custom = not 0

### 6.2.10 P Position

* 0-3: P gear in BIT position of byte 2
* 7: P file in BIT position 7 of byte 5 (V40 added)
* 8: P gear is not displayed.
* 11: P gear in byte 4 position 0 (V57 increase)
* 13: P file at byte 2 = 0x0a/0x08 (V40 added)
* 14: P file in byte 2 = 0X0E (V40 added)
* 15: P-phase switching at byte 2=1/8 (V40 increase)

### 6.2.11 Side Stand Position

* 0-3: BIT position of side support at byte 2
* 7: BIT7 in byte 3 of side support
* 8: Side support in not showing.

### 6.2.12 Grip Position

One line through the inside of the rotary control display bit (0-3, default 3 ), if not set to 8

### 6.2.13 Anti-Theft Position

Burglar indicator display bit (0-3, default 8 ), if not set to 8

### 6.2.14 Current Factor

Default 64, 640=0.1A,320=0.2A 128=0.5A,64=1A,32=2A,

### 6.2.15 Byte Options

0, 1, 2, 3: contact Fardriver to adjust parameters

### 6.2.16 one-stop debugging

Most of the One-Wire default 21, byte option = 3 can basically show the speed, some meters can not show. You can try to use 1-Wire but do not know the protocol, the step size is recommended 0.9ms, the interval time is recommended 216ms, try 1-Wire to see if the meter has feedback:

1. Try special frame 16 first, byte option = 3.
2. Try parameter set 1 first: PUSLE=0,SQH=0,DATA0=8,DATA1=97.
3. If not, try parameter group 2: PUSLE=0,SQH=0,DATA0=89,DATA1=66.
4. If it does not pass then parameter other parameter groups. See the table that follows for details.
5. If all parameter groups are invalid, go to 3.2.
6. If special frame 16 does not respond, change to 16,32,48,64,80,96,112,128,144,160,176,192,208.
7. In general, try the above special frames to find the correct one line pass, for details of the voltage and power display is not correct, then a small range of special frame modification to meet the requirements: for example, to find 48 speed can be displayed normally, but the voltage and power or current display is not correct, then you can try to modify the special frame between 48 - 63 to correct the number. For example, if you find 160 speed can be displayed normally, but the voltage or current display is not correct, then you can try to modify the numbers between 160-175 in the special frame to correct the problem. If the display of P-position is inaccurate, you can modify the position of P-position to meet the display requirement.
8. If the above operations do not display the One-Wire communication correctly, try steps 3.1-3.3 again with a step size of 0.5ms.
9. For none of the above operations can you display a one-line pass. Consider special frames 247 or 248.
10. If none of the above works, then you need to contact the Fardriver to analyze the specific 224 or other special frames from 240-255.

## 6.3 Tire Ratio

Note that it has to be set correctly for the speed mileage calculations to be correct.

### 6.3.1 Tire width

Take 120/70/R12 as an example, tire width = 120

### 6.3.2 Tire Flatness

Take 120/70/R12 as an example, tire flatness = 70

### 6.3.3 Wheel R

As an example 120/70/R12, wheel R = 12

### 6.3.4 transmission speed ratio

Hall version of hub motor with pole pairs = 20, calculated for 4 pairs of poles 🎧 Transmission speed ratio = 20/5 = 5

### 6.3.5 mileage

Total miles traveled by the controller.

# 7 Protection

![image](/images/13.jpg)

## 7.1 Voltage Protection

### 7.1.1 Overvoltage protection, recovery

Internal setting based on rated voltage

### 7.1.2 Undervoltage protection, recovery

When the battery voltage approaches the undervoltage protection point, the controller reduces the power output so that the battery will not be over-discharged and damaged. The general battery undervoltage setting is as follows:

| Voltage | 48V | 60V | 72V | 84V | 96V | 108V |
|---|---|---|---|---|---|---|
| Undervoltage Point | 42V | 52.5V | 63V | 73.5V | 84V | 94.5V |

### 7.1.3 Undervoltage mode

`LowVol Way` in the app.

* +2V: Power reduction starts when the voltage reaches 2V above the undervoltage point.
* +4V: Power reduction starts when the voltage reaches 4V above the undervoltage point.
* +8V: Power reduction starts when the voltage reaches 8V above the undervoltage point.
* +12V: Power reduction starts when the voltage reaches 12V above the undervoltage point.
* +16V: Power reduction starts when the voltage reaches 16V above the undervoltage point.
* SOC 5%: Power reduction when the battery capacity is less than or equal to 20%, and slow mode when less than or equal to 5%. 
* SOC 6%: Power reduction when the battery capacity is less than or equal to 30%, and slow mode when less than or equal to 6%.
* SOC 7%: Power reduction when the battery capacity is less than or equal to 40%, and slow mode when less than or equal to 7%.
* SOC 8%: Power reduction when the battery capacity is less than or equal to 50%, and slow mode when less than or equal to 8%.
* SOC 9%: Power reduction when the battery capacity is less than or equal to 60%, and slow mode when less than or equal to 9%.
* SOC 10%: Power reduction when the battery capacity is less than or equal to 70%, and slow mode when less than or equal to 10%.
* SOP value: Limit power according to the maximum allowable line current SOP value received by the BMS/CAN bus.
* Other

## 7.2 Temperature Protection

### 7.2.1 Motor temperature protection, recovery

Internal settings

### 7.2.2 Controller temperature protection, recovery

Internal settings

### 7.2.3 Temperature

coefficient

## 7.3 Functional protection

### 7.3.1 Lost throttle alarm

Valid/invalid

### 7.3.2 Throttle plug protection

1 means that the throttle plugging and unplugging will cause a bailout to prevent flying cars caused by charged plugging and unplugging, 0 means no protection.

### 7.3.3 Back to P idle time:

Default 10 seconds

### 7.3.4 Seat bucket

delay: Default 1 sec.

### 7.3.5 Plug turn time

The unit is 0.1 second, and a setting of 50 is 5 seconds.

### 7.3.6 Parking time

Default 0.1 seconds, maximum 132 seconds; note that 0-131 seconds will cancel the parking when the time comes, while setting 132 seconds will park for a long time until the controller or the motor is over-temperature before and will cancel the parking.

## 7.4 Battery Protection

### 7.4.1 Power factor

**Calibrates the parameters displayed in the 0 capacity display.**

The controller itself can estimate the battery charge, and by adjusting the 0 charge factor and the full charge factor you can get a more accurate display of the charge. When the battery is full, adjust the full charge factor so that the displayed capacity is exactly 100%. When the battery is dead, adjust the 0 capacity factor so that the displayed capacity matches the power level. For example, when there is 10% battery power left, adjust the 0 capacity factor so that the display will be exactly 10%.

### 7.4.2 Full power factor

Calibrate the parameters of the full power display.

### 7.4.3 Limit starting power

Starting power for power limiting algorithms

### 7.4.4 Limit speed limit power

Limit Minimum Power for Power Limit Algorithm

### 7.4.5 Speed Limit Limit Factor

Limit coefficients according to the power limiting algorithm

### 7.4.6 Turtle speed limiting factor

Turtle current limiting factor default 53, Turtle current = User 🎧 Factory Maximum:

`Current * Turtle Current Factor/2048`

## 7.5 Battery Characteristics

### 7.5.1 Battery Signal Source

|Option | element | clarification |
|---|---|---|
| 0 | one-stop-shop | Obtaining the SOC of a battery through a one-line pass-through |
| 1 | serial port | Get the SOC of the battery through the serial port |
| 2 | CAN | Obtaining the SOC of the battery via CAN |
| 3 | Li-Ion | Simulation of SOC by Li-ion Ternary Battery Characterization Calculation |
| 4 | lead acid | Simulation of SOC by lead-acid battery characterization
| 5 | Lithium iron (H72) | Simulation of SOC by LiFePO4 battery characterization calculation |


### 7.5.2 current level

Displays the current battery level.

### 7.5.3 Battery Internal Resistance

Base value: 0-255, default 8

|add value|with|without|
|---|---|---|
| +256 | Measurement of second throttle/brake voltage | Detect the electric door lock voltage |
| +512 | PD Protocol | OP Protocol |
|+1024 | Protocol 2 | OP Protocol |
|+1536 | Protocol 3 | OP Protocol |
|+2048 | Protocol 4 | OP Protocol |
|+2560 | Protocol 5 | OP Protocol |
|+3072 | Protocol 6 | OP Protocol |
|+3584 | Protocol 7 | OP Protocol |
|+4096 | 8x PID, ordinary users should not change it, otherwise it is easy to damage the controller | Current sensor type >=2 is not supported |
|+8192 | 2x PID | Current sensor type >=2 is not supported |
|+12288| 4x PID | Current sensor type >=2 is not supported |

`Base value = 16053/16759 Allowed to turn on special weak magnetism (deep weak magnetism)`

# 8 PID Control

![image](/images/14.jpg)

## 8.1 AN

Motor body characteristics AN value, parameter range 0-16.

Standard surface mount motor AN=0. Standard IPM motor AN=16.

This parameter setting must be consistent with the motor characteristics. The AN value of the embedded mid-mounted motor is not less than 8. Encoder mid-mounted motors matched with remote drives and automotive permanent magnet synchronous motors all adopt AN=16.

All hub motors on the market are surface mount motors, and the AN value is generally set to 0 and not exceed 4. If the AN value is set incorrectly, the starting efficiency will be low.
There is even MOE/OVER protection.

## 8.2 LM

Vehicle motor acceleration matching parameter. This value is used to adjust the smoothness of the motor running on the vehicle.

The default setting for cars is 22, and the default setting for electric motorcycles is 18. For some small-power tricycles, 10 or less is more suitable.

However, some motor types are poorly matched with the whole vehicle, and obvious resonance vibrations can be felt at the low-speed and medium-speed stages of the start. Adjusting the LM value will improve it.

Start with 22. If the acceleration vibrations occur at low speeds, reduce the LM and test the effect from 16, 14, 12, 11, 8, and 5. The numbers in the middle will also work. Generally, it is better to be larger and try not to be too small. Too small will not be able to control the current, causing MOE/OVER protection, or even burning the control. Therefore, the LM value after the vibration disappears is the best parameter, and do not adjust it down.

Some motors and vehicles are very smooth when LM=22, but will cause jitter when it is reduced. Therefore, if there is no problem when LM=22, do not adjust this parameter.

Or if jitter resonance occurs, and the LM value is reduced from 22 to 16, 14, . . . or even 5, it does not have much effect, which means it is not related to this parameter. At this time, you must change it back to the maximum value, such as 22, instead of keeping a random number in the controller.

## 8.3 PID parameters: StartKI,MidKI,MaxKI / StartKP,MidKP,MaxKP

Default parameters StartKI=4,MidKI=8,MaxKI=12 / StartKP=40,MidKP=80,MaxKP=120.

The higher the motor power, the higher the voltage, the smaller the PID, the PID parameters can not be filled in casually, otherwise it will lead to abnormal operation or even burn control. The following are the commonly used PID setting parameters. There are 9 sets of parameters in total, choose one of them to match the motor vehicle and modify it under the guidance of professionals.

| StartKI | MidKI | MaxKI | StartKP | MidKP | MaxKP | Note |
|---|---|---|---|---|---|---|
| 1 | 1 | 1 | 10 | 10 | 10 | Surfboard Default
| 2 | 2 | 3 | 20 | 20 | 30 | Ultra High Power Motor
| 3 | 3 | 4 | 30 | 30 | 40 |
| 4 | 4 | 6 | 40 | 40 | 60 | High Power Default
| 4 | 5 | 8 | 40 | 50 | 80 |
| 6 | 6 | 9 | 60 | 60 | 90 | Medium power motors
| 6 | 7 | 10 | 60 | 70 | 100 |
| 8 | 8 | 12 | 80 | 80 | 120 | Small and Medium Power Defaults
| 8 | 9 | 13 | 80 | 90 | 130 |
| 8 | 10 | 15 | 80 | 100 | 150 |
| 8 | 11 | 16 | 80 | 110 | 160 |
| 10 | 12 | 18 | 100 | 120 | 180 |
| 10 | 13 | 19 | 100 | 130 | 190 |
| 10 | 14 | 21 | 100 | 140 | 210 |
| 10 | 15 | 22 | 100 | 150 | 220 |
| 16 | 16 | 24 | 160 | 160 | 240 | Small power motors

Note that improper PID parameter settings will cause the system to work abnormally, and even MOE/OVER/PHASE failures, etc. Too large a difference will cause burnout, so pay special attention.

Note that the PID parameters of some small-power motors exceed the controller debugging range. In this case please contact YuanDrive to solve the problem.

## 8.4 Speed SKI, SKP

SKI min. 1, max. 18, heavy car KI=18, light car KI=2, default KI=9, SKP5-20, default 10

## 8.5 MOE

MOE defaults On to turn on the protection, select Off to turn off the protection, note that it is not allowed to turn off under normal circumstances.

## 8.6 Curve Sampling

Sampling in ms intervals, Hxx and above have 2560 points in the acceleration curve, the following versions have a total of 510 points in the acceleration curve, for example, if you set 100ms sampling, then the acceleration curve will have 510 points, and the total time will be 256 seconds/51 seconds.

## 8.7 Special Code

| Version | Special code | Version | Special code |
|---|---|---|---|
| Hall Speed 128 Regular | 1 | 8x PID | +8 |
| Hall Speed 256 Light Jump Edition | 2 | Detecting brake voltage | +16 |
| Hall Velocity 384 Pu Jump Edition | 3 | Old controller | + 64 |
| Hall's Speed 512 Jump Edition | 4 | RS485 | +128 |
| Specific SERIAL8 | +256 | Specific SERIAL12 | +512 |
| Specific SERIAL16 | +1024 | high speed version | +4096 |

# 9 Stats

Hxx version valid

* 9.1 Average speed: current average speed
* 9.2 Working hours: total working hours
* 9.3 Average energy consumption: current average energy consumption
* 9.4 Error record (reserved)
* 9.5 Customer Maximum Line Current: Maximum line current of BOOST
* 9.6 Customer Maximum Phase Current: Maximum phase current of BOOST

# 10 Factory 2

## 10.1 Front and rear gear ratios

The default ratio is 64, the setting 64 is 1:1, 128 is 2:1, 32 is 0.5:1.

## 10.2 Forward and reverse speed ratios

A parameter required for forward and reverse gear shifting systems. 0-255

|add value|with|without|
|---|---|---|
| +256 | Reverse side support signal | Reverse side support signal
| +512 | Allows small current switching | Small current switching not allowed
| +1024 | Neutral Anti-Skid Parking | The gap does not prevent backward skidding.
| +2048 | Record mileage | Mileage not recorded |
| +4096 | Extension code Y Lower magnetic brake switch | Extended code Y under the Bullseye function
| +8192 | Downhill reverse charge overvoltage cutoff |  Downhill reverse charge control overvoltage
| +16384 | Shielded gear speed limit 2 | Enable gear speed limit 2
| +32768 | PD1 Input | PD1 Loss 🎧

## 10.3 Voltage selection factor

Selection of controller operating voltage by pin, calculation factor for low voltage selection.
For example, a 72V system with the voltage selection pin connected low becomes a 60V system with a factor of 60/72*128=107.

## 10.4 torque coefficient

Range 256-16384, default 8192

## 10.5 Weak magnetic current coefficient

Range 48-80, default 64

## 10.6 Backward acceleration factor

Backward Maximum Acceleration Factor Default 32, Maximum 224

## 10.7 Alarm Delay

Burglar alarm generates alarm recovery delay time setting, default 500ms Select a multiple of 100. The use of digits: 1-9 means that the brakes do not respond within 100RPM-900RPM. 0 means that the brakes respond.

| Tens digits (H59) | One Line Display | When the READY lamp turns | One Line Electronic Brake Status (H60) |
|---|----|---|---|
| 0 | brake condition | go out (of a fire etc) | demonstrate
| 1 | brake condition | go out (of a fire etc) | not shown
| 2 | brake condition | resounding | demonstrate
| 3 | brake condition | resounding | not shown
| 4 | brake failure | go out (of a fire etc) | demonstrate
| 5 | brake failure | go out (of a fire etc) | not shown
| 6 | brake failure | resounding | demonstrate
| 7 | brake failure | resounding | not shown
| 8 | brake condition | go out (of a fire etc) | demonstrate
| 9 | brake condition | go out (of a fire etc) | not shown

## 10.8 Relay delay

Setting the relay delay closing time after system power on: ms as unit, default 1ms, set to 1000ms if needed. Note: The new version of H44 controller has been changed to all function bits:

| Bit | Function | Description|
|---|---|---|
| 0 | Side stand | 0:disable side side function, 1:enable side side function, default 1
| 1 | Seat switch | 0:disable seat cushion function, 1:enable seat cushion function, default 1
| 2 | P Position | 0:Disable P position function, 1:Enable P position function, default 1
| 3 | Automatic return to P | 0:disable auto return to P function, 1:enable auto return to P function, default 0
| 4 | Cruise Control | 0:Disable cruise function, 1:Enable cruise function, default 1
| 5 | EABS | 0:disable EABS function, 1:enable EABS function, default 1
| 6 | Power-assist pushing | 0:disable the help push function, 1:enable the help push function, default 1, when pushing is enabled, the P gear will be automatically cancelled and the push mode will be entered
| 7 | Forced Anti-theft | 0:no forced anti-theft, 1:forced to enter anti-theft, default 0
| 8 | speeding alarm | 0:disable speeding alarm function, 1:enable speeding alarm function, default 0
| 9 | Automatic parking brake release | 0: Braking will release the parking brake, 1: Braking does not release the parking brake, default is 0
| 10 | Gear Memory | 0: Gear memory off 1: Gear memory active Default 1
| 11 | | Default 1
| 12 | | Default 1
| 13 | | Default 0
| 14 | Reverse | 0:disable reverse function, 1:enable reverse function, default 1
| 15 | Relay Time Delay | 0: no relay delay, 1: delay 1 sec, default 0

`Relay delay = BIT15*2^15 + BIT14*2^14 + .... +BIT1*2^1+BIT0`

## 10.9 Slow start

Default 512

## 10.10 Follow speed

The default value is 0. Some customers need to exit the follow-up within 100 turns, so they set it to 100.

## 10.11 Current theft prevention

The default is 0, which provides a large resistance to the anti-theft and is difficult to push, and does not consume batteries. When it is 1, the anti-theft lock motor will be locked and the motor cannot rotate, consuming batteries.

## 10.12 Anti-theft pulse

* Default 0:  The anti-theft signal is a level signal, pulling down the anti-theft.
* 1 (overspeed alarm == 0): Anti-theft signal is a 1mS pulse signal, if there is a pulse, it is anti-theft.
* 1 (overspeed alarm == 1): Pulse is GB data, low level is anti-theft.
* 2: Power on speed limit, pulse signal 8 to release speed limit

* Temperature 70:

Controller temperature protection 70 algorithm:

* 0 means starting control at 50°, protecting the life of the battery, controller, and motor for the longest time and extending the mileage.
* 1 means start control starts at 70°, and the temperature of the battery, controller, and motor is considered as a compromise between mileage and performance.
* 3 means start control starts at 80°, giving priority to performance, but the mileage is the shortest and rapid acceleration is most likely to cause over-temperature protection.

## 10.13 Reverse time

The time for starting the slow descent and parking when reversing, 2-48, default 36.

* Odd number: Too much gear clearance, flexible parking. H78
* Even number: Small gear clearance, normal parking H78

|add value| with | without |
|---|---|---|
| +64 | JL National Standard Status <br />Maximum speed ratio for SEC5=48V<br />Maximum speed ratio for SEC6=60V<br /> Maximum speed ratio for SEC7 = 72V | common state |
| +128 | Solve for P under 2 | Solve for P under 1
| +256 | Low-medium speed to high medium speed | Default low to medium speed 
| +512 | No sound prompt | With sound prompt
| +1024 | reserved | |
| +2048 | Silence Buzzer | Enable Buzzer
| +4096 | Enable the back-up buzzer tone | Disable the back-up buzzer tone
| +8192 | Disable motor angle sensor repair | Allows motor angle sensor repair
| +16384 | Allow brake fault repair | Disable brake fault repair
| +32768 | Reverse One-Line | Forward One-Line

## 10.14 Slow down the RPM

Steep gradient speed threshold, default 320, can be set 256-1024 to implement the speed adjustment also use this parameter.

## 10.15 Slow-down coefficient

Default is 2, can be set from 1 to 7. The larger the number, the slower the slow-down speed. Note that if the number is too large, the gear gap will be large and the vibration will occur.

The smaller the number, the faster the slow-down speed.

## 10.16 0 Speed switching

Gear shift is allowed only when speed is equal to 0

## 10.17 Deep weak magnetism

In the case of battery internal resistance = special value (please consult the far drive), the depth of weak magnetism (currently a motor factory absolute encoder motor special special dedicated) can only be set to 1 = effective. Otherwise, it will automatically return to 0=invalid.

## 10.18 RS485 protocol

Extension code = "X": Protocol control in RS485 state, default connection to RS485 instrument, after connecting to computer host computer, it will automatically enter the communication mode with the host computer.

* 0: BMS protocol control for OEM YJs
* 1: VCU protocol for OEM PD, OP
* 2: VCU protocol control for OEM DP2 numbers
* 3: For OEM xxx VCU protocol control
* 4: For OEMs 。。。。。
* 5: TUYA control for OEMs

## 10.19 Serial port sharing

Manufacturer's set value, no user alteration allowed.

||serial port|clarification|
|---|---|---|
| 1 | Not shared | RXD is used for user serial port debugging and upgrading. SPD pin is used to output speed pulse and one-line signal.
| 2 | Pull-up to share | Old controller, YJCAN Interface Board
| 3 | Drive sharing | 12 Tube and NS Series.
| 4 | RS485 | Dedicated controller. 485 interface

## 10.20 Self-learning throttle

Default 24, maximum 36, note that self-learning requires the motor in the no-load state. Normal motor when starting self-learning 24 throttle enough, a small part of the motor does not turn up, increase the throttle to 36 to start the motor. If the self-learning motor does not rotate, it is likely that the hall wire error or phase wires are not connected in sequence. Check the hall wiring, or swap the blue and green phase wires.

Try re-studying yourself again.

Self-learning throttle = 23, 24, 25, 26, 27 corresponds to different idle strengths. 23 weakest, 27 strongest.

## 10.21 Self-learning voltage low (self-learning VQL)

Base Default Value 18432, Base Wide Range Value = 25856, Normally the default value is maintained.

|add value|functionality|default|
|---|---|---|
| +1 | Activate idle clutch function (H67) | No clutch function activated
| +2 | When voltage pin = PIN8: (H72) <br />PIN14 grounded Soft Start, PIN8 ground 60V, Suspended 48/72V Automatic Voltage Switching | Voltage pin = PIN8: PIN8,PIN14 Dual line selector push down
| +4 | Reverse Neutral for Ignition Switch (H72) | Normal reverse neutral function
| +8 | Knob to adjust maximum bus bar (H72) | normal mode
| +16 | One-touch repair foot switching half current (H72) | no switching
| +32 | Pinch 2x Brake Solution P (H72) | normal P
| +64 | Press P first, then squeeze the brake to release P. (H72) | normal P
| +128 | Single cell not allowed BOOST(H74) | Normal BOOST

## 10.22 Self-learning voltage high (self-learning VQH)

Base Default Value 24320, Base Wide Range Value = 31744, Normally the default value is maintained.

|add value|functionality|default|
|---|---|---|
| +1 | Tap forward and back (H67) | Switch forward and backward 
| +2 | Dual Throttle Voltage (H72) | single throttle |
| +4 | Center Throttle Neutral (H74) | Normal throttle |
| +8 | Effective one-click repair (H72) | One-click repair doesn't work |
| +16 | Enhanced input signal filtering (H72) | Normal Input Filtering |
| +32 | Cruise speed unlimited, pushing acceleration Degree controllable (H72) | Cruise limited to 3/4 max RPM, pushing the slowest
| +64 | Six-fold speed Hall detection (H72) | Single Speed Hall Detection |
|+128 | New MTPA Vector (H73) | Conventional MTPA Vector |

# 11 Calibrate

![image](/images/17.jpg)

## 11.1 Voltage

Displays the input voltage of the controller

## 11.2 Number of calibrations

Displays the number of controller parameter modifications

# 12 Communication

![image](/images/18.jpg)

## 12.1 Communications serial port

* Port: Depending on the user's computer, check the COM port number in the Device Manager to select it.
* Baud rate: fixed 19200.

## 12.2 Software upgrades

Only the code is upgraded, no parameters are changed.

## 12.3 Flash

Upgrade the code and reset to the parameters provided by the program. Note that after flashing the HXX version, the data is cleared but the customer data is not included. You also need to use the HEB file to download the data to the controller.

## 12.4 Operation

* Self-learning: Start self-learning
* Cancel self-learning
* Save: Save data to the controller, and the new data will be used when it is reset and started next time.

## 12.5 Product number

Internal product number of the controller: unique number of the controller, used for product registration and password retrieval.

## 12.6 Area, type of control: reserved

## 12.7 Log in

The generated version software can set a 30-digit password, so that the controller can only modify parameters when the password is entered. Ordinary controllers do not have passwords. Some controllers are factory-set with a 30-digit password as required. After the password is set, the user can only view the parameters and status. Click Login and enter the correct 30-digit password before modifying the parameters.

## 12.8 Recovery 🎧 Factory

Restore the parameters that come with the 🎧 Factory Program BIN file.

## 12.9 Open CAN

Turn on the CAN analyzer, connect the controller, and debug.

## 12.10 Close CAN

Shutting down the CAN analyzer

# 13 Data copy

Batch view and adjustment of controller data and CAN bus data for Hxx and above:

## 13.1 Get controller data

1. Batch Download Parameters button on the right: Opens the Batch Download Parameters window. Click "Get controller data".
2. The CAN protocol format parameters within the controller can be displayed in the dialog box.
3. Tap the Cancel button to return to the main menu.
4. Save your own controller parameter file by clicking on the main icon in the upper left corner and selecting Save as heb file.

## 13.2 Download heb data

1. Connect the controller, open the host computer, click the main icon in the upper left corner, select Open a "heb" file (e.g. GX72400_13_A.heb), and the 🎧 dialog box will pop up automatically.
2. Tap "Data Download to Controller", you can see the matching number progress bar gradually full frame, the controller will prompt the alarm sound, tap "Controller Write and Reset", the controller data according to the new data to work.
3. Tap Cancel to exit the 🎧 dialog box.

## 13.3 CAN protocol data

### 13.3.1 CAN control

#### 13.3.1.1 Data format

CAN data segment information byte location map:

```
Bits   7  6  5  4  3  2  1  0
---------------------------------------------
Byte1  7  6  5  4  3  2  1  0
Byte2 15 14 13 12 11 10  9  8
Byte3 23 22 21 20 19 18 17 16
Byte4 31 30 29 28 27 26 25 24
Byte5 39 38 37 36 35 34 33 32
Byte6 47 46 45 44 43 42 41 40
Byte7 55 54 53 52 51 50 49 48
Byte8 63 62 61 60 59 58 57 56
```

Example of sending sequence:  
BYTE:1, 2, 3, 4, 5, 6, 7, 8  
bit:7 6 5 4 3 2 1 0, 15 14 13 12 11 10 9 8, ..., 63 62 61 60 59 58 57 56.

Data format: INTEL/MOTOROLA two optional, according to the protocol requirements to choose.

INTEL format: small end mode.

```
Bit     7   6   5   4   3   2   1   0
-------------------------------------
Byte1 The The The The The The The LSB
Byte2 MSB The The The The The The The
Byte3   -   -   -   -   -   -   -   -
Byte4   -   -   -   -   -   -   -   -
Byte5 The The The The The The The LSB
Byte6   -   -   -   - MSB The The The
Byte7   -   -   -   -   -   -   -   -
Byte8   -   -   -   -   -   -   -   -
```

Conversion example:

RPM=4000RPM, physical signal value=precision*signal logic value+bias, precision=0.25, bias=0; then hexadecimal is 0x3E80(16000d), message BYTE1=80H,BYTE2=3EH

MOTOROLA Format: Big End Mode:

```
Bit     7   6   5   4   3   2   1   0
-------------------------------------
Byte1 MSB The The The The The The The
Byte2 The The The The The The The LSB
Byte3   -   -   -   -   -   -   -   -
Byte4   -   -   -   -   -   -   -   -
Byte5   -   -   -   - MSB The The The
Byte6 The The The The The The The LSB
Byte7   -   -   -   -   -   -   -   -
Byte8   -   -   -   -   -   -   -   -
```

Conversion example:

RPM=4000RPM,physical signal value=precision*signal logic value+bias,precision=0.25,bias=0;then hexadecimal is 0x3E80(16000d),message BYTE1=3EH,BYTE2=80H

#### 13.3.1.2 Receive frame type

Selectable standard frame, extended frame

#### 13.3.1.3 Send frame type

Selectable standard frame, extended frame

#### 13.3.1.4 SOP_ID,SOP unit, SOP high byte position, SOP low byte position

* BMS Maximum Allowable Discharge Current Value, 2 bytes representation.
* SOP_ID: ID number of the SOP instruction.
* SOP unit: Generally set to 0.1A, or 0.25A or 1A. SOP high byte position (0-7 corresponds to BYTE1-BYTE8)
* SOP Low byte position (0-7 corresponds to BYTE1-BYTE8)
* SOP value = (value of SOP high byte position * 256 + value of SOP low byte position) * SOP unit (A).

#### 13.3.1.5 SOC_ID, SOC Location

The current power percentage value of BMS, full power=100, no power=0. SOC_ID: ID number of SOC command.

SOC Position: 0-7 corresponds to BYTE1-BYTE8.

#### 13.3.1.6 Charge ID, Charge Byte Position, Charge Bit Position

Charge ID: ID number of the charge command.

When both the byte position and the Bit position are 0, stopping occurs as long as there is an ID number. When the position is not 0, it stops when the position is set to 1.

#### 13.3.1.7 Side Stand ID, Side Stand Byte Position, Side Stand Bit Position

Side Stand ID: The ID number of the edge support command.

Set to 1 when the side stand down to disallow traveling, and set to 0 when the side stand is up to allow traveling.

In the case of a dual battery system, this ID is the charging anti-running ID of the second battery, the contents of which are the same as in 12.3.1.6.

#### 13.3.1.8 3-Speed ID, 3-Speed Byte Position, 3-Speed Bit Position

3-Speed ID: ID number of the 3-speed command.

The three speeds total 2 positions, 0 for 1st gear speed, 1 for 2nd gear speed, 2 for 3rd gear speed, and 3 for 4th gear/boost speed. The low position of the three speeds is in the specified Bit position and the high position is in the Bit+1 position.

#### 13.3.1.9 Gear ID, Gear Byte Position, Gear Bit Position

Gear ID: ID number of the gear command. Note that the gear control is used and the reverse is fast.

The gears have a total of 2 positions, 0 for N, 1 for forward and 2 for reverse. The low position of the gear is in the specified Bit position, and the high position is in the Bit+1 position.

#### 13.3.1.10 Control ID, control type, control byte position

Control ID: The ID number
of the control command.

Control Type:

|sports event|==1|==0|
|---|---|---|
| BIT0 | +1: Unmanned display | +0 Other items shown
| BIT1 | +2: Serial number | +0 Error log
| BIT2 | +4: Separate display for low/high speed | +0 Normal 3-speed display
| BIT3 | +8: Display of laps | +0 Display total mileage
| BIT6-BIT4 Special Control | 0=+0: unmanned 9  <br /> 3=+48: Unmanned 59 <br />6=+96: Dual battery system <br /> 7=+112: Dual battery systems - TCSID| 1=+16: ZN/YJ Calculation of SOC based on BMS residual battery capacity<br />2 = +32: total mileage handshake<br />4=+64: Feedback on demand<br />5=+80: TCS-ID
| BIT7 | =+128 Display current mileage | Display of remaining mileage

On-demand commands: 12, 13, 14, 15 correspond to Send ID2, Send ID3, Send ID4, Send
ID5 respectively.

In a dual-battery system, this control ID is the SOPID of the second
battery, the content is the same as 12.3.1.4, and the SOC ID of the second
BMS is the same as this ID.

#### 13.3.1.11 OBD_ID

OBD ID number, standard frame is 0x7DF.

### 13.3.2 CAN Transmit ID

The controller has set up 6 ID numbers to send data.

Send ID0-ID5 timer is the timing count in units of 10ms:

* `0` = 10ms
* `1` = 20ms
* `2` = 30ms
* ...
* `199` = 2000ms

Send ID2-ID5 timer must be >=4 i.e. 50ms. If it is less than 4, it will be sent on demand according to the command received by CAN.

### 13.3.3 CAN Rule Description

The CAN send content consists of 21 data, 17 status and 14 alarm messages. Each
content includes the following definitions:

#### 13.3.3.1 Length

It refers to the number of BITs required for the data. For example, speed,
current and voltage are usually 16 bits, gear position is 2 bits and alarm status is usually 1 bit.

#### 13.3.3.2 Placement

For the position of the LSB of this data in the CAN frame, see the "CAN Data Segment Information Byte Position Diagram" above.

#### 13.3.3.3 gain (electronics)

The coefficients * are required for this data. Default gain = 1

1. Customer code, serial number, hardware version, software version: gain=1
2. Current voltage unit 0.1V, gain = 1
3. Current current unit 0.1A, gain = 1
4. Current phase current unit 0.1A, gain = 1
5. Throttle opening, gain = 1
6. Throttle voltage unit 0.01V, gain = 1
7. Current torque unit = 0.1Nm, gain = 1
8. Current speed, gain = 1
9. Current RPM unit = 1RPM, gain = 1
10.  Total distance traveled 16 digits higher, unit=0.1Km, gain=1
11.  Total distance traveled 16 bits lower, unit=0.1Km, gain=1
12.  Current mileage unit = 0.1Km, gain = 1
13.  Controller temperature in °, gain=1, bias=40
14.  Motor temperature in °, gain=1, bias=40
15.  Battery level in %, gain=1
16.  Status, Alarm: Gain = 1

#### 13.3.3.4 ID

ID of this data transmission (0-5, corresponding to CAN transmission ID0-ID5)

#### 13.3.3.5 Valid Flag

* Valid (1): This data is reported to the CAN bus in the specified BIT, BYTE position. 
* Invalid (0): This data is not reported on the CAN bus.

#### 13.3.3.6 Bias

Temperature bias 40, other default bias = 0:

1. Controller temperature in °, gain=1, bias=40
2. Motor temperature in °, gain=1, bias=40

## 13.3.4 CAN Data

There are a total of 21 data items that the user can choose to report or not report:

| sports event | Element | Size |
|---|---|---|
| 1 | client code | 2 letters
| 2 | Sequence number 0 | 16-bit digital
| 3 | Sequence number 1 | 16-bit digital
| 4 | Serial Number/Error Code | 16-bit: according to the control word
| 5 | hardware version | 8-bit
| 6 | Software version 0 | 8-bit
| 7 | Software Version 1 | 8-bit
| 8 | input voltage | 16-bit
| 9 | amps | 16-bit
| 10 | phase current | 16-bit
| 11 | Throttle opening/control data | 8/16-bit, driverless project display control data
| 12 | Throttle voltage/control command | 16-bit, driverless project display control commands
| 13 | torsion | 16-bit
| 14 | current velocity | 16-bit
| 15 | current speed | 16-bit
| 16 | Total mileage/laps High 16 digits | 16-bit: according to the control word
| 17 | Total mileage/laps Low 16 digits | 16-bit: according to the control word
| 18 | Current Mileage / Remaining Mileage | 16-bit: according to the control word
| 19 | Controller temperature | 8-bit
| 20 | Motor temperature | 8-bit
| 21 | current level | 8-bit

## 13.3.5 CAN status:

There are a total of 17 statuses that the user can choose to report or not report:

| sports event | Element | Size, Notes |
|---|---|---|
| 1 | gear level (i.e. first gear, second gear) | 2 bits <br /> SEC3=1: P send 0, reverse send 1, neutral send 2, forward send 3 SEC3=2: reverse send 3, neutral send 2, forward send 1 <br /> SEC3 = Other: neutral = 0, forward = 1, reverse = 2.
| 2 | Three speed status | 3 digits: Low/high speed status according to the control word (ZN) gear display, <br />SEC1=1 high speed low speed reverse display SEC1=2: 123 backward, BST,P gear display <br />SEC1=3:Neutral 0, gear display = 1, 2, 3 <br /> SEC1=4:Neutral 0, Reverse 5, Gear display 2,3,4 (H62) <br /> SEC1=5:Neutral 0, Reverse A, Gear 1,2,3 <br /> SEC1=6:Neutral 0x20,Reverse 0x80,Forward 0,1,2 <br /> SEC1=7:Neutral 0,Reverse 3,Medium 0,Low 1,High 2 <br /> SEC1=other: gear display=0,1,2
| 3 | brake condition | 1 bit
| 4 | cruise state | 1 bit
| 5 | pedestal state | 1 bit
| 6 | edge support sth. | 1 bit
| 7 | speed limit | 1 bit
| 8 | restoration status | 1 bit
| 9 | Backward state/motor direction | 1 bit, unmanned program showing motor direction
| 10 | Boost status/direction of rotation |  1 digit, unmanned program display turning direction
| 11 | Push Status/Master Relay |  1 digit, unmanned program displays main relay status
| 12 | Parking P-gear status | 1 bit
| 13 | state of charge | 1 bit
| 14 | READY status | 1 bit, no alarm in gear can turn normally when light, turn off after turning. (CAN58 special: remains on after rotation)
| 15 | ECO state | 1 bit
| 16 | ABS status | 1 bit
| 17 | BOOST status | 1 bit

## 13.3.6 CAN Alarm

A total of 14 alarms, user can choose to report or not to report:

| sports event | Element | Size|
|---|---|---|
| 1 | Motor Hall Failure | 1 bit
| 2 | throttle failure | 1 bit
| 3 | brake condition | 1 bit
| 4 | MOS Failure | 1 bit
| 5 | phase line short circuit fault | 1 bit
| 6 | Phase line missing fault | 1 bit
| 7 | Controller over- temperature alarm | 1 bit
| 8 | Motor over-temperature alarm | 1 bit
| 9 | overcurrent alarm | 1 bit
| 10 | overpressure alarm | 1 bit
| 11 | undervoltage alarm | 1 bit
| 12 | blocking and alerting | 1 bit
| 13 | anti-theft alarm | 1 bit
| 14 | Controller Alarms | 1 bit

# 14 Controller Model Description

Example: ND72530B_13_ARH68

* Customer code (AA-ZZ): `ND`
* Rated voltage (V): `72`
* Maximum phase current (A): `530`
* Type (B for encoder version, otherwise Hall version): `B`
* `_`
* Current sensor type (1-9): `1`
* Application type (0-9): `3`
* `_`
* Function code (0-9, A-Z): `A`
* Extension code (*, 0-9, A-Z): `R`
* Hardware version (0-9, A-Z): `H`
* Software version (00-99): `68`
