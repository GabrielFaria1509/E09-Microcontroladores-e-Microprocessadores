//Pergunta geral : Utilizando o ATMega328p, escreva as linhas de código (registradores EICRA e EIMSK) necessárias para as seguintes configurações. Considere que a função sei(); 
//será chamada em todos os casos:

//a)Interrupção por qualquer mudança de nível (borda de subida ou de descida) no pino INT0;

#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>

ISR(INT0_vect){
  PORTD &= ~(1<<PD3);
  _delay_ms(500);
  PORTD |= (1<<PD5);
  _delay_ms(500);
  PORTD &= ~(1<<PD5);
}

int main(void){
  DDRD &= ~(1<<PD2);      // PD2 (INT0) como entrada
  DDRD |= (1<<PD3) | (1<<PD4) | (1<<PD5); // LEDs como saída

  EICRA |= (1 << ISC00);  // qualquer mudança de nível em INT0
  EIMSK |= (1 << INT0);   // habilita INT0

  PORTD &= ~(1 << PD3);
  PORTD &= ~(1 << PD5);
  PORTD |= (1 << PD2);    // pull-up interno no PD2 

  sei();

  while(1){
    PORTD |= (1<<PD3);
    _delay_ms(500);
    PORTD &= ~(1<<PD3);
    _delay_ms(500);
  }
}
