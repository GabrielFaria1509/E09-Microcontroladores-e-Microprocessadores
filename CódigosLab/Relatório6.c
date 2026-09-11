#include<stdio.h>
 
ISR(INT0_vect){
  PORTD = PORTD | 0b00010000;
  _delay_ms(1000);
  PORTD = PORTD &~ (0b00010000);
  _delay_ms(1000);
}
 
 
 
int main(void){
  DDRD = 0b00110000;  //declara pino 5 e 4
  PORTD = 0b00000000;
 
  EICRA = 0b00000011; //como quero que a interrupcao aconteca; os ultimos dois ativados: INT0 e os dois anteriores INT1 desativados
  EIMSK = 0b00000001;  //onde quero que a interrupcao aconteca;
 
  sei();
 
  while(true){
 
  //loop do led do pino 5 usando o PORTD
  PORTD = PORTD | 0b00100000; //LIGA
  _delay_ms(500);
  PORTD = PORTD & ~(0b00100000);  //DESLIGA
  _delay_ms(500);
 
 
  }
}
