# Yunhan Tian Worklog

# 2025-09-23 - Post proposal review

After the proposal review, we now have a general idea of our project. We want to build an antweight 3D-printing battlebot. As a group, we agreed that our battlebot will consist of 4 subsystems: the drivetrain subsystem, the weapon subsystem, the control subsystem, and the power subsystem. We agreed that our weapon system would be a shovel, trying to lift up the opponent's battlebot. We calculated the required torque for our weapon subsystem servo to be able to lift a 2lb weight. We calculated the battery requirement for our battlebot to last 2 minutes. We also determined the designed capacity, including the theoretical runtime, speed capacity, and the required torque. 

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/calculations.png)

# 2025-09-30 - PCB schematics

For the PCB design, I am responsible for the power subsystem design. The schematics I design consist of a buck converter converting 12V to 3.3V, providing a voltage supply for the control subsystem. I also added some circuit protection measures to prevent our PCB from being damaged by any unexpected current flow. We did not end up using my design, but it helps me keep track of our PCB design.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/power.png)

# 2025-10-06 - Breadboard demo 1

For the breadboard demo, we agreed that we want to show a drivetrain motor being controlled by commands. Since the purpose of this demo is to mimic a working PCB to some extent, we decided to use a development board to execute our Arduino code and a ready-to-use H-bridge chip to enable the motor, making the motor able to accept commands to change its spinning direction once we press a button, which corresponds with our battlebot going straight and going back. I was mainly figuring out the circuit wiring while Jimmy and Mig figured out a simple version of Arduino code for us to control the motor. 

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/demo1.png)

# 2025-10-12 - PCB v1 completed

We finished the first version of the PCB design.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/pcbv1.png)

# 2025-10-20 3D printing structure

We sent the PCB purchasing request. We decided that while Jimmy works on implementing the Bluetooth control, Mig and I can have our 3D printing structure ready for the upcoming breadboard demo 2. I designed the main structure, while Mig designed the shovel. We printed out everything, and they overall work expected.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/3dstr1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/3dstr2.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/shovel.png)

# 2025-10-28 - Breadboard demo 2

For breadboard demo 2, Jimmy successfully implemented the Bluetooth connection. We were also able to modify the code and make progress on expanding the control feature to 2 motors instead of 1, tuning the motor and the corresponding code to make turning directions possible, also the activation button, which needs a PWM signal, to control the weapon servo. We also realized that the 3D printing structures would require a lot more time than anticipated. We decided to split up the work. Jimmy and Mig would be working on the PCB soldering/testing/modifying, and I will be designing all 3D printing structures and improving through iterations. 

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/demo2.png)

# 2025-10-31 - 3D printing structure iteration 1

Because I realized that I would not be able to fit all the components(PCB, battery, motors, etc.) into the small hole reserved for the wheels of the sealed 3D printing structure we had, I performed the first iteration of the 3D printing structure, which I divided the whole structure into 2 subparts: the shell and the bottom plate. I also arranged the positioning space for the back wheels, battery, PCB, and the front drivetrain motors (PCB would be screwed to the top of the shell). I printed out the shell and the bottom plate, and they both worked as expected. I did not design the positioning hole for the weapon servo since I had a hard time picturing how the servo would work, and the servo did not arrive, so I did not have the exact dimensions of the servo. I decided to do that on the next iteration. 

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v1shell.png)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v1bottomplate.png)

# 2025-11-04 - Group communication

During our group meeting, I updated Jimmy and Mig about iteration 1, and I learned that the PCB had arrived, and they had soldered the components and would be testing it. Also, the servo motor arrived, and I got the dimensions of the servo and had a better understanding of how the servo functions.

# 2025-11-08 - 3D printing structure iteration 2

With the new servo information, I added the position hole on the bottom plate for the servo. I redesigned our shovel since we agreed that the original shovel was too big and was not strong enough. I mounted 2 holes on the shovel stick to ensure the screws could pass through and connect with the servo motor arm. I also designed a converter for the connection between the drivetrain motor and the wheels since the shaft hole on the wheels was too small to fit our drivetrain motor. I printed out everything I redesigned and found out that the dimension information given is incorrect; the servo will not fit the position hole. The converter was also too small on the motor side. The shovel works as expected.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v2.png)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v2con.png)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v2shovel.png)

# 2025-11-16 - 3D printing structure iteration 3

I realized that we needed the shovel to be touching the ground for it to be able to lift anything. After I fixed the known issue from iteration 2, I made the position hole even deeper down the bottom plate. I also created an additional space in the front for the servo arm to extend without making contact with any other components. Additionally, I made the shovel shorter and narrower to enhance torque. I printed out everything and tested it. They all worked as expected.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v3-1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v3-2.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v3-3.jpg)

# 2025-11-19 - 3D printing structure iteration 4

I realized the space reserved for the drivetrain motors is not compatible with our motors, so I made an adjustment to the bottom plate.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v4.png)

# 2025-11-21 - Mock demo assembly 

For the mock demo, since the newly designed PCB had not arrived yet, we decided to build a prototype using a breadboard that consisted of chip modules such as the ESP32 development board, the Adafruit H-bridge module, and the 3.3V and 5V buck converter module. The built prototype showed all functionalities worked as intended.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/mockdemo1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/mockdemo2.jpg)

# 2025-11-27 - 3D printing structure iteration 5

I followed the advice given by our TA during the mock demo that we might want to improve the professional packaging aspect of the design. As a result, I added some screw holes on all the edges of the shell. I also made the drivetrain converter bigger. I also made some changes to the shell PCB position space because it has some conflicts with our new PCB. 

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v5-1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v5-2.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/v5-3.png)

# 2025-11-29 - Final demo assembly

We assembled everything with the newly arrived PCB. We noticed that the code that was working on the development board was no longer working. We found out that it was because the defined PIN in the PCB design did not correspond to the same GPIO pin in the code. I also found that our PCB had some issues with the power distribution. We had to put a buck converter module in parallel with the PCB to resolve the problem. We tested everything, and they all worked as expected except that we could not remove a screw connecting the servo arm and the shovel, making the shovel non-functional.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/final1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/final2.jpg)

# 2025-12-02 - Final demo preparation

We ended up going to the machine shop for help, and they removed the screw for us. Mig also redesigned the front wheels, so we no longer needed the converter(the converters were easy to break). We reassembled our battlebot, and all components worked as expected. We were ready for the final demo.

![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/ready1.jpg)
![Alt text](https://github.com/YanhaoYang2/ECE-445-notebooks/blob/main/notebooks/Yunhan%20Tian/ready2.jpg)
