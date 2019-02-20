/*
 * Test how to use uart stuff as an outside library. Redirects stdout
 * to uart.
 * 
 * Led at Arduino digital 13 (PORTB5). Cause we all love blinken leds!
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-* 9600
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 */
 

#define F_CPU 16000000UL


//#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


int main(void) {    
                
    while (1) 
	{
          
    }

}

