#include "mbed.h"
#include "pindef.h"
#include "notes.h"
#include "leds.cpp"
#include "switches.c"
#include <stdio.h>
#include <stdlib.h>
/*
Define the PWM speaker output
Define analog inputs*/
#define _(a)    # a
void red(); void green();
Timeout timer;
Serial device(UART_TX, UART_RX);
PwmOut Speaker(PB_10);
float frequency[] ={E3,E3,D3b,E3,E3,D3b,E3,G5,C2,D2,D3b,F4,F4,F4,F4,F4,E3,E3,E3,E3,E3,D2,D2,E3,D2b,G5b,E3,E3,D3b,E3,E3,D3b,E3,G5,C2,D2,E3,F4,F4,F4,F4,F4,E3,E3,E3,E3,G5,G5,F4,D2,C2};
float duration2[] = {.5,.5,.5,1.0,.5,.5,.5,1.0,.5,.5,.5,.8,1.5,.5,.5,.5,.5,.8,.5,.5,.7,.7,.7,.7,.5,.5,.5,.5,.5,.7,.8,.8,.5,.5,.5,.9,.5,.5,.5,.7,.7,.8,.6,1.0,.7,.7,.7,.7,.5,.7,.7,.7,.5,.5,.7,.7,.7,.7,1.0,0.0};
float frequency2[] = {E3,E3,D3b,E3,E3,D3b,E3,G5,C2,D2,D3b};
float duration3[] = {.5,.5,.5,1.0,.5,.5,.5,1.0,.5,.5,.5,.8};
float frequency3[] = {B6,B6,B6,B6,B6,B6,B6,D6b,G6,A6,B6,C6x,C6x,C6x,C6x,C6x,B6,B6,B6,B6,B6,A6,A6,B6,A6,D6b};
float duration4[] = {.5,.5,1.0,.5,.5,1.0,.5,.5,.7,.5,1.0,.5,.5,1.0,.5,.5,.5,1.5,.5,.5,.5,.5,.5,.5,.5,1.0,1.0};
float frequency4[] = {B4,B4,B4,B4,B4,B4,B4,D4b,G4,A4,B4,C4x,C4x,C4x,C4x,C4x,B4,B4,B4,B4,B4,A4,A4,B4,A4,D4b};


float furelise[] = 
{
    e4, d4x,e4, d4x, e4, b3, d4, c4, a3, p, 
    c3, e3, a3,  b3, p, e3, g3x, b3, c4, p, e3,
    e3, d4x, e4, d4x, e4, b3, d4, c4, a3, p, c3,
    e3, a3, b3, p, e3, c4, b3,a3, MUSIC_END};
	
float duration6[] = { 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8,
     1.8, 1.8, 1.8, 1.4, 1.8, 1.8, 1.8, 1.8, 1.4, 1.8, 1.8,
     1.8,  1.8,  1.8,  1.8,  1.8,  1.8,  1.8,  1.8,  1.8, 1.8,  1.8,
1.8, 1.8, 1.4, 1.8, 1.8, 1.8, 1.8, 1.4};
float starwars2[] = 
{
	Ais2,Ais2, P, F3, F3, P, Dis3, P, D3, P, C3, P, Ais3,
	Ais3, P, F3, P, Dis3, P, D3, P, C3, P, Ais3, Ais3, P,
	F3, P, Dis3, P, D3, P, Dis3, P, C3, C3, MUSIC_END
};
float duration5[] = {1.8,1.8,1.16,1.8,1.8,1.16,1.16,1.16,1.16,1.16,1.16,1.16,1.8,1.8,1.16,1.8,1.16,1.16,1.16,1.16,1.16, 1.16,1.16,1.8,1.8,1.16,1.8,1.16,1.16,1.16,1.16,1.16,1.16,1.16,1.8,1.8};
	int i = 0;
	
	//not used
	void red()
{
	toggle_g();
	toggle_b();
}

//not used
void green()
{
	toggle_b();
	toggle_g();
}

//not used
void endSong()
{
	GPIOA->ODR ^= ODR(GREEN_LED);
	Speaker.write(.5);
	//exit(0);
	timer.detach();
	
}	
	void printNote(float note)
	{
		device.baud(9600);
		//printf("%s: %.6f\n", _(note), note);
		printf("%.6f\r\n", note);
	}
void audio(float frequencyptr[],float durationptr[],int size, float speed, float range)
{
//bool color = 0;
	
	while(i<= size/sizeof(int) - 1){
		if(frequency[i] < 500)
			toggle_r();
		else if(frequency[i] > 600 && frequency[i] < 1000)
			toggle_g();
		else if(frequency[i] > 100)
			toggle_b();
	//float freq = (FrequencyIn.read() * 2000) + frequency[i];
	Speaker.period(range/frequencyptr[i]);
	//Speaker.period(1.0f/freq);
  // i++;
	if( p == frequencyptr[i] )
		{
			//pause, do not generate any sound
			Speaker = 0;
		}
		else{
		Speaker.write(0.2);}
		wait(((durationptr[i]) - speed));
	if(frequency[i] < 300)
			toggle_b();
		else if(frequency[i] > 300 && frequency[i] < 400){
			//toggle_r();
			toggle_r();}
		else if(frequency[i] > 500)
			toggle_g();		// .3
		printNote(range/frequency[i]);
		i++;
	};
	i = 0;
	Speaker = 0.0f;
	Speaker.period(1);
}
/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
//int i = 0;
int main(){
	init_RGB();
	//init_switches();
	audio(frequency4,duration4,sizeof(frequency4),0.1,1.0f);
	audio(furelise,duration6,sizeof(furelise),1.4,1.0f);
	
	if(!(GPIOA->IDR >> SWITCH_1 & 0x1)){
			toggle_r();
		audio(frequency4,duration4,sizeof(frequency4),0.1,1.0f);
		}
	
	
	if(!(GPIOA->IDR >> SWITCH_1 & 0x1))
				{
				audio(frequency4,duration4,sizeof(frequency4),0.1,1.0f);
				}
			if(!(GPIOB->IDR >> SWITCH_2 & 0x1))
				{
						audio(furelise,duration6,sizeof(furelise),1.4,1.0f);
					timer.attach(&endSong,10);
					GPIOA->ODR ^= ODR(GREEN_LED);
				}
			if(!(GPIOB->IDR >> SWITCH_3 & 0x1))
				{}
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
