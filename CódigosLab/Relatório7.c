
Claude terminou a resposta
//Pergunta : Utilizando o ATMega328p, escreva as linhas de código (registradores PCICR e PCMSKn) necessárias para habilitar interrupções por mudança de pino (PCINT) nos 
//seguintes pinos: PB2, PB5, PC0 e PD7. Indique explicitamente quais bits de PCICR e quais registradores PCMSKn precisam ser configurados, e justifique cada escolha. 

#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setup(){

    DDRD |= (1<<PD3);  //Saídas
    DDRB |= (1<<PB6);
    DDRC |= (1<<PC7);

    DDRC &= ~(1<<PC2); //Entradas 
    DDRB &= ~(1<<PB2);
    DDRB &= ~(1<<PB5);
    DDRD &= ~(1<<PD7);

    PORTD &= ~(1 << PD3);   //Deixando os LEDs apagados inicialmente
    PORTB &= ~(1 << PB6);  
   PORTC &= ~(1 << PC7);  

    PORTD |= (1 << PD7);   //Deixando entradas em PULL UP
    PORTB |= (1 << PB5);
    PORTC |= (1 << PC1);
    PORTB |= (1 << PB2);

  //PICINT0  A PCINT7 == PORTA B
  //PCINT8 A PCINT14 == PORT c
  //PCINT 16 A PCINT23 == PORTA D

  PCICR = 0b00000111;
  //Ativo os 3 primeros bits, pois cada um representa a porta que possui os pinos que vão sofrer interrupção
  //Ou PCICR |= (1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2); //Vou usar os 3 PINT(B,C,D)

   PCMSK0 = 0b00100100;
    // Bit 2 = PCINT2 (PB2) e bit 5 = PCINT5 (PB5)
    // Ou: PCMSK0 |= (1<<PCINT2) | (1<<PCINT5);

    PCMSK1 = 0b00000001;
    // Bit 0 = PCINT8 (PC0)
    // Ou: PCMSK1 |= (1<<PCINT8);

    PCMSK2 = 0b10000000;
    // Bit 7 = PCINT23 (PD7)
    // Ou: PCMSK2 |= (1<<PCINT23);

}

int main(void){

  //...(Lógica desejada)

}

}

Boa, você anotou o mapeamento correto nos comentários agora. A parte de PCICR/PCMSK continua certa. Mas ainda tem problemas a resolver:

1) PC7 ainda não existe — você ainda usa DDRC |= (1<<PC7) e PORTC &= ~(1<<PC7), mas a Porta C só vai até PC6. Precisa trocar por um pino válido, tipo PC1 — só que...

2) Você já está usando PC1 como saída (PORTC |= (1<<PC1)) — só que a questão pede PC0 como um dos pinos de interrupção (você deixou como entrada certinho: DDRC &= ~(1<<PC2)... espera, aqui é outro problema:

3) Você configurou PC2 como entrada, mas a questão pede PC0. PCMSK1 está mascarando PCINT8 (PC0) corretamente, mas no setup() o pino que você deixou como entrada com pull-up foi o PC2, não o PC0. Isso é uma inconsistência: o registrador de máscara está monitorando PC0, mas fisicamente é o PC2 que está configurado como entrada. Precisa ser:

c
DDRC &= ~(1<<PC0);   // PC0 como entrada (não PC2)
PORTC |= (1<<PC0);   // pull-up em PC0 (não PC1)
4) Ainda faltam: a chave extra sobrando no fim do arquivo, e o main() sem chamar setup() nem sei().

Versão final corrigida do setup() e main():

c
void setup(){
    DDRD |= (1<<PD3);   // LED saída
    DDRB |= (1<<PB6);   // LED saída
    DDRC |= (1<<PC1);   // LED saída (troquei PC7, que não existe, por PC1)

    DDRC &= ~(1<<PC0);  // PC0 como entrada (pedido pela questão)
    DDRB &= ~(1<<PB2);  // PB2 como entrada (pedido pela questão)
    DDRB &= ~(1<<PB5);  // PB5 como entrada (pedido pela questão)
    DDRD &= ~(1<<PD7);  // PD7 como entrada (pedido pela questão)

    PORTD &= ~(1<<PD3);
    PORTB &= ~(1<<PB6);
    PORTC &= ~(1<<PC1);

    PORTC |= (1<<PC0);  // pull-up em PC0
    PORTB |= (1<<PB5);  // pull-up em PB5
    PORTB |= (1<<PB2);  // pull-up em PB2
    PORTD |= (1<<PD7);  // pull-up em PD7

    // PCINT0 a PCINT7 = Porta B
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
me manda logo sa porra certa ent q copio e colo

c
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

