#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){
  PORTD = PORTD | 0b00010000;   //liga LED do pino 4
  _delay_ms(1000);
  PORTD = PORTD & ~(0b00010000); //desliga LED do pino 4
}

ISR(INT1_vect){
  // Verifica se o INT0 está habilitado (bit 0 do EIMSK)
  if(EIMSK & 0b00000001){
    EIMSK = EIMSK & ~(0b00000001); //desabilita INT0
  } else {
    EIMSK = EIMSK | 0b00000001;    //habilita INT0
  }
}

int main(void){
  DDRD = 0b00110000;  //declara pino 5 e 4 como saida
  PORTD = 0b00000000;

  //EICRA: bits 3,2 = ISC11,ISC10 (INT1) | bits 1,0 = ISC01,ISC00 (INT0)
  //INT0 = transicao de subida (11) | INT1 = transicao de descida (10)
  EICRA = 0b00001011;

  EIMSK = 0b00000011; //habilita INT0 e INT1

  sei();

  while(1){
    //loop do led do pino 5 usando o PORTD
    PORTD = PORTD | 0b00100000; //LIGA
    _delay_ms(500);
    PORTD = PORTD & ~(0b00100000);  //DESLIGA
    _delay_ms(500);
  }
}
