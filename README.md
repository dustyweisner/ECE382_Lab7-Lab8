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

*CENTER IR SENSOR* 

|DISTANCE (inches)|VOLTAGE (V)|
|:----|:-----:|
|no wall|<.6|
|12|.6|
|10|.65|
|8.25|.7|
|7|.8|
|6|.95|
|5|1.2|
|4|1.35|
|3|1.875|
|2|2.869|
|1|4.52|
|Touching|4.80|

*LEFT IR SENSOR*

|DISTANCE (inches)|VOLTAGE (V)|
|:----|:-----:|
|no wall|<.22|
|13|.258|
|12|.259|
|11|.266|
|10|.284|
|9|.293|
|8|.316|
|7|.330|
|6|.374|
|5|.439|
|4|.520|
|3|.647|
|2|.951|
|1|1.485|
|Touching|1.778|

*RIGHT IR SENSOR*

|DISTANCE (inches)|VOLTAGE (V)|
|:----|:-----:|
|no wall|<.6|
|13|.6|
|12|.616|
|11|.625|
|10|.65|
|9|.680|
|8|.720|
|7|.769|
|6|.860|
|5|.981|
|4|1.21|
|3|1.59|
|2|2.28|
|1|3.22|
|Touching|4.35|


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

__*Lab 7 "Robot Maze"*__

Pseudocode of how to make the robot go through the maze:

        // if leftWall is less than threshold,
        //      stop
        //      turn quarter right
        //      moveforward
        // if rightWall is less than threshold,
        //      stop
        //      turn quarter left
        //      moveForward
        // if rightWall is greater than moveZone
        //      stop
        //      turn right
        //      move forward
        // if frontwall is less than threshold 
        //      stop
        //      90 degree turn right
        // if frontwall is less than threshold

FIRST ATTEMPT:

    	if (rightValue() <= RIGHT_MIN && rightValue() >= RIGHT_MAX && frontValue() < FRONT_MAX) {
    			moveForward();
    		} else if (frontValue() >= FRONT_MAX) {
    			stopMovingForward();
    			if (rightValue() < RIGHT_MIN) {
    				moveLeft();
    			} else {
    				moveRight();
    				moveForward();
    				_delay_cycles(10000);
    			}
    		} else if (frontValue() < FRONT_MAX)  {
    			if(rightValue() >= RIGHT_MIN ) {
    				stopMovingForward();
    //				moveSmallLeft();
    				moveLeft();
    				moveForward();
    				_delay_cycles(1000);
    				stopMovingForward();
    //				moveSmallRight();
    				moveRight();
    				moveForward();
    				_delay_cycles(1000);
    				stopMovingForward();
    			} else if (rightValue() <= RIGHT_MAX) {
    				stopMovingForward();
    //				moveSmallRight();
    				moveRight();
    				moveForward();
    				_delay_cycles(1000);
    				stopMovingForward();
    //				moveSmallLeft();
    				moveLeft();
    				moveForward();
    				_delay_cycles(1000);
    				stopMovingForward();
    			}
    		}

The robot stutters back and forth, runs into the wall, and when it gets past the left wall, it sprints.
