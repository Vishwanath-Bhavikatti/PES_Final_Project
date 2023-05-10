[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10386395&assignment_repo_type=AssignmentRepo)
# Course: Principle of Embedded Software - ECEN 5813 (Spring 2023)
# Final Project: Temperature Monitoring System
## Author : Vishwanath Bhavikatti (vishwanathbhavikatti1310@gmail.com)
## Date : 05/02/2023

# Description: 
Temperature plays a critical role in day-to-day life hence monitoring a critical parameter is of utmost importance. 
This project implements a temperature monitoring system which basically uses an onboard temperature sensor connected to an ADC input of KL25Z dev board. Current temperature will be displayed on UART and LCD for real time monitoring. Also, this system gives some kind of alert to an user in the form of glowing an LED in the case of temperature crossing upper or lower threshold limits.

## Compiler Used:
`gcc (with -WALL and -WERROR Flags enabled)`
## IDE and Development board
<br> IDE: MCUXpresso IDE 11.6.1
<br> Development Board: MKL25Z
## Build Settings:
<br>Preprocessor setting: PRINTF_FLOAT_ENABLE=1
<br> Manage Linker Script : Heap size 0x3000
<br> Manage Linker Script : Stack size Default

## Video Demo Link:
https://drive.google.com/file/d/1SuLLLtdSTUkTbmVwKzfyeFWkAem_70r6/view?usp=share_link

## Proposed Objectives:
|  | Objectives | Status | 
| --- | --- | --- |
| 1 | Monitoring real time temperature using onboard temperature sensor in KL25Z board. | Done |
| 2 | Successfull Calibration of the sensor to receive the data in understandable formats.| Done |
| 3 |Configuring UART 0 to display temperature on terminal in both degree Celsius and degree Fahrenheit format| Done |
| 4 |Configuring 16 X 4 LCD to display temperature using Memory mapping technique | Done |
| 5 |Setting upper and lower temperature thresholds and glowing LEDS accordingly to alert an user about the temperature variation | Done |

## Block Diagram:
<p align="center">
    <img width="800" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/Block_Diagram.png" alt="Block Diagram">
</p>

## Technologies used in this project:
<br>▪ Embedded Temperature Sensor on KL25Z dev Board
<br>▪ GPIO lines
<br>▪ Interrupts
<br>▪ UART
<br>▪ ADC
<br>▪ 16 X 4 LCD Module interfacing

## More about Embedded Temperature Sensor:
The ADC module has a P-N transistor junction with temperature dependent properties acting as an embedded temperature sensor. The voltage across this junction rises or lowers with temperature allowing silicon to act as a temperature sensor.

## Algorithm to calibrate temperature: 
Using the typical parameters provided by the HCS08 data sheet to perform a temperature reading. An approximate transfer function describes the temperature sensor.
<p align="center">
    <img width="700" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/Algorithm.png" alt="Algorithm">
</p>
<p align="center">
    <img width="700" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/Flow_chart.png" alt="Flow chart">
</p>

## Pin Mapping of LCD with KL25Z
| LCD | KL25Z | External connection  |
| --- | --- | --- |
| GND | GND |  |
| VCC | 5V | |
| V0 |  | external resistor pot |
| RS | PTC 10 | |
| R/W | PTC 6 |  |
| E | PTC 5 |  |
| DB4 | PTC 4 |  |
| DB5 | PTC 3 |  | 
| DB6 | PTC 0 |  |
| DB7 | PTC 7 |  |

## Results:
### LCD Display:
<p align="center">
    <img width="800" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/LCD.png" alt="Block Diagram">
</p>

### UART Terminal Image:
<p align="center">
    <img width="400" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/UART_setting.png" alt="Block Diagram">
</p>

<p align="center">
    <img width="800" src="https://github.com/ECEN5813/final-project-Vishwanath-Bhavikatti/blob/main/Screenshots/uart.png" alt="Block Diagram">
</p>

## Testings Carried
<br>▪ Initially once the ADC is configured to read analog temperature value. I calibrated using the above mentioned algorithm to see whether I get the proper temperature values. 
<br>▪ I didn't get the accurate readings even after calibration but my temperature sensor was responding to different temperature cases that is if I bring cold conditions it would decrease the values and if I bring the board the temperature would increase. So I added a proper offset value to the calibrated temperature to set a realtime temperature reading.
<br>▪ After integrating LCD part I did a regressive trials to get the display to work as required. Initially my memory mapping was wrong so I was not getting any output on LCD Pixels. After understanding the initialization of LCD properly with respect to memory mapping I was able to print Hello world. Next I wrote LCD write Int function to write integers on the LCD display.
<br>▪ After Integrating UART, LCD and ADC I checked temperature reading on both UART and LCD by introducing different temperature conditions.

## Key Learnings:
<br>**Optimizing the Temperature Sensor:**  
<br>**1.Analog-to-digital Configuration**
<br> Configure the analog-to-digital for long sample time and a maximum of 1MHz ADC CLK. Use a MCU low power mode to do an analog-to-digital reading. Wait or preferably stop mode reduces the effect of internal MCU noise on the temperature sensor reading.
<br>**2. Averaging ADC readings as demonstrated in the Processor Expert example** 
<br>Averaging is the most basic of digital filtering techniques and can reduce the effect system noise on ADC readings. This smooths the temperature sensor input and increases the effective resolution of the analog-to-digital converter.
<br>**3. Determine a current reading of VDD by using the bandgap voltage to calculate VDD**
<br>Using a current value of VDD more accurately represents VTEMP25 and VTEMP. This leads to a
better result for the approximate transfer function.
<br>**4. A floating-point implementation**
<br> Floating-point implementation results in more accurate math when using the approximate
transfer function if you can spare the code space.

<br>▪**Interfacing ADC to collect real time analog signal from any kind of sensor.**
<br>▪**Interfacing 16 X 4 LCD using Memory mapping technique**

## Challenges Faced:
<br>▪ While Interfacing LCD initially I thought it can be done easily as I used the same LCD for my Embedded System Design class. But while implementing I understood this LCD module DDRAM interface depends on Processor. As I did for 8051 controller so I need to understand how to carry out LCD initializations for ARM board.
<br>▪ Calibration of temperature reading from ADC.

## What would I do differently:
<br>I would like to add gsm module so that a user can get message / alert when the temperature crosses limit, which would greatly help farmers growing citrus fruits on snowy mountains.
<br>Also I would like to add buzzer to beep in case of temperature crossing the range.
<br>I would use any temperature sensor with SPI based communication protocol.

