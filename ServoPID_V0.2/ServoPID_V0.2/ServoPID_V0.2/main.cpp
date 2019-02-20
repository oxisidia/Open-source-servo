/*
 * GccApplication4.cpp //Switch LED
 *
 * Created: 2/3/2019 3:10:38 PM
 * Author : Dylan Rice
 */ 

 //Serial print stuff.

#include <avr/io.h>

#include <avr/interrupt.h>

#include <stdint.h>

//Define statements.

#define F_CPU 16000000 //Define the CPU speed.


//Hall effect global setup

int count = 0; //To count the iterations.

bool hall_effectA = true;  //boolean gate for hall A.

bool hall_effectB = true; //boolean gate for hall B.

bool hall_effectN = true; 

//Print void.



int main(void)
{

	//hall effect setup
	
	DDRC =  0b00010011; //Setting a value to 1 makes it an output zero an input.

	PORTC = 0b00101100; //Setting a value to 1 turns on the pull up resistor for that register. 

	PORTC &= 0b11111111;
	
    while (1) 
    {
		
		//Hall A Logic.

		if(!(PINC & 0b00001000)) //If the values of PinC anded with the binary mask 0b00000010 is not true then blink the led. 
		{
			PORTC |= 0b0000010; //Turn the last bit on. This causes pin 0 on port c to go high blinking the LED.

			

			if(hall_effectA == true) //Check if the boolean gate is true.
			{
				count++; //iterate the encoding

				hall_effectA = false; //close the boolean gate.
			}

		}
		else
		{
			PORTC &= 0b11111101; //Turn the last bit off

			hall_effectA = true; //Reopen the boolean gate.
		}


		//Hall B logic.

		if(!(PINC & 0b00000100))
		{
			PORTC |= 0b00010000;

			if(hall_effectB == true) //
			{
				count++;

				hall_effectB = false;
			}

		}
		else
		{
			PORTC &= 0b11101111;

			hall_effectB = true;
		}



		//hall effect n logic.

		if((hall_effectA == true) && (hall_effectB == true))
		{
			if(hall_effectN == true)
			{
				count++;

				hall_effectN = false;
			}
			
		}
		else
		{
			hall_effectN = true;
		}

		//limit switch logic.



		if(!(PINC & 0b00100000))
		{
			PORTC |= 0b000000001; 
		}
		
		else
		{
			PORTC &= 0b11111110; 
		}		
    }
}

