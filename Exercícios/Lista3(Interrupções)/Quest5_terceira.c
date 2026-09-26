//Pergunta geral : Utilizando o ATMega328p, escreva as linhas de código (registradores EICRA e EIMSK) necessárias para as seguintes configurações. Considere que a função sei(); 
//será chamada em todos os casos:

//b)Interrupção de subida em INT0 e, simultaneamente, interrupção de descida em INT1. 

#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(INT1_vect){
  PORTD &= ~(1<<PD4);
  _delay_ms(500);
  PORTD |= (1<<PD5);
  _delay_ms(500);
  PORTD &= ~(1<<PD5);
  _delay_ms(500);
}

ISR(INT0_vect){
  PORTD |= (1<<PD6);
  _delay_ms(500);
  PORTD &= ~(1<<PD6);
  _delay_ms(500);
}

int main(void){
  DDRD &= ~(1<<PD3);      // PD3 (INT1) como entrada
  DDRD &= ~(1<<PD2);      // PD2 (INT0) como entrada
  
  DDRD |= (1<<PD4) | (1<<PD5) | (1<<PD6); // LEDs como saída

  EICRA |= (1 << ISC11) | (1<<ISC00) | (1<<ISC01);  // Descida em INT1 e Subida em INT0
  
  EIMSK |= (1 << INT1) | (1 << INT0);   // habilita INT0 e INT1

  PORTD &= ~(1 << PD5); //led pino 5 desligado
  PORTD &= ~(1 << PD4); //led pino 4 desligado
  PORTD &= ~(1 << PD6); //led pino 4 desligado
  
  
  PORTD |= (1 << PD3);    // pull-up interno no PD3
  PORTD |= ( 1 << PD2); //pull-up interno no PD2

  sei();

  while(1){
    PORTD |= (1<<PD4);
    _delay_ms(500);
    PORTD &= ~(1<<PD4);
    _delay_ms(500);
  }
}
