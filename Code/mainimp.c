//-----------------------------------------------------------------
// Name:	Dustin Weisner
// File:	lab7 and lab8 implementation
// Date:	2 DEC 2014
// Purp:	Make a robot go through a maze
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "main.h"

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
	moveSmallRight();
	moveForward();
	_delay_cycles(100000);
	stopMovingForward();
	_delay_cycles(100000);
}

void autocorrectLeft() {
	stopMovingForward();
	moveSmallLeft();
	moveForward();
	_delay_cycles(10000);
	stopMovingForward();
	_delay_cycles(100000);
}
