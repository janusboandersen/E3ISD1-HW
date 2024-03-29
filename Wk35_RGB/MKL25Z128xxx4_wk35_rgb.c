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
 * @file    MKL25Z128xxx4_Test1.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "rgbLed.h"
/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

   // PRINTF("Hello World\n");
   // char c;
   // c = GETCHAR();
   // PRINTF("Your character is a %c\n", c);
    /* Force the counter to be placed into memory. */
   // volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    char c;

    printf("GPIO Example, E1ISD1 Week 35: Use numbers 1-8 to control RGB color...\n");

    init_rgb();

    while(1) {
   //     i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
   //     __asm volatile ("nop");

    	printf("Enter value 1-8:\n");
    	c = getchar();

    	if (c == '1')
    		set_rgb(BLACK);
    	if (c == '2')
    		set_rgb(WHITE);
    	if (c == '3')
    		set_rgb(RED);
    	if (c == '4')
    		set_rgb(GREEN);
    	if (c == '5')
    		set_rgb(BLUE);
    	if (c == '6')
    		set_rgb(YELLOW);
    	if (c == '7')
    		set_rgb(CYAN);
    	if (c == '8')
    		set_rgb(MAGENTA);

    }
    return 0 ;
}
