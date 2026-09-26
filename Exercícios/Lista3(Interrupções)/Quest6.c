#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setup(){
    DDRD |= (1<<PD3);   // LED saída
    DDRB |= (1<<PB6);   // LED saída
    DDRC |= (1<<PC1);   // LED saída

    DDRC &= ~(1<<PC0);  // PC0 como entrada
    DDRB &= ~(1<<PB2);  // PB2 como entrada
    DDRB &= ~(1<<PB5);  // PB5 como entrada
    DDRD &= ~(1<<PD7);  // PD7 como entrada

    PORTD &= ~(1<<PD3);
    PORTB &= ~(1<<PB6);
    PORTC &= ~(1<<PC1);

    PORTC |= (1<<PC0);  // pull-up em PC0
    PORTB |= (1<<PB5);  // pull-up em PB5
    PORTB |= (1<<PB2);  // pull-up em PB2
    PORTD |= (1<<PD7);  // pull-up em PD7

    // PCINT0 a PCINT7  = Porta B
    // PCINT8 a PCINT14 = Porta C
    // PCINT16 a PCINT23 = Porta D
    PCICR = 0b00000111;
    // habilita PCIE0 (Porta B), PCIE1 (Porta C) e PCIE2 (Porta D)

    PCMSK0 = 0b00100100; // bit2=PCINT2(PB2), bit5=PCINT5(PB5)
    PCMSK1 = 0b00000001; // bit0=PCINT8(PC0)
    PCMSK2 = 0b10000000; // bit7=PCINT23(PD7)
}

int main(void){
  setup();
  sei();

  while(1){
    // lógica desejada
  }
}
