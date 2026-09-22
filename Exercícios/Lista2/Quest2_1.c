#include <util/delay.h>//Para usar _delay_ms()
#include<stdio.h> //Para printf(),C base
#include <avr/io.h> //reconhece registradores


int main(void)
{
    DDRB &= ~((1 << PB0) + (1 << PB1) + (1 << PB2) + ( 1 << PB3) + (1 << PB4)); // Entradas
    DDRD |= (1 << PD0) ; //SAÍDAS //LED1
    DDRC |= (1 << PC0); //LED2

    PORTB = 0b00011111;  //Ativo pull up(Enquanto eu não pressionar eles estão em 1)

    PORTD &= ~(1 << PD0);   //Deixando os LEDs apagados inicialmente
    PORTC &= ~(1 << PC0);

    uint8_t botao; //Declaro variável para ler a entrada

    while(1){

        botao = PINB & PORTB; //Variável para ler PORTB de uma única vez
        // ou botao = PINB & 0b00011111
        
        //LED1 aceso e LED2 apagado
    if(botao == 0b10101 || botao == 0b01010){
        PORTD = PORTD | (1 << 0); 
        PORTC = PORTC & ~(1 << 0);

        //LED2 aceso e LED1 apagado
    }else if(botao == 0b00000 || botao == 0b11111){
        PORTC |= (1 << 0);
        PORTD &= ~(1<<0);
        //Ambos apagados
    }else{
        PORTD &= ~(1<<0);
        PORTC &= ~(1<<0);
    }


    

  }
}
