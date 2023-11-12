
# Obstacle Avoiding Car System 

## Overview

This document provides an in-depth explanation of the robot control system, which is built using various hardware components including the ATmega32 microcontroller, ultrasonic sensor, buttons, LCD display, H-bridge, and motors. The system's primary function is to control the robot's movement and behavior based on different scenarios and obstacle detection.

## System Testing Video
Watch the system testing video : [System Testing Video](https://drive.google.com/file/d/1bo7xG_WeI8JDQTjQS5LrowVHpT8kMMwb/view?usp=sharing)

## Hardware Components

The following hardware components are integrated into the robot control system:

- ATmega32 Microcontroller
- Ultrasonic Sensor
- Buttons (PB1 and PB2)
- LCD Display
- H-Bridge Motor Driver
- Motors

## Functionalities

### Default Rotation

1. Upon startup, the robot defaults to rotating in a rightward direction.
2. Pressing PB2 initiates or halts the robot's actions.
3. After the "start" command, the LCD displays the message "Set Def. Rot." in line 1.
4. The robot waits for 5 seconds to determine the rotation direction: right or left.
5. Pressing PB1 toggles the default rotation between left and right.
6. After the 5-second interval, the robot adopts the chosen default rotation.

### Movement Control

1. The robot begins movement 2 seconds after setting the default rotation.
2. If there are no obstacles within 70 centimeters:
   - The robot moves forward at 30% speed for 5 seconds.
   - The LCD displays speed and direction on line 1.
3. Following the initial 5 seconds, the robot maintains 50% speed while ensuring obstacles remain over 70 centimeters.
4. The LCD displays speed and direction on line 1, and object distance on line 2.

### Obstacle Detection

1. For obstacles situated between 30 and 70 centimeters:
   - The robot's speed is reduced to 30%.
   - LCD information is updated.

2. Obstacles within the range of 20 to 30 centimeters:
   - The robot halts and rotates 90 degrees in either direction, depending on configuration.
   - LCD information is updated.

3. Obstacles closer than 20 centimeters:
   - The robot stops and moves backward at 30% speed until the distance is within 20-30 centimeters.
   - LCD information is updated.
   - The robot then repeats this process.

4. In case of obstacles surrounding the robot:
   - If a full 360-degree rotation reveals no obstacles beyond 20 cm, the robot stops.
   - The robot periodically checks for obstacle removal, moving toward the furthest object every 3 seconds.

## Setup and Usage

### Hardware Connections

1. Connect the ultrasonic sensor to the appropriate microcontroller pins.
2. Attach buttons (PB1 and PB2) to designated microcontroller pins.
3. Connect the LCD display to the microcontroller to enable information display.
4. Establish connections with the H-bridge to facilitate motor control.
5. Connect the motors to the H-bridge for proper motor functioning.

### Programming

1. Develop the necessary code to manage the ultrasonic sensor, buttons, LCD, and motors.
2. Implement the logic described earlier for default rotation, movement control, and obstacle detection.

### Usage

1. Power up the robot.
2. Use PB2 to start or stop the robot's actions.
3. Follow the LCD prompts to determine the default rotation direction.
4. The robot will execute movements based on predefined scenarios and obstacle detection.

## Author

[Ararfa Arafa Abd Elmawgod]

For questions or support, contact [Mail connection](arafa.prog.98@gmail.com).


Happy coding!
