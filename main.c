/*
    Author: Hossam Medhat
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/io.h"

#define F_CPU 8000000
#include "util/delay.h"

/*Common Anode in Kit*/
u8 Arr_DecToSeg[10] = {0xc0,   /* 0 */
                       0xf9,   /* 1 */
                       0xa4,   /* 2 */
                       0xb0,   /* 3 */
                       0x99,   /* 4 */
                       0x92,   /* 5 */
                       0x82,   /* 6 */
                       0xf8,   /* 7 */
                       0x80,   /* 8 */
                       0x90    /* 9 */
					  };

u8 timer = 11 ;
u8 ones , tens ;

u8 colour_state = 0 ; /* 0 for green , 1 for red , 2 for yellow*/
void main ()
{
	/* Set PORTD,PORTC , A0,A1,A2 as output */
	DDRD   = 0xff;
	DDRC = 0xff ;
	DDRA = 0x07;
	SET_BIT(PORTA , 0); /* Green On */
	while(1)
	{

		if (colour_state == 0)
		{
			timer--;
			if (timer == 0)
			{
				CLR_BIT(PORTA , 0); /* Green Off */
				SET_BIT(PORTA , 1); /* Yellow On */
				colour_state = 1 ;
				timer = 3 ;
			}
		}

		else if (colour_state == 1)
		{
			timer--;
			if (timer == 0)
			{
				CLR_BIT(PORTA , 1); /* Yellow Off */
				SET_BIT(PORTA , 2); /* Red On */
				colour_state = 2 ;
				timer = 10 ;
			}
		}

		else if (colour_state == 2)
		{
			timer--;
			if (timer == 0)
			{
				CLR_BIT(PORTA , 2); /* Red Off */
				SET_BIT(PORTA , 0); /* Green On */
				colour_state = 0;
				timer = 10 ;
			}
		}


		/* Display on 7 seg */
		tens = timer / 10 ;
		ones = timer % 10 ;
		PORTD = Arr_DecToSeg[tens] ;
		PORTC = Arr_DecToSeg[ones] ;

		_delay_ms(1000);

	}

}


