#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>



void setup(){
DDRD |= (1<<PD5) | (1<<PD4);
TCCR0A |= (1 << WGM01); //configura o modo de operação do timer
TCCR0B |= (1 << CS00) | (1 << CS01); // config o divisor de clock
TIMSK0 |= (1 << OCIE0A); //intervalo  
OCR0A = 249;



sei();
}
uint8_t cont = 0;
uint16_t cont2 = 0;



//função de tratamento da interrupção
ISR(TIMER0_COMPA_vect){



  //led pisca com 150ms
  
  cont ++;
  if(cont >=100){
  PORTD ^= (1 << PD5);  //led vermelho
  cont = 0;
  }



  cont2 ++;
  if(cont2 >=60000){
  PORTD ^= (1 << PD4);  //led vermelho
  cont2 = 0;
  }
  
}
int main(){
  setup();
  for(;;){}
  
}
 
