#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup(){
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD6);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB1);

    PORTD &= ~(1 << PD5);
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    PORTB &= ~(1 << PB1);

    PORTB |= (1 << PB0);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD4);

    PCICR |= (1 << PCIE0) | (1 << PCIE2);

    PCMSK0 |= (1 << PCINT0) | (1 << PCINT2);

    PCMSK2 |= (1 << PCINT20);

    sei();
}

ISR(PCINT0_vect){
    if(!(PINB & (1 << PB0))){
        PORTD |= (1 << PD7);
        _delay_ms(1000);
        PORTD &= ~(1 << PD7);
        _delay_ms(1000);
    }

    if(!(PINB & (1 << PB2))){
        PORTD |= (1 << PD6);
        _delay_ms(500);
        PORTD &= ~(1 << PD6);
        _delay_ms(500);
    }
}

ISR(PCINT2_vect){
    if(!(PIND & (1 << PD4))){
        PORTB |= (1 << PB1);
        _delay_ms(2000);
        PORTB &= ~(1 << PB1);
        _delay_ms(2000);
    }
}

void loop(){
    PORTD |= (1<<PD5);
    _delay_ms(250);
    PORTD &= ~(1<<PD5);
    _delay_ms(250);
}

int main(void){
  setup();
  while(1){
    loop();
  }
  return 0;
}
