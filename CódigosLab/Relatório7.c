#include <util/delay.h>

void setup(){ //Arrumando configuração geral
    DDRD |= (1 << PD5); //Equivlente de DDRD = 0b11100000 //Pinos 7,6,5 saída(leds)
    DDRD |= (1 << PD6);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB1); //Equivlente de DDRB = 0b10000000  //Pino 15 saída(led)

    PORTD &= ~(1 << PD5);   //Deixando os LEDs apagados inicialmente
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    PORTB &= ~(1 << PB1);  //PB1 aqui é outro nome pro pino 15 

    // Pull-up interno nos botões
    // Botão solto = HIGH (1); botão pressionado = LOW (0)
    PORTB |= (1 << PB0);  // pull-up em PB0
    PORTB |= (1 << PB2);  // pull-up em PB2
    PORTD |= (1 << PD4);  // pull-up em PD4

    // PCICR: habilita interrupção nos PORTs B e D
    PCICR |= (1 << PCIE0) | (1 << PCIE2);

    // PCMSK0 controla o PORT B -> PCINT0 (PB0) e PCINT2 (PB2)
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT2);

    // PCMSK2 controla o PORT D -> PCINT20 (PD4)
    PCMSK2 |= (1 << PCINT20);

    sei(); //Habilita interrupções globais
}

ISR(PCINT0_vect){  //Interrupções da família de pinos B
    if(!(PINB & (1 << PB0))){  //PB0 em LOW = botão pressionado (pull-up)
        PORTD |= (1 << PD7);
        _delay_ms(1000);
        PORTD &= ~(1 << PD7);
        _delay_ms(1000);
    }

    if(!(PINB & (1 << PB2))){  //PB2 em LOW = botão pressionado (pull-up)
        PORTD |= (1 << PD6);
        _delay_ms(500);
        PORTD &= ~(1 << PD6);
        _delay_ms(500);
    }
}

ISR(PCINT2_vect){  //Interrupções da família de pinos D
    if(!(PIND & (1 << PD4))){  //PD4 em LOW = botão pressionado (pull-up)
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
