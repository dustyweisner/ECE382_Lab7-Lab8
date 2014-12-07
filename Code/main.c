//-----------------------------------------------------------------
// Name:	Dustin Weisner
// File:	lab7_lab8.c
// Date:	2 DEC 2014
// Purp:	Make a robot go through a maze
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "main.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;
	//initMSP430();
	// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
	P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

	P2DIR |= BIT4;							// P2.2 is associated with TA1CCR2
	P2SEL |= BIT4;							// P2.2 is associated with TA1CCTL2

	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
	TA1CCR0 = 100;							// set signal period

	TA1CCR1 = 20;
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	TA1CCR2 = 80;
	TA1CCTL2 = OUTMOD_3;




													// Set the red LED as output


	while(1) {

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


//	Required Functionality Lab 7
//				if (leftValue() > 0x0200) {
//					P1DIR |= BIT0;
//					P1OUT &= ~BIT6;
//					P1OUT |= BIT0;
//
//				} else {
//					P1OUT &= ~BIT0;
//				}
//				if (rightValue() > 0x0210) {
//					P1DIR |= BIT6;
//					P1OUT &= ~BIT0;
//					P1OUT |= BIT6;
//				}
//
//				if (frontValue() > 0x0200) {
//					P1DIR |= BIT6;
//					P1DIR |= BIT0;
//					P1OUT |= BIT0;
//					P1OUT |= BIT6;
//				} else {
//					P1OUT &= ~BIT6;
//					P1OUT &= ~BIT0;
//				}

	} // end infinite loop

} // end main
