# IMT_AVR_GRADUATIN_PROJECT

## *Brief :*
<p style="font-size: 20px; line-height: 1;"> this project was carried out as a fulfillment of the graduation project of the embedded systems AVR diploma at IMT to apply theoretical knowledge practically.</p>
<p style="font-size: 20px; line-height: 1;"> All drivers for all peripherals and components were implemented from scratch.</p>
<p style="font-size: 20px; line-height: 1;"> The project was implemented in 3 layers and 1 sub-layer.</p>
1. <strong>Micro Controller Abstraction Layer (MCAL): </strong> includes drivers for all the used peripherals. <br>
2. <strong>Hardware Abstraction Layer (HAL): </strong> includes drivers for all the used components.  <br>
3. <strong>Application Layer : </strong> includes Application Code. <br>
- <strong>Libraries Layer: </strong>includes libraries shared across the previous 3 layers. 

## Used Software:
- <p style="font-size: 20px; line-height: 1;"><strong>Eclipse IDE:</strong> for programming the microcontrollers.</p>

## Used Components:
1. <strong>Atmega32 microcontroller (x2).</strong>
2. <strong>NRF24L01 Radio Transceiver (x2).</strong>
3. <strong>Infrared Sensors (x2).</strong>
4. <strong>L298N H-Bridge (x1).</strong>
5. <strong>DC Motors (x2).</strong>
6. <strong>HC05: Bluetooth Module (x1).</strong>
7. <strong>Pusbuttons (x4).</strong>
8. <strong>Leds (x4.)</strong>
9. <strong>MPU6050 gyroscope sensor (x1).</strong>
10. <strong>Ultrasonic Sensor (x1).</strong>
11. <strong>Servo Motor (SG90) (x1).</strong>

## Used Atmega32 Peripherals:
1. <strong>DIO.</strong>
2. <strong>TIM0, TIM2 for dc motors speed control.</strong>
3. <strong>TIM1 for ICU used by ultrasonic sensor and Servo motor control.</strong>

## Used Communication Protocols:
1. <strong>UART.</strong>
2. <strong>SPI.</strong>
3. <strong>TWI (I2C).</strong>


## Project Description:
### The Project consists of two parts and four modes:


### First Part: 
#### <p style="font-size: 20px; line-height: 1;"><strong>Wireless Controlling Gloves:</strong> for switching the car mode through push-buttons and by sending specific commands through `NRF24l01` which uses `SPI` communication protocol.</p><br>
<p style="font-size: 20px; line-height: 1;"> Also used in Gesture Control mode to control the car movement (explained later)</p>

### Second Part: 
#### <p style="font-size: 20px; line-height: 1;"><strong>Wireless Controlled Car:</strong> that can operate in four modes (depending on the command received by the `NRF24l01` from the `glove`).</p><br>

### Four Modes:
1. #### 🔵 **Bluetooth Mode**: <p style="font-size: 20px; line-height: 1;">the `car` can be controlled using any `Bluetooth application` through `Bluetooth Module` which uses `UART `communication protocol</p><br>

2. #### 🔵**Line Following with Obstacle Avoidance Mode**: <p style="font-size: 20px; line-height: 1;">the `car` moves avoiding Obstacles (using the `Ultrasonic sensor` and the `servo motor`) until it discovers a black line, it then starts to follow that line using the `infrared sensors`</p><br>

3. #### 🔵**Grid Mode**: <p style="font-size: 20px; line-height: 1;">the `car` is initially placed on a specific square in a `3x3 line-following Grid` with squares numbered from `0 to 8`, using `Bluetooth Module`, by first sending an `ACK` command then sending the square number you want the `car` to go to, the `car` uses the `IR sensors` to move across the Grid towards the desired location.</p><br>

4. #### 🔵**gesture Control Mode**: <p style="font-size: 20px; line-height: 1;">Using the `glove`, the `car` moves according to the tilt angle of your hand in four directions, the `tilt angle` is determined through the `MPU6050` gyroscope sensor which uses `TWI` commnincation protocol</p><br>


#### 🔵 A python desktop app is provided for bluetooth communication.


![Capture](https://github.com/Omar-Said-4/IMT_AVR_GRADUATION_PROJECT/assets/87082462/43ad2a6d-ca17-4b41-a594-c2f722396e3c)

## Project Video: https://drive.google.com/file/d/1LozJLg4PEHOvtu7QN1vIt6a_RnGVHoAy/view?usp=drive_link

 

 
