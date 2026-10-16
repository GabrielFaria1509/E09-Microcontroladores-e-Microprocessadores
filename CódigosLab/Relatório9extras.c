#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t esteira1 = 0b00001010;
volatile uint8_t esteira2 = 0b00000000;

ISR(INT1_vect)
{
  while (esteira1) {                 // enquanto houver peça
    if (esteira1 & (1<<0)) {         // peça com defeito na posição 0
      esteira2 >>= 1;                // esteira 2 avança
      esteira2 |= (1<<7);            // peça entra na última posição
      PORTD |= (1<<PD5);
      _delay_ms(1000);
      PORTD &= ~(1<<PD5);
      _delay_ms(1000);
    }
    esteira1 >>= 1;                  // esteira 1 avança uma única vez
  }
}

ISR(PCINT0_vect)
{
  if (!(PINB & (1<<PB4))) {          // S2 pressionado (pull-up: nível baixo)
    while (esteira2) {
      if (esteira2 & (1<<0)) {       // peça na posição 0
        PORTD |= (1<<PD6);
        _delay_ms(1000);
        PORTD &= ~(1<<PD6);
        _delay_ms(1000);
      }
      esteira2 >>= 1;
    }
  }
}
