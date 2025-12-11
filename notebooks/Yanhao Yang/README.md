# Yanhao Worklog
# 2025-09-18 - Discussion with Professor Kumar and Gayatri
After our discussion with Professor Kumar and Gayatri, we now have a well-defined project roadmap. Our next step is to accurately calculate the torque required to lift a 2 lb load so we can select suitable servos and motor drivers. This calculation is essential to ensure the lifting mechanism provides sufficient power during competition.

Battery selection is another key consideration : we need to balance size and weight while ensuring enough capacity to power the robot for the full 2-minute battle. The battery must reliably sustain both general operation and the energy needed for lifting opponents without depleting mid-match.

Professor Kumar highlighted that our robot doesn't need high speed to succeed. Instead, our main strategy should center around using the shovel mechanism to flip opponents. He advised us to define our win condition clearly and design our system around achieving that specific goal. I also discussed potential structural designs and strategies for implementing current control with him.
# 2025-09-23 - Discussion about PCB

After the proposal review of our Ant-Weight BattleBot project, our team began discussing how to design and document the electrical schematics for each subsystem on the printed circuit board (PCB). We decided to divide responsibilities among the key modules-such as the power distribution, control logic, sensor interface, and drivetrain subsystems. I was assigned to focus specifically on the drivetrain, which primarily involves the design and implementation of the H-bridge motor driver circuitry. To begin this task, I selected the DRV883RTY motor driver IC as the candidate component. My next step is to carefully review its datasheet to understand its operating characteristics, pin configuration, current-handling capabilities, and recommended layout guidelines. This analysis will help ensure that the H-bridge design meets the drivetrain's performance and thermal requirements while remaining compact and efficient for the overall PCB integration.



# 2025-09-30 - Schematics Updates

I designed the drivetrain subsystem using the dual H-bridge DRV 8833RTY, which can take 10.8 Voltages at maximum.

![](H_Bridge_Scheme.png)

[link](https://www.ti.com.cn/product/cn/DRV8833)

This means that we need to design buck converters for it: Our raw input is 12 V since we are using 450mah 3s Lipo Battery

We also need to start thinking about integrating different subsystems on our schematics.

# 2025-10-09 - Whole Schematics

Getting the microcontroller subsystem schematic and 3.3V buck converters from Mig, I added two more buck converters using LM2596 adjustable version, since 10.8V for Hbridge and 6 V for servo motors are not standard output of voltage regulators.
![](whole_scheme1.png)

The choices of resistors and other parameters in designig these buck converters take reference from this:
![](LM2596.png)

# 2025-10-12 - Complete First Version of PCB

According to the whole schematic, designed the whole PCB and there are some issues when running DRC on it, including isolated islands, hole sizes.
![](First_PCB.png) 

# 2025-10-16 PCB Orders Sent

Debugged previous problem by adding vias and rerouting, created second version PCB that fits 100mm*100mm and place orders of it.
![](Second_PCB.png)

# 2025-10-21 BlueTooth Control

To implement the Bluetooth control, I start from implementing and testing out giving command to ESP32 to move backward and forward for this motor 
![](test_motor.jpg)

I started with application Bluetooth_Serial_Terminal to give command to ESP32 and uses Arduino code to program the ESP32 Dev Board. To ensure safety of the bluetooth connection, I set up a code that I have to put in before I give any commands. Since ESP32 Bluetooth module doesn't really support code matching,it will automatically connected to any device, I use the code logic that if the first thing I sent after connection is not the password, disconnect automatically. The result looks pretty good

![](BL_Password.jpg)

Move Forward and Move Backward implemented successfully:

![](motor_bl.jpg)

![](BlueTooth_1.jpg)

The issue is that the motor keeps moving forward or backward continuously until I send a command to reverse or stop it. I want to control it like a car where, if I don't give any command for a moment, it automatically stops.

# 2025-10-22 BlueTooth Control(Time)

I updated the code to include time-based control. In the loop(), if no meaningful command is received within 300 ms, the system stops automatically. This approach relies on streaming where the ESP32 continuously receives 1-byte commands. However, this makes using a password impossible because any noise can interfere, which is the trade-off for real-time control.

# 2025-11-04 PCB soldering

We got PCB and started soldering it and we noticed that we lack some irregular resistor, capacitors SMD. I put orders through DigiKey
![](PCB1.jpg)

# 2025-11-10 PCB Tested

While some of our ordered components haven't arrived yet, we temporarily replaced them with through-hole versions so we can decide whether to submit a new PCB order for the fourth round. However, our buck converters failed the one intended to output 3.3 V gives 0.1 V, the 10.8 V output gives 12 V, and the 6 V output gives 4.3 V, but with reversed polarity.  
![](PCB_Soldered.jpg)
![](BC3.3.jpg)
![](BC10.8.jpg)
![](BC6.jpg)


# 2025-11-12 Second PCB Order

Considering the buck converter's failure, I rechecked the datasheet and think I used a capacitor meant for decoupling that was too large in value and polarized. It should be small and nonpolarized. I also removed the H bridge chip and used pins to connect with a mature module because the H bridge is too difficult to solder. Additionally, I left power pins available so if our buck converters don't work, we can use external power to boot and load our ESP32.
![](whole_scheme2.png)

# 2025-11-14 Battery Testing

We obtained an XT30 to JST adapter and a charger for our battery. We started powering the motors and modules on the breadboard using our own battery and tested it by running two wheels for 4 minutes. I believe this duration is sufficient to withstand a competition lasting 2 minutes.
![](Battery_Test.jpg)

# 2025-11-21 Mock Demo with Circuit on Breadboard
Before the fall break, we successfully assembled our BattleBot prototype using two small breadboards that housed all the core electronic components. The setup included the buck converters for voltage regulation, the ESP32 development kit for control and communication, and DRV8871 H-bridge motor drivers to power the drivetrain. We chose the DRV8871 over the DRV8833RTY after comparing their specifications, as the DRV8871 can handle a direct 12 V input—making it more suitable for our power system and overall design simplicity. Initial functionality tests confirmed that the system performs as expected, with stable motor control and reliable power delivery.

During this stage, Gayatri provided several useful suggestions for mechanical improvements, particularly regarding the 3D-printed chassis. She recommended using screws or standoffs to secure and align the top plate with the main chassis, instead of relying on tapes, to enhance structural stability and durability during matches.

Our next major task is to transition the entire circuit from the breadboard prototype to a custom PCB. This step will help minimize wiring complexity, reduce connection noise, and enable a more compact and robust integration with the mechanical frame of the BattleBot.
![](mockdemorobot.jpg)
![](breadboardd.jpg)

# 2025-11-27 Transition from Breadboard to PCB
Since the traditional PCB footprint used in the ESP32 DevKit is not compatible with the newer ESP32-S3 module, we updated our control firmware to ensure compatibility, particularly by transitioning the existing Bluetooth communication code to Bluetooth Low Energy (BLE). After successfully porting the code, we proceeded to assemble all components onto the custom PCB. Initial electrical tests showed that all voltage outputs were within the expected range, and the circuit appeared to function correctly under no-load conditions.

However, during real-world testing, we observed a significant voltage drop across the ESP32-S3 when the servo motor was activated. The supply voltage to the ESP32 would temporarily fall below the 3.3 V threshold, triggering an automatic reset of the microcontroller. This issue indicated that the power distribution network was unable to maintain stable voltage levels when both the servo and the ESP32 drew current simultaneously.

To mitigate this problem, I temporarily reintroduced a breadboard connection to isolate and stabilize the power lines. By wiring the servo and ESP32 in parallel power rails, the voltage fluctuations from the servo no longer interfered directly with the microcontroller's supply. This adjustment successfully prevented unintentional resets, allowing the system to operate more reliably during integrated testing.
![](final%20pcb.jpg)

# 2025-12-03 Final Demo
After ensuring that all internal electronics were fully functional, we began assembling the system using our 3D-printed mechanical components. Our initial setup weighed only about 1 lb-well below the 2 lb weight limit-so we added screws to the rear of the BattleBot to increase mass and counterbalance the front-heavy servo motor.

During assembly, we encountered an issue with the wheels: the toy wheels purchased online did not fit securely onto the motor shafts, and the original 3D-printed adapters lacked sufficient strength to handle impact during battles. To address this, we redesigned and 3D-printed custom wheels that directly interfaced with the motor shafts, reinforcing them with hot glue for added stability. To improve traction and handling, we wrapped the wheel surfaces with electrical tape, creating effective makeshift tires.

Our first shovel prototype also failed during testing, as it concentrated stress at a single joint. We redesigned the shovel to better distribute mechanical loads across the structure, significantly improving durability. After completing these mechanical revisions, we performed a full system test and confirmed that the BattleBot satisfied all key design requirements. It could sustain continuous operation for more than two minutes and demonstrated sufficient resilience for competitive combat.

Most verification tests were conducted through direct observation or simple measurements. Mobility and movement capabilities were verified visually, while the lifting mechanism was tested using everyday objects-phones and water bottles-totaling 2 lbs. We used a ruler to measure the shovel's height from the ground and a timer to record the servo's actuation time. For control performance, we measured response delay by recording a video and analyzing it at one-quarter speed. The observed delay in the slowed footage was under one second, confirming the system's true latency was below 250 ms. We also validated remote control functionality up to a 5-meter range. For mobility assessment, we measured distance traveled versus elapsed time using a ruler and timer, and recorded the robot's total operational duration during combat tests. Finally, we used a voltmeter to confirm proper voltage supply across all major components.

Our final record was 2 wins and 1 loss. Here is a link to the highlights of our battles: https://drive.google.com/file/d/1RE8FONN-sFi-dEDkxu0kXL-BYywnTr4P/view?resourcekey
![](finalchasis.jpg)
![](finalbot.jpg)


