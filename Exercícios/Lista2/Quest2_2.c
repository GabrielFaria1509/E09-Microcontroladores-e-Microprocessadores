```c
#include <util/delay.h>//Para usar _delay_ms()
#include<stdio.h> //Para printf(),C base
#include <avr/io.h> //reconhece registradores


int main(void)
{
    DDRB &= ~((1 << PB1) + (1 << PB2) + ( 1 << PB3) + (1 << PB4)); // Entradas
    DDRD |= (1 << PD3) ; //SAÍDAS //Pino 3 porta D
    

    PORTB = 0b00011111;  //Ativo pull up(Enquanto eu não pressionar eles estão em 1)

    PORTD &= ~(1 << PD3);   //Fechadura travada

    uint8_t estado = 0; //Começo fechada a tranca

    while(1){

        if(estado == 0){
            if(!(PINB & (1<<PB2)) && (PINB & (1<<PB1)) && (PINB & (1<<PB3)) && (PINB & (1<<PB4))){
                estado = 1;
            }else{
                estado = 0;
            }
        }

        else if(estado == 1){
            if(!(PINB & (1<<PB2)) && !(PINB & (1<<PB3)) && (PINB & (1<<PB1)) && (PINB & (1<<PB4))){
                estado = 2;
            }else{
                estado = 0;
            }
        }
        else if(estado == 2){
            if(!(PINB & (1<<PB2)) && !(PINB & (1<<PB3)) && !(PINB & (1<<PB4)) && (PINB & (1<<PB1))){
                estado = 3;
            }else{
                estado = 0;
            }
        }
        else if(estado == 3){
            if(!(PINB & (1<<PB2)) && !(PINB & (1<<PB3)) && !(PINB & (1<<PB4)) && !(PINB & (1<<PB1))){
                estado = 4;
            }else{
                estado = 0;
            }
        }
        else if(estado == 4){
            if(!(PINB & (1<<PB2)) && !(PINB & (1<<PB3)) && !(PINB & (1<<PB4)) && !(PINB & (1<<PB1))){
                PORTD |= (1<<PD3);
            }else{
                PORTD &= ~(1<<PD3);
                estado = 0;
            }
        }
    }
}
```
