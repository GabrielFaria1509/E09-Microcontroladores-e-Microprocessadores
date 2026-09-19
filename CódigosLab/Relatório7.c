#include <util/delay.h>

void setup(){ //Arrumando configuração geral
    DDRD |= (1 << PD5); //Equivlente de DDRD = 0b11100000 //Pinos 7,6,5 saída(leds)
    DDRD |= (1 << PD6);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB1); //Equivlente de DDRB = 0b10000000  //Pino 15 saída(led)

    PORTD &= ~(1 << PD5);   //Deixando os LEDs apagados inicialmente (Seto em 0)
    PORTD &= ~(1 << PD6); //Começam em 0, PULL DOWN
    PORTD &= ~(1 << PD7);
    PORTB &= ~(1 << PB1);  //PB1 aqui é outro nome pro pino 15 

    //PCICR responsável por habilitar a interrupoção em determinado port(B,C,D)
    //PCMSK  responsável por habilitar a interrupoção em determinado pino de um port

       //====================================================================
    // ATENÇÃO: "PCINT" aparece em dois contextos DIFERENTES aqui, e isso
    // confunde bastante no começo. Vamos separar os dois significados:
    //
    // 1) PCINTx (pino) -> é o "apelido" de um pino físico específico.
    //    Ex: PCINT0 = pino PB0, PCINT20 = pino PD4, PCINT2 = pino PB2.
    //    Esse número (x) pode ir de 0 até 23 (23 pinos possíveis no total).
    //    É esse número que define QUAL BIT você vai setar dentro do PCMSK.
    //
    // 2) PCINTx_vect (grupo/vetor de interrupção) -> existem só 3 desses:
    //    PCINT0_vect, PCINT1_vect, PCINT2_vect.
    //    Cada um representa um PORT inteiro (PCINT0_vect = PORT B,
    //    PCINT1_vect = PORT C, PCINT2_vect = PORT D). É a ISR que vai
    //    rodar quando QUALQUER pino habilitado dentro daquele PORT mudar.
    //
    // Ou seja: "PCINT0" (pino, dentro de PCMSK0) e "PCINT0_vect" (grupo/ISR)
    // têm o mesmo número "0" mas não são a mesma coisa. PCINT0 é UM pino
    // específico do PORT B; PCINT0_vect é a ISR de TODO o PORT B.
    //====================================================================

    // PCICR (Pin Change Interrupt Control Register): habilita ou não a
    // interrupção em cada PORT inteiro (é o "disjuntor geral" de cada PORT).
    //   PCIE0 (bit 0) -> liga o grupo do PORT B (dispara PCINT0_vect)
    //   PCIE1 (bit 1) -> liga o grupo do PORT C (dispara PCINT1_vect)
    //   PCIE2 (bit 2) -> liga o grupo do PORT D (dispara PCINT2_vect)
    PCICR |= (1 << PCIE0) | (1 << PCIE2); // Habilitando PORT B e PORT D 
    //Equivalente a usar PCICR = 0b00000101
    

    // PCMSK0/1/2 (Pin Change Mask Register): dentro do PORT já habilitado
    // no PCICR, escolhe quais PINOS individuais vão gerar a interrupção
    // (é o "interruptor individual" de cada pino).
    //
    // PCMSK0 controla o PORT B -> aqui uso PCINT0 (pino PB0) e PCINT2 (pino PB2)
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT2);
    //Equivalente a fazer PCMSK0 = 0b00000101

    // PCMSK2 controla o PORT D -> aqui uso PCINT20 (pino PD4)
    PCMSK2 |= (1 << PCINT20);
    //Equivalente a fazer PCMSK2 = 0b00010000

    sei(); //Função para habilitar interrupções
   
}

//Funções de interrupção

ISR(PCINT0_vect){  //Função que é pra interrupções da família de pinos B
    if(PINB & (1 << PB0)){  //PCINT0(Pino) acionado
    //Como deixei em pull down a configuração inicial, a mudança é qd o led/pino vai pra 1

        PORTD |= (1 << PD7);

        _delay_ms(1000);

        PORTD &= ~(1 << PD7);

        _delay_ms(1000);
    }

    if(PINB & (1 << PB2)){  //PCINT2(Pino) acionado 
        PORTD |= (1 << PD6);

        _delay_ms(500);

        PORTD &= ~(1 << PD6);

        _delay_ms(500);
    }

    //Ambos pinos pertencem ao port B, logo uso PCINT0_vect
}

ISR(PCINT2_vect){  //Função pra interrupções da família de pinos D
    if(PIND & (1 << PD4)){ //PCINT20(Pino) acionado
        //Uso PORTB pois pino 15 é tb PB1 como nome
        //Mas o pino da interrupção que pede é da família D
        PORTB |= (1 << PB1);

        _delay_ms(2000);

        PORTB &= ~(1 << PB1);

        _delay_ms(2000);
    }
}

void loop(){
    //Led do pino 5 sempre piscando
    PORTD = PORTD | (1<<5);
    _delay_ms(250);
    PORTD = PORTD & ~(1<<5);
    _delay_ms(250);
}
