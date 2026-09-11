--Exercício 1
void setup() {
    DDRD = 0b00001110;
    DDRB = 0b00001110;

    PORTB = 0b00001110;

}

void loop() {
  // put your main code here, to run repeatedly:

}

--Exercício 2



void main(void) {
    
    DDRD = 0b00000000
    while(1){
      
      PORTD = 0b00000000;
      printf("00");
      _delay_ms(500);

      PORTD = 0b00000001;
      printf("01")
      _delay_ms(500);

      PORTD = 0b00000010;
      printf("10");
      _delay_ms(500);

      PORTD = 0b00000011;
      printf("11");
      _delay_ms(500);


    }

}

--Exercício3


void main(void) {
    
    DDRD = 0b00000000
    while(1){
      
      PORTD = 0b00000001;
      printf("01");
      _delay_ms(500);

      PORTD = 0b00000010;
      printf("10")
      _delay_ms(500);

      PORTD = 0b00000000;
      printf("00");
      _delay_ms(500);
    }

}




