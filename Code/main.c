//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
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
				stopMovingForward();
				moveSmallRight();
				moveForward();
				_delay_cycles(100000);
				stopMovingForward();
				_delay_cycles(100000);
			} else if (rightValue() > RIGHT_MIN) {
				stopMovingForward();
				moveSmallLeft();
				moveForward();
				_delay_cycles(10000);
				stopMovingForward();
				_delay_cycles(100000);
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


//
//		if (rightValue() <= RIGHT_MIN && rightValue() >= RIGHT_MAX && frontValue() < FRONT_MAX) {
//			moveForward();
//			_delay_cycles(10000);
//			stopMovingForward();
//			_delay_cycles(100);
//
//		} else if (frontValue() >= FRONT_MAX) {
//			stopMovingForward();
//			if (rightValue() < RIGHT_MIN) {
//				moveLeft();
//				moveForward();
//				_delay_cycles(1000000);
//				stopMovingForward();
//			} else {
//				moveRight();
//				moveForward();
//				_delay_cycles(1000000);
//				stopMovingForward();
//			}
//		} else if (frontValue() < FRONT_MAX)  {
//			if(rightValue() >= RIGHT_MIN ) {
//				autocorrectLeft();
//			} else if (rightValue() <= RIGHT_MAX) {
//				autocorrectRight();
//			}
//		}
//		if (rightValue() > 0x0210) {
//						moveSmallLeft();
//					} else {
//						moveSmallRight();
//					}

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


//		if (rightValue() > 0x0210) {
//			moveForward();
//			_delay_cycles(10000);
//		}
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

int rightValue() {
	ADC10CTL0 = 0;											// Turn off ADC subsystem
	ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT4;		 								// Make P1.4 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference


	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
	return ADC10MEM;
}

int leftValue() {
	ADC10CTL0 = 0;											// Turn off ADC subsystem
	ADC10CTL1 = INCH_3 | ADC10DIV_3;						// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT3;		 								// Make P1.4 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference


	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
	return ADC10MEM;
}

int frontValue() {
	ADC10CTL0 = 0;											// Turn off ADC subsystem
	ADC10CTL1 = INCH_2 | ADC10DIV_3;						// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT2;		 								// Make P1.4 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference


	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
	return ADC10MEM;
}

void stopMovingBackward(void) {
		P2DIR |= BIT1;
		P2OUT |= BIT1;
		P2DIR |= BIT5;
		P2OUT |= BIT5;
		TA1CCR1 = 0;
		TA1CCR2 = 0;
		TA1CCTL1 = OUTMOD_5;
		TA1CCTL2 = OUTMOD_5;
}

void stopMovingForward(void) {
		P2DIR |= BIT0;
		P2OUT |= BIT0;
		P2DIR |= BIT3;
		P2OUT |= BIT3;
		TA1CCR1 = 0;
		TA1CCR2 = 0;
		TA1CCTL1 = OUTMOD_5;
		TA1CCTL2 = OUTMOD_5;
}

void moveForward(void) {
    	P2DIR |= BIT0;
		P2OUT &= ~BIT0;
		P2DIR |= BIT3;
		P2OUT &= ~BIT3;
		TA1CCR1 = 20;
		TA1CCR2 = 80;
		TA1CCTL1 = OUTMOD_5;
		TA1CCTL2 = OUTMOD_7;

}

void moveBackward() {
	P2DIR |= BIT1;
	P2OUT &= ~BIT1;
	P2DIR |= BIT5;
	P2OUT &= ~BIT5;
	TA1CCR1 = 50;
	TA1CCR2 = 50;
	TA1CCTL1 = OUTMOD_7;
	TA1CCTL2 = OUTMOD_5;
}

void moveSmallRight() {
	P2DIR |= BIT0;
	P2OUT &= ~BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 50;
	TA1CCR2 = 50;
	TA1CCTL1 = OUTMOD_7;
	TA1CCTL2 = OUTMOD_5;
	_delay_cycles(250000);
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 0;
	TA1CCR2 = 0;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_5;

}

void moveSmallLeft() {
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT &= ~BIT3;
	TA1CCR1 = 50;
	TA1CCR2 = 50;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_7;
	_delay_cycles(250000);
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 0;
	TA1CCR2 = 0;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_5;

}

void moveRight() {
	P2DIR |= BIT0;
	P2OUT &= ~BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 50;
	TA1CCR2 = 50;
	TA1CCTL1 = OUTMOD_7;
	TA1CCTL2 = OUTMOD_5;
	_delay_cycles(900000);
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 0;
	TA1CCR2 = 0;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_5;

}

void moveLeft() {
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT &= ~BIT3;
	TA1CCR1 = 50;
	TA1CCR2 = 50;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_7;
	_delay_cycles(900000);
	P2DIR |= BIT0;
	P2OUT |= BIT0;
	P2DIR |= BIT3;
	P2OUT |= BIT3;
	TA1CCR1 = 0;
	TA1CCR2 = 0;
	TA1CCTL1 = OUTMOD_5;
	TA1CCTL2 = OUTMOD_5;
}

void autocorrectRight() {
	stopMovingForward();
	_delay_cycles(10000);
	moveSmallRight();
	moveForward();
	_delay_cycles(100000);
//	moveSmallLeft();
//	_delay_cycles(10000);
}

void autocorrectLeft() {
	stopMovingForward();
	_delay_cycles(10000);
	moveSmallLeft();
	moveForward();
	_delay_cycles(100000);
//	moveSmallRight();
//	_delay_cycles(10000);
}

