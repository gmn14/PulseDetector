/*
 * ssd1306_atmega328.cpp
 *
 * Created: 16/04/2019 13:08:11
 * Author : GUSTAVO
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<stdlib.h>
#include "my_plot.h"
#include <stdint.h>
#include <math.h>
#include <avr/interrupt.h>

//double const PI = 3.14159;

uint8_t const PROGMEM pucp[1024] =
 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 7, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 5, 122, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 37, 182, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 112, 63, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 243, 252, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 79, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 6, 31, 255, 228, 0, 0, 0, 0, 0, 0, 7, 128, 0, 0, 0,
		0, 3, 63, 255, 200, 0, 127, 252, 62, 1, 240, 63, 249, 255, 224, 0,
		0, 6, 127, 255, 242, 0, 127, 254, 62, 1, 240, 255, 253, 255, 248, 0,
		0, 14, 247, 224, 244, 0, 127, 255, 62, 1, 241, 255, 253, 255, 252, 0,
		0, 1, 255, 129, 255, 0, 126, 63, 62, 1, 241, 255, 253, 248, 252, 0,
		0, 29, 255, 129, 251, 128, 126, 31, 62, 1, 243, 248, 13, 248, 124, 0,
		0, 1, 255, 129, 252, 128, 126, 31, 62, 1, 243, 240, 1, 248, 124, 0,
		0, 35, 255, 129, 248, 0, 126, 31, 62, 1, 247, 224, 1, 248, 252, 0,
		0, 59, 255, 224, 251, 128, 127, 255, 62, 1, 247, 224, 1, 255, 252, 0,
		0, 3, 255, 243, 252, 0, 127, 255, 62, 1, 247, 224, 1, 255, 248, 0,
		0, 59, 255, 255, 251, 128, 127, 254, 62, 1, 247, 224, 1, 255, 240, 0,
		0, 3, 255, 255, 248, 8, 127, 248, 62, 3, 247, 224, 1, 255, 224, 0,
		0, 3, 255, 255, 251, 8, 126, 0, 63, 3, 243, 240, 1, 248, 0, 0,
		0, 61, 255, 255, 255, 136, 126, 0, 63, 135, 243, 248, 13, 248, 0, 0,
		0, 29, 255, 255, 255, 136, 126, 0, 31, 255, 227, 254, 125, 248, 0, 0,
		0, 30, 158, 247, 255, 8, 126, 0, 31, 255, 225, 255, 253, 248, 0, 0,
		0, 30, 107, 31, 255, 8, 126, 0, 15, 255, 192, 255, 253, 248, 0, 0,
		0, 15, 255, 255, 255, 8, 126, 0, 7, 255, 0, 127, 249, 248, 0, 0,
		0, 15, 255, 255, 222, 8, 60, 0, 0, 252, 0, 15, 224, 240, 0, 0,
		0, 7, 223, 255, 188, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 239, 254, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 251, 249, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 255, 159, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 127, 255, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 31, 255, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 7, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};	
uint8_t const PROGMEM menu[1024]= //no modificar
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 28, 112, 0, 0, 0, 0, 0, 8, 64,
	0, 0, 0, 3, 135, 12, 8, 62, 248, 0, 0, 0, 0, 0, 8, 64,
	0, 0, 0, 6, 196, 204, 24, 63, 248, 0, 0, 0, 0, 0, 8, 78,
	0, 0, 0, 6, 100, 78, 24, 63, 248, 0, 0, 0, 0, 0, 8, 67,
	0, 0, 0, 6, 68, 74, 44, 63, 248, 0, 0, 0, 0, 0, 15, 194,
	0, 0, 0, 7, 196, 203, 44, 31, 240, 0, 0, 0, 0, 0, 8, 68,
	0, 0, 0, 6, 103, 137, 108, 31, 240, 0, 0, 0, 0, 0, 8, 68,
	0, 0, 0, 6, 36, 9, 76, 15, 224, 0, 0, 0, 0, 0, 8, 72,
	0, 0, 0, 6, 36, 9, 204, 7, 192, 0, 0, 0, 0, 0, 8, 79,
	0, 0, 0, 7, 196, 8, 136, 3, 128, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0x80, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0x80, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0x80, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setInterrupt();
void setPWM();
void setGPIO();
void InitADC();
uint16_t ReadADC(uint8_t);

uint8_t freq = 1;
uint16_t bpm = 60;
uint32_t f_counter = 15000/(uint32_t)bpm ;
uint8_t global_temp = 0;

uint8_t  threshold = 18;

my_plot fb;

int main(void) {
	
	setInterrupt();
	setPWM();
	setGPIO();
	InitADC();
	
	fb.drawBuffer(pucp);
	fb.show();
	_delay_ms(100);
	fb.drawBuffer(menu);
	fb.setBPM(bpm);
	fb.show();
	
	while(1)
	{
		//getBPM();
		
		fb.show();
		_delay_ms(10);
	}
		
	return 0;
}


void setInterrupt()
{
    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);
    // Set the value that you want to count to
    OCR0A = 0xF9;
    TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect
    sei();         //enable interrupts
    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and start the timer

}

void setPWM()
{
	//TIMER1
	DDRB |= (1 << DDB1)|(1 << DDB2);
	// PB1 and PB2 is now an output
	ICR1 = 25;
	// set TOP to 180
	OCR1A = 10;
	// duty 177
	OCR1B = 10;
	// duty 177	
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	TCCR1B |= (1 << CS12);
	// 256 presc
}

void setGPIO(){
	DDRB |= (1 << DDB0);
}

void InitADC()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t ReadADC(uint8_t ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}





ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt
{
	static uint8_t var = 0;
	static uint16_t var2 = 0;
	static uint8_t var3 = 0;
	static uint8_t frame = 0;
	static uint8_t max = 0;
	
	static uint8_t counter = 0 ;
	
	static bool flag = false;
	
	/*
	static uint8_t arr[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	*/
	
	
	uint8_t temp = 0;
	
	//double x = (double) temp;
	//x = 18*(cos(4*PI*x/127.0)+1);
	//temp = (uint8_t)(39*((double)ReadADC(0)/1024.0));
	if (!((f_counter > 300) || (f_counter < 20)))
	{
		if(var2 >= f_counter)
		{
			PORTB |= 0x01;
			if (var2 >= (f_counter + 25))
			{
				PORTB &= ~0x01;
				var2 = 25;
			}
			
		}
	}
	else
	{
		PORTB |= 0x01;	
	}

	if (var3 >= 4)
	{
		
		
		var3 = 0;
		temp = (uint8_t)(40*((double)ReadADC(0)/1024.0));

		fb.plotg(temp,var);
		if (temp >= max)
		{
			max = temp;
		}
		threshold = max - 2;
		
		if ( (!flag) && (temp > threshold))
		{
			counter += 1;
			flag = true;
		}
		else if (flag && (temp <= threshold))
		{
			flag = false;
		}
		
		
		if (var >= 127)
		{
			max  = 0;
			if (frame == 2)
			{
			
			bpm = 625 * counter /64;
			f_counter = (3*512)/ counter;
			counter = 0;
			}
			
			fb.clear();
			
			//fb.clearPlot();
			fb.drawBuffer(menu);
			fb.setBPM(bpm);
			
			frame = (frame >= 2)?(0):(frame+1);
			var = 0;
		}
		
		var++;
		
	}
	var3++;
	var2++;
}
