//Pergunta geral : Utilizando o ATMega328p, escreva as linhas de código (registradores EICRA e EIMSK) necessárias para as seguintes configurações. Considere que a função sei(); 
//será chamada em todos os casos:

//b)Interrupção de descida no pino INT1; 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT1_vect){
  PORTD &= ~(1<<PD4);
  _delay_ms(500);
  PORTD |= (1<<PD5);
  _delay_ms(500);
  PORTD &= ~(1<<PD5);
  _delay_ms(500);
}

int main(void){
  DDRD &= ~(1<<PD3);           // PD3 (INT1) como entrada
  DDRD |= (1<<PD4) | (1<<PD5); // LEDs como saída

  EICRA |= (1 << ISC11);  // borda de descida em INT1
  EIMSK |= (1 << INT1);   // habilita INT1

  PORTD &= ~(1 << PD5);
  PORTD &= ~(1 << PD4);

  PORTD |= (1 << PD3);    // pull-up interno no PD3

  sei();

  while(1){
    PORTD |= (1<<PD4);
    _delay_ms(500);
    PORTD &= ~(1<<PD4);
    _delay_ms(500);
  }
}
