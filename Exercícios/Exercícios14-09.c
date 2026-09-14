#include <stdio.h>

ISR(INT0_vect){ //Função para isar o INT0
    PORTD = PORTD | 0b00010000;
  _delay_ms(1000);
  PORTD = PORTD &~ (0b00010000);
  _delay_ms(1000);
}

ISR(INT1_vect){ //Função para isar o INT1
    PORTD = PORTD | 0b00010000;
  _delay_ms(1000);
  PORTD = PORTD &~ (0b00010000);
  _delay_ms(1000);
}


int main()
{
     DDRD = 0b00110000;  //declara pino 5 e 4 como saída
     PORTD = 0b00000000; //Pinos 2,3 entrada
    
    //Letra A
    EICRA = 0b0001000; //Ativando INT1(Descida : 10)
    EIMSK = 0b00000010; //Declaro qual INT estou usando

    //Letra B
    EICRA = 0b00000011; //Ativando INT0(Subida : 11)
    EIMSK = 0b00000001; //Declaro qual INT estou usando

    //Letra C
    EICRA = 0b00001010; //Ativando INT0 e INT1 (Descida : 10)
    EIMSL = 0b00000011; //Declaro qual INT estou usando

    sei();


}
