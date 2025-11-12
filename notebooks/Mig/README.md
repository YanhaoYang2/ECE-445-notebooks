# Mig Worklog


# 2025-09-18 - Discussion with Professor Kumar and Gayatri

After meeting with Professor Kumar, we now have a clear roadmap for our project. We need to carefully calculate the torque required to lift a 2 lb weight and select our servo and motor driver accordingly. This calculation is critical to ensure our lifting mechanism has adequate power for the competition.
Battery selection requires careful consideration of both size and weight. The battery must have sufficient capacity to power the robot for the full 2-minute battle duration while maintaining enough energy to lift opponent robots. We'll need to calculate battery life to ensure it lasts throughout the entire match without running out of power.
Professor Kumar emphasized an important point about our strategy: our robot doesn't need to be fast or high-speed. Our winning strategy is to flip opponents using our shovel mechanism, so we should focus our design efforts on maximizing that capability. He also advised us to clearly identify our win condition and design around that objective.
Additionally, I spoke with Gayatri about where we can 3D print our battlebot structure, which will be an important next step in bringing our design to life.

# 2025-09-30 - Designing the Schematics and PCB

I am responsible for designing the control unit schematics. My design replicates the module layout as closely as possible, including boot and load buttons for code uploading. To address the voltage mismatch between the ESP32's 3.3V requirement and our 12V battery, I designed a buck converter using the LM2596S-3.3 module, chosen for its simplicity and fixed output. The schematics was designed with the circuit diagram from the datasheet as reference.

My initial design also incorporates a current sensor for stall detection. For programming, I opted for a 3-pin UART interface rather than an onboard USB-C port. In a battlebot application, reducing component count improves structural integrity and reliability. The board will expose only three programming pins, and we will upload code using an external UART-to-USB dongle. Additionally, I made sure that everything is connected and pass all electrical checks.

- Buck Converter: [LM2596S-3.3](https://www.digikey.com/en/products/detail/texas-instruments/LM2596S-3-3/3701219)

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/control_unit_schematics.png?raw=true)
![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/threevolts_buckconverter.png?raw=true)

# 2025-10-08 - Breadboard Demo 1

For our first breadboard demonstration, we acquired components from the available modules in ECEB 2070 and assembled a prototype. Since we have not yet received the components we ordered, such as the motors, servos, and buck converters, we used readily available components from the lab instead. While these substitute components are not fully compatible with our final design, they were sufficient for demonstration purposes.

I and Jimmy helped each other code a simple program to move the motor and allow it to turn using Adafruit H-Bridge module.

During the meeting, Professor Kumar provided valuable feedback on our design. He emphasized the importance of ensuring our robot is properly balanced and capable of effectively flipping opponents. He also suggested incorporating a self-righting mechanism in case our robot gets flipped during battle. Possible solutions include adding an additional set of wheels or designing the structure to be inherently unstable, making it easier to flip back upright.

Additionally, Professor Kumar noted that the current sensor may no longer be necessary. Instead, he recommended that we focus on monitoring the energy consumption throughout the match and tracking how much battery capacity remains to ensure our robot can operate for the full duration of the battle.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/breadboard1.jpg?raw=true)

# 2025-10-12 - First PCB Done

Jimmy combined individual subsystems of the schematics that we designed into one and route everything into one board.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/fullschematics.png?raw=true)
![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/routedpcb.png?raw=true)

# 2025-10-13 - Changes in components used

We realized that the components we initially planned to use were too expensive, thus in our design document, we looked for cheaper alternatives that still satisfy the requirements of the battlebots.

We are using Servocity's 508 RPM Mini Econ Gear Motor and DSSERVO 20KG Digital Servo instead.

- Motor Driver: [508 RPM Mini Econ Gear Motor](https://www.servocity.com/508-rpm-mini-econ-gear-motor/)
- Servo: [ANNIMOS 20KG Digital Servo](https://www.amazon.com/ANNIMOS-Digital-Waterproof-DS3218MG-Control/dp/B076CNKQX4)

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/motordriver.jpg?raw=true)
![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/servo.jpg?raw=true)

# 2025-10-17 - Designing the Battlebot 3D-Printed Structure

John and I collaborated on the mechanical design and 3D modeling using Tinkercad. The main chassis features a trapezoid-shaped body (24 cm long × 13 cm wide × 8 cm tall) with a wider base that lowers the center of gravity and increases stability against being lifted or flipped. The front incorporates a sloped wedge design to slide under opponents while deflecting attacks. The chassis includes a central cavity for the servo motor with full range of motion, plus cable routing channels for wire management.

The weapon shovel measures 16 cm wide (approximately 70% of the robot's frontal width) and consists of a 10 cm shaft connected to the servo and a 10 cm blade extending forward. To optimize the strength-to-weight ratio, I designed lightening holes throughout the blade, removing material from non-critical areas while maintaining strength near the servo attachment and leading edge.

We 3D printed an initial PLA prototype to verify component fitment. Testing revealed minor interference issues with motor mounting holes and PCB standoffs, which are being addressed in the current design iteration.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/shovelinitialdesign.png?raw=true)
![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/mainstructure.png?raw=true)

# 2025-10-24 - Breadboard Demo 2

For our second breadboard demonstration, we received some of the ordered components and made progress. We added Bluetooth functionality to enable wireless control and modified the code to support differential drive control with two motors for turning. We also integrated a servo with the 3D-printed structure we designed previously to test the feasibility of the weapon mechanism and verify proper fitment and operation.

# 2025-11-03 - PCB Arrived and Soldering

Our PCB and most of the components we ordered have arrived, allowing us to begin assembly. We initially started soldering by hand but later learned to use solder paste and a heat gun, which significantly simplified and accelerated the process. Soldering the ESP32 and DRV8833 chips proved particularly challenging due to their fine-pitch pins and tight spacing, making it very easy to create solder bridges between adjacent pads. We had to exercise extra care and precision when working with these components to ensure proper connections without shorts.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/barepcb.jpg?raw=true)

# 2025-11-09 - PCB Testing and Parts Replacement

Since some surface-mount components were unavailable, we substituted through-hole versions of capacitors, resistors, and inductors to save time, trimming their leads and soldering them directly to the board. We encountered adhesion issues with some solder joints, but flux greatly improved the results.
We systematically tested each subsystem using a multimeter for continuity testing (checking for bridges), voltage measurements (verifying buck converter outputs), capacitance and resistance measurements (validating component values), and diode testing (confirming correct placement and polarity).
Testing revealed that the buck converters were not functioning properly. The 3.3V converter produced little to no output, while the 5V converter output approximately 10.8V instead of 5V. We traced these issues to soldering defects where the board surface had peeled off and to errors in the schematic design.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/solderedpcb.jpg?raw=true)

# 2025-11-12 - Ordering the Second PCB

We revised our PCB design to simplify assembly by switching from the DRV8833 H-Bridge chip to an H-Bridge module, as the fine-pitch chip proved extremely difficult to solder reliably. We also made the power pins easily accessible on the board as a contingency measure, allowing us to use external power sources if the buck converters continue to malfunction.

Following Gayatri's recommendation, we ordered a solder paste stencil to improve the precision and consistency of our soldering process, particularly for surface-mount components.

![image alt](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Mig/secondpcbfullschematics.png?raw=true)