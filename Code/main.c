//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;




													// Set the red LED as output


	while(1) {

				if (leftValue() > 0x0200) {
					P1DIR |= BIT0;
					P1OUT &= ~BIT6;
					P1OUT |= BIT0;

				} else {
					P1OUT &= ~BIT0;
				}
				if (rightValue() > 0x0210) {
					P1DIR |= BIT6;
					P1OUT &= ~BIT0;
					P1OUT |= BIT6;
				}

				if (frontValue() > 0x0210) {
					P1DIR |= BIT6;
					P1DIR |= BIT0;
					P1OUT |= BIT0;
					P1OUT |= BIT6;
				} else {
					P1OUT &= ~BIT6;
					P1OUT &= ~BIT0;
				}

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

