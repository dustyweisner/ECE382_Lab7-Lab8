ECE382_Lab7-Lab8
================

Robot Sensing and Robot Maze


__*Lab 7 "Robot Sensing"*__


Required Functionality  
Use the ADC subsystem to light LEDs based on the presence of a wall. The presence of a wall next to the left sensor should light LED1 on your Launchpad board. The presence of a wall next to the right sensor should light LED2 on your Launchpad board. Demonstrate that the LEDs do not light until they come into close proximity with a wall.

B Functionality  
Create a standalone library for your ATD code and release it on Github. This should be separate from your lab code. It should have a thoughtful interface and README, capable of being reused in the robot maze laboratory.

A Functionality  
Since each robot's sensors are a little bit different, you need to fully characterize the sensor for your robot. Create a table and graphical plot that shows the ATD values for a variety of distances from a maze wall. This table/graph must be generated for each IR sensor. Use these values to determine how the IR sensors work so you can properly use them to solve the maze.


__Prelab__  
To begin the lab I decided to include information from this lab I thought will be useful in creating my program. I started with the software part of it. I thought of the following pseudocode for the required functionality:

    if (leftWall <= CLOSE_PROXIMITY) {
      P1OUT |= BIT0;
    } else {
      P1OUT &= ~BIT0;
    }
      
    if (rightWall <= CLOSE_PROXIMITY) {
      P1OUT |= BIT6;
    } else {
      P1OUT &= ~BIT0;
    }

The variables, `leftWall` and `rightWall`, will be constantly updated by the sensors. This is where I transitioned into testing the sensors to see if they worked. I used a DMM to measure the voltages at certain distances:

|DISTANCE|VOLTAGE|
|:--|:__:|
|||
|||
|||
|||
|||
|||
|||

Then I considered how I would set up the ADC10 subsystem (Analog-to-digital Conversion) :

      1. ADC10ON and interrup enable
      2. Select input channel to be A4, according to device specific data
      3. Enable A4 for analog input
      4. Select ADC10 clock - probably SMCLK
      5. Set the output direction for the LED1
      6. Set the Output direction for LED2
      7. Make a while loop that includes:
        a.Sampling and conversion
        b. ISR force exit

After that, I included inside the main loop the pseudocode from above that turned on the lights. 
