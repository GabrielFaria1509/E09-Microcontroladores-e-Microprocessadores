#define pwm_out (1 << PD6)
int brightness = 0; //variavel criada pra evitar manipular toda hora o OCR0A

int main() {
 
  // Serial.begin(9600);
  DDRD |= pwm_out;
  DDRD &= ~(1 << PD4);
  PORTD &= ~pwm_out;
  PORTD |= (1 << PD4);
  //CONFIGURAÇÃO DOS TEMPORIZADORES
  //TIMER 0 - MODO OVERFLOW
  TCCR0A |=  (1 << WGM01) |
             (1 << WGM00) |
             (1 << COM0A1);
;
  OCR0A = 0; //REGISTRADOR DE MODO DE FUNCIONAMENTO DO TIMER (OVERFLOW - COMPARAÇÃO - PWM)
  TCCR0B |= (1 << CS00); //REGISTRADOR QUE DEFINE O VALOR DO PRESCALER  
  //PWM = NAO USA TIMSK
 
  for(;;){
    if((PIND & (1 << PD4)) == 0){
      OCR0A = 128;
    }
    else{
     OCR0A = brightness;
    }
  }
}
