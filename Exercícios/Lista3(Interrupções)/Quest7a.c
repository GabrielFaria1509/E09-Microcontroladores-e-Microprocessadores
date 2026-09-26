//Contexto : Um sistema de irrigação automática possui um sensor de nível (chave que assume nível alto quando o reservatório está cheio) 
//conectado ao pino PD2 (INT0) e um botão de parada manual conectado ao pino PB0 (grupo PCINT0). Desenvolva, em linguagem C, um código que: 

//a)ao detectar a borda de subida em PD2 (reservatório cheio), desligue a bomba de irrigação (uma saída digital) e acenda um LED indicativo; 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect){ // Reservatório cheio (borda de subida em PD2)
  //Não preciso de if nesse tipo de interrupção pois já coloquei que vai ativar com subida(Logo botão começa em 0)
  PORTD |= (1<<PD5);   // acende LED indicativo
  PORTD &= ~(1<<PD4);  // desliga bomba de irrigação
}

void setup(){
  DDRD |= (1<<PD4);   // Bomba de irrigação (saída)
  DDRD |= (1<<PD5);   // LED (saída)
  DDRD &= ~(1<<PD2);  // Sensor de nível (entrada)
  DDRB &= ~(1<<PB0);  // Botão (entrada)

  EICRA |= (1<<ISC01) | (1<<ISC00); // borda de subida em INT0
  EIMSK |= (1<<INT0);               // habilita INT0

  PCICR |= (1<<PCIE0);              // habilita grupo PCINT da Porta B
  PCMSK0 |= (1<<PCINT0);            // habilita PCINT0 (PB0)

  PORTD &= ~(1<<PD5);  // LED desligado
  PORTD |= (1<<PD4);   // bomba começa ligada
  PORTD &= ~(1<<PD2);  // sem pull-up interno (sensor externo controla o nível)
  PORTB |= (1<<PB0);   // pull-up interno no botão

  sei();
}

int main(void){
  setup(); //chama configuração

  while(1){
    // lógica desejada
  }
}
