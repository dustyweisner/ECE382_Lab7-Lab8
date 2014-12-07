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

__*Lab 8 "Robot Maze"*__

INSTRUCTIONS  
You must write a program that autonomously navigates your robot through a maze (Figure 1) while meeting the following requirements:

1. Your robot must always start at the home position.
2. Your robot is considered successful only if it finds one of the three exits and moves partially out of the maze. A large portion of your grade depends on which door you exit.
    Door 1 - Required Functionality
    Door 2 - B Functionality
    Door 3 - A Functionality
3.You cannot hit a wall!
4. Bonus! Navigate from the A door back to the entrance using the same algorithm.
5. You cannot hit a wall!
6. Your robot must solve the maze in less than three minutes.
7. Your robot will be stopped if it touches the wall more than twice.
8. Your robot must use the IR sensors to find its path through the maze.

Pseudocode of how to make the robot go through the maze FOR A FUNCTIONALITY:

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

The robot stutters back and forth, runs into the wall, and when it gets past the left wall, it sprints. After little corrections and more coding for dubugging, I changed my coding using a different pseudocode:

        /* move forward if right wall is within range else stop and....
         * if right wall is too far away
         * 		stop
         * 		move small right
         * 		move forward
         * 		move small left
         * if right wall is too close
         * 		stop
         * 		move small left
         * 		moveforward()
         * 		delay 1000
         * 		move small right
         * if left wall is too close
         * 		stop
         * 		move small right
         * 		moveforward
         * 		delay 1000
         * 		move small left
         * if front wall is too close
         * 		stop
         * 		turn right
         *
         */

The code for this also did not work. My robot kept twirling around in circles, and I could not correct the code for functionality. When I corrected the IR reciever threshold distances, I finally got the robot to move forward and correct itself if it was too close to the wall. So then the problem was that it kept going slow and then when it went past the wall on the left, it would sprint, slamming into the wall ahead of it. Then I kept fiddling with the speed and coding, and it didn't make much of a difference and actually forward hit a wall and turned completely around to hit another wall and so on. I decided to make an even newer pseudocode, which is the code I ended with for A/Bonus functionality. The following code is what I ended up with:

        if(frontValue() < FRONT_MAX) {
        	if (rightValue() <= RIGHT_MIN && rightValue() >= RIGHT_MAX) {
        		moveForward();
        		_delay_cycles(10000);
        		stopMovingForward();
        		_delay_cycles(10000);
        	} else if (rightValue() <= RIGHT_MIN) {
        		autocorrectRight();
        	} else if (rightValue() > RIGHT_MIN) {
        		autocorrectLeft();
        	}
        } else if(frontValue() >= FRONT_MAX) {
        	while(frontValue() >= FRONT_MAX) {
        		moveSmallLeft();
        		stopMovingForward();
        		_delay_cycles(10000);
        	}
        	moveForward();
        	_delay_cycles(10000);
        }
    
The autocorrects were just to keep the right wall within a certain minimum and maximum voltage threshold for the robot to follow the rightmost wall to get to the A door. Because this code worked, I will give an explanation of what it does.

Explanation of Code with Maze  
The code first looks for if there is a wall ahead of it. Because there was not one at the beginning, it then looked for a wall to the right. I placed it within a range, so it moved only forward. However, my robot doesn't perfectly move straight. So to compensate, my autocorrects would put the robot back on track. The robot would continue until the first wall. When the wall was in front of the front sensor, the robot would turn left until the front sensor didn't sense anymore. Then the robot would move forward for a little, then continue on its program. The robot then moved forward, sensing the right wall, and the robot continued until there was no right wall. When there was no right wall, the robot autocorrected right because it wasn't within the threshold range. It autocorrected all the way around the corner of the wall, where it picked up the wall to the right and got back into the threshold range. It continued until it saw the wall in front of it and took a left turn until the front sensors didn't pick it up anymore and continued on its way forward right out the A functionality door. Then, using the exact same algorithm, I put it back through the maze backwards. It made it through and earned Bonus functionality.

Some difficulties occured trying to get the correct threshold values to get the maze only to sense certain distances. All I did was give about 4 inches of a threshold value range. The range was not always accurate so I had to move the inner value farther from the wall, but I had to keep the outer value large enough so that the voltage picked up from noise would not screw up the readings and make a false sensing and thus motor control. The correct voltage was used for the front wall from the start. I picked a low enough value that would not interfere if the robot suddenly turned left too far. I did not have to worry about the left wall because given the other code, the robot should always make its way right back to the right wall. The left sensor would come handy if the walls were closer together or if the maze was bigger.

Documentation: NONE

This concludes LAB 7, LAB 8, and ECE 382 Labs.

