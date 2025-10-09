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