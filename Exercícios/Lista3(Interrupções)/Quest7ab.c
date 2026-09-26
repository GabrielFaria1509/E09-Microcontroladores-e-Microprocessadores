//Contexto : Um sistema de irrigação automática possui um sensor de nível (chave que assume nível alto quando o reservatório está cheio) 
//conectado ao pino PD2 (INT0) e um botão de parada manual conectado ao pino PB0 (grupo PCINT0). Desenvolva, em linguagem C, um código que: 

//a)ao detectar a borda de subida em PD2 (reservatório cheio), desligue a bomba de irrigação (uma saída digital) e acenda um LED indicativo;

//b)ao detectar qualquer mudança de nível em PB0 (botão de parada manual), 
//interrompa a irrigação imediatamente, independentemente do estado do reservatório. 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>



ISR(INT0_vect){ // Reservatório cheio (borda de subida em PD2)
  //Não preciso de if nesse tipo de interrupção pois já coloquei que vai ativar com subida(Logo botão começa em 0)
  PORTD |= (1<<PD5);   // acende LED indicativo
  PORTD &= ~(1<<PD4);  // desliga bomba de irrigação
}

ISR(PCINT0_vect){
        // Qualquer mudança de nível em PB0 (grupo PCINT0) interrompe a irrigação imediatamente
       PORTD &= ~(1<<PD4);  // desliga bomba de irrigação
}

void setup(){
  DDRD |= (1<<PD4);   // Bomba de irrigação (saída)
  DDRD |= (1<<PD5);   // LED (saída)
  DDRD &= ~(1<<PD2);  // Sensor de nível (entrada)
  DDRB &= ~(1<<PB0);  // Botão (entrada)

  EICRA |= (1<<ISC01) | (1<<ISC00); // borda de subida em INT0
  EIMSK |= (1<<INT0);               // habilita INT0
  //Interrupção INT posso especificar qual transição quero

  PCICR |= (1<<PCIE0);              // habilita grupo PCINT da Porta B
  PCMSK0 |= (1<<PCINT0);            // habilita PCINT0 (PB0)
  //Interrupção PCINT nào diferencia subida,descida etc, ele foca em ver se houve mudança

  PORTD &= ~(1<<PD5);  // LED desligado
  PORTD |= (1<<PD4);   // bomba começa ligada
  PORTD &= ~(1<<PD2);  // sem pull-up interno (sensor externo controla o nível)

  //Resumo 
  //Usa-se if com leitura de PINx dentro da ISR sempre que a condição configurada no
  //hardware (EICRA, no caso de INT0/INT1) não for específica o suficiente pra ação
  //desejada, ou quando é preciso identificar qual pino de um grupo PCINT causou o evento, 
  //ou ainda diferenciar subida de descida numa interrupção PCINT (que não tem esse filtro
  //por hardware). Quando a condição de disparo já é exatamente a que se precisa (ex: borda
  //de subida configurada e ação única pra essa borda), a checagem dentro da ISR é desnecessária.

  sei();
}

int main(void){
  setup(); //chama configuração

  while(1){
    // lógica desejada
  }
}
