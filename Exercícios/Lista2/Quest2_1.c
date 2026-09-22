#include <util/delay.h>
#include<stdio.h>

int main(void)
{
    DDRB &= ~((1 << PB0) + (1 << PB1) + (1 << PB2) + ( 1 << PB3) + (1 << PB4)); // Entradas
    DDRD |= (1 << PD0) ; //SAÍDAS
    DDRC |= (1 << PC0);

    PORTB = 0b00011111;  //Ativo pull up(Enquanto eu não pressionar eles estão em 1)
}
