/*
 * Garage.c
 *
 * Created: 10/24/2024 4:25:37 PM
 *  Author: AHMED GAMAL
 */ 


#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "LCD.h"
#include "timer.h"

int main(void)
{
	LCD_vInit();
	LCD_vSend_string("There are 0 Cars");
	LCD_movecursor(2,1);
	LCD_vSend_string("Garage has space");
	char flag1=0,flag2=0,flag3=0,flag4=0,IR1,IR2,IR3,IR4,counter=0;
	DIO_vsetPINDir('D',0,0);
	DIO_vsetPINDir('D',1,0);
	DIO_vsetPINDir('D',2,0);
	DIO_vsetPINDir('D',3,0);
    while(1)
    {
		IR1=DIO_u8read('D',0);
		if (IR1==1 && flag1==0 && counter<5)
		{
			counter++;
			timer1_wave_fastPWM_B(0.999999);
			LCD_clearscreen();
			LCD_vSend_string("Welcome");
			_delay_ms(50);
			LCD_clearscreen();
			LCD_vSend_string("There are ");
			LCD_vSend_char(counter+48);
			LCD_vSend_string(" cars");
			LCD_movecursor(2,1);
			LCD_vSend_string("Garage has space");
			flag1=1;
			if (counter==5)
			{
				LCD_clearscreen();
				LCD_vSend_string("there are 5 cars");
				LCD_movecursor(2,1);
				LCD_vSend_string("Garage is full");
			}
			
			
		}
		else if (IR1==0)
		{
			flag1=0;
		}
		
		
		IR2=DIO_u8read('D',1);
		if (IR2==1 && flag2==0)
		{
			timer1_wave_fastPWM_B(1.499999);
			flag2=1;
		}
		else if (IR2==0)
		{
			flag2=0;
		}
		
		IR3=DIO_u8read('D',2);
		if (IR3==1 && flag3==0 && counter>0)
		{
			timer1_wave_fastPWM_A(0.99999);
			counter--;
			flag3=1;
			LCD_clearscreen();
			LCD_vSend_string("There are ");
			LCD_vSend_char(counter+48);
			LCD_vSend_string(" cars");
			LCD_movecursor(2,1);
			LCD_vSend_string("Garage has space");
			
		}
		else if (IR3==0)
		{
			flag3=0;
		}
		
		IR4=DIO_u8read('D',3);
		if (IR4==1 && flag4==0 && counter>-1)
		{
			timer1_wave_fastPWM_A(1.49999);
			LCD_clearscreen();
			LCD_vSend_string("Good Bye");
			_delay_ms(150);
			LCD_clearscreen();
			LCD_vSend_string("There are ");
			LCD_vSend_char(counter+48);
			LCD_vSend_string(" cars");
			LCD_movecursor(2,1);
			LCD_vSend_string("Garage has space");
			_delay_ms(350);
			flag4=1;
		}
		else if (IR4==0)
		{
			flag4=0;
		}
    }
}