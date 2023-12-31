#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "common_macros.h"
#include "GPIO.h"

#define MINUTE 60
#define HOUR 60
#define DAY 24
#define TICKS_PER_SECOND 977

unsigned char seconds=0;
unsigned char minutes=0;
unsigned char hours=0;
unsigned char countDownMode = 0;
unsigned char countDownButtonState = 0 ;


void Timer1_CTC_mode_Initial(void) {
	SET_BIT(SREG,7);
	TIMSK|=(1<<OCIE1A);
	TCNT1=0;
	OCR1A = TICKS_PER_SECOND;
	TCCR1A |= (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10); //pre-scaler 1024 , 977 ticks for 1 second
}

void Initial_IO(void) {
	DDRA |=0x3F;
	PORTA|=0x3F;
	DDRC|=0x0F;
	PORTC = 0x00;

	//stopWatch button : internal pull up
	DDRB&=~(1<<PB5);
	PORTB|=(1<<PB5);
}

void Initial_INT0(void) {
	DDRD&=~(1<<PD2);
	PORTD|=(1<<PD2);
	GICR |=(1<<INT0);
	MCUCR |=(1<<ISC01);
}

void Initial_INT1(void) {
	DDRD&=~(1<<PD3);
	GICR |=(1<<INT1);
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}
void Initial_INT2(void) {
	DDRB&=~(1<<PB2);
	PORTB|=(1<<PB2);
	GICR |=(1<<INT2);
	MCUCSR &=~(1<<ISC2);
}


ISR(TIMER1_COMPA_vect){
	if (countDownMode) {
		if (seconds>0) {
			seconds--;
		}
		else {
			if (minutes>0){
				seconds=59;
				minutes--;
			}
			else {
				if (hours>0){
					minutes=59;
					seconds=59;
					hours--;
				}
				else {
					hours = minutes = seconds = 0;
				}
			}
		}
	}
	else {
		seconds++;
		if (seconds==MINUTE) {
			seconds=0;
			minutes++;
		}
		if(minutes==HOUR){
			minutes=0;
			hours++;
		}
		if (hours==DAY){
			// reset timer
			seconds = minutes = hours =0;
		}
	}

}
ISR(INT0_vect) { //reset stopWatch. button PD2
	seconds= 0;
	minutes = 0;
	hours = 0;
}

// stop the timer from counting by stopping the clock source. button PD3
ISR(INT1_vect) {
	TCCR1B &= ~((1<<CS10) | (1<<CS12));
}
// resume timer count by clicking on button PB2
ISR(INT2_vect) {
	TCCR1B |= (1<<CS10) | (1<<CS12);
}
void StopWatch_display(void) {
	while(1){
		if (!(PINB&(1<<PB5))){
			_delay_ms(30);
			if (!(PINB&(1<<PB5))){
				if (!countDownButtonState){
					countDownMode =! countDownMode;
					countDownButtonState = 1;
				}
				else {
					countDownButtonState=0;
					countDownMode =! countDownMode ;
				}
			}
		}

		int pin =0;
		for (; pin < 6; ++pin) {
			PORTA= (1<<pin);
			PORTC &= 0xF0;
			switch (pin){
			case 0:
				PORTC |= seconds%10;
				break;
			case 1:
				PORTC |= seconds/10;
				break;
			case 2:
				PORTC |= minutes%10;
				break;
			case 3:
				PORTC |= minutes/10;;
				break;
			case 4:
				PORTC |= hours%10;;
				break;
			case 5:
				PORTC |= hours/10;
				break;
			}
			_delay_ms(3);
		}
	  }
}
int main (void) {
	Initial_IO();
	Initial_INT0();
	Initial_INT1();
	Initial_INT2();
	Timer1_CTC_mode_Initial();
	StopWatch_display();

}
