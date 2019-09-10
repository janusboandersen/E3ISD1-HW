/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_wk36_GPIO.c
 * @brief   Application entry point.
 */

/* This is based on example pp. 40-41 in Dean (ESF) */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define LED1_SHIFT (1)  // PTA
#define LED2_SHIFT (2)	// PTA
#define SW1_SHIFT (5)	// PTA

#define MASK(x)	(1UL << (x))
/*
 * @brief   Application entry point.
 */

void setup_pins(void) {
	// Enable clock
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //only connect clock to PTA

	// Set 3 pins as GPIO
	PORTA->PCR[LED1_SHIFT] &= ~PORT_PCR_MUX_MASK; 	//clear MUX values without touching other bits
	PORTA->PCR[LED1_SHIFT] |= PORT_PCR_MUX(1); 		// Connect pin PTA1 as GPIO

	PORTA->PCR[LED2_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LED2_SHIFT] |= PORT_PCR_MUX(1);

	PORTA->PCR[SW1_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SW1_SHIFT] |= PORT_PCR_MUX(1);

	/* Set LEDs to be outputs -- here we work on the entire 32 bit PDDR */
	PTA->PDDR |= MASK(LED1_SHIFT) | MASK(LED2_SHIFT);

	/* Clear SW to be input */
	PTA->PDDR &= ~MASK(SW1_SHIFT);
}

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    setup_pins(); //start the pins

    PRINTF("E3ISD1/HW wk36 - GPIO examples... Toggle LEDs using a switch\n");

    PTA->PSOR = MASK(LED1_SHIFT); //Turn on: Using the set mechanism
    PTA->PCOR = MASK(LED2_SHIFT); //Turn off: Using the clear mechanism

    /* Start infinite loop to check switch and handle lights */
    while(1) {

    	if (PTA->PDIR & MASK(SW1_SHIFT)) { //read off the particular bit in the input register of port A
    		//switch is inactive (inactive high)
    		printf("Switch off\n");
    		PTA->PSOR = MASK(LED2_SHIFT); //set LED2
    		PTA->PCOR = MASK(LED1_SHIFT); //clear LED1
    	} else {
    		//switch is active (active low)
    		printf("Switch on\n");
    		PTA->PSOR = MASK(LED1_SHIFT); //set LED2
    		PTA->PCOR = MASK(LED2_SHIFT); //clear LED1
    	}
    }
    return 0 ;
}
