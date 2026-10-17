#include <util/delay.h>   // necessário para o _delay_ms

#define pwm_out (1 << PD6)
volatile int brightness = 0; //0 a 100 (%) - volatile porque muda dentro da ISR

ISR(INT0_vect){
  brightness += 10;          // +10% de luminosidade
  if(brightness > 100){      // passou de 100%?
    brightness = 0;          // volta para 0 (LED apaga)
  }
  _delay_ms(200);            // debounce simples (pode tirar no simulador)
}

int main() {

  DDRD |= pwm_out;
  DDRD &= ~(1 << PD2);   //PD2 = INT0 (entrada)
  PORTD &= ~pwm_out;
  PORTD |= (1 << PD2);   //pull-up no botao

  //CONFIGURAÇÃO DO TIMER 0 - MODO FAST PWM

  // TCCR0A = registrador de controle A do Timer0 (modo de operação + comportamento do pino)
  TCCR0A |=  (1 << WGM01) |   // WGM01 = 1 \ junto com WGM00 = 1 e WGM02 = 0 (padrão, fica em TCCR0B),
             (1 << WGM00) |   // WGM00 = 1 / seleciona o modo 3: FAST PWM, contagem de 0 até 255 (TOP = 0xFF)
             (1 << COM0A1);   // COM0A1 = 1 e COM0A0 = 0: modo NÃO INVERTIDO no pino OC0A (PD6):
                              //   - pino vai para 1 quando TCNT0 zera (BOTTOM)
                              //   - pino vai para 0 quando TCNT0 == OCR0A (compare match)

  // OCR0A = registrador de comparação. Define o duty cycle:
  // o pino fica em 1 de 0 até OCR0A, e em 0 de OCR0A até 255
  // OCR0A = 0 -> quase sempre desligado | OCR0A = 255 -> sempre ligado
  OCR0A = 0;

  // TCCR0B = registrador de controle B do Timer0 (escolhe o clock do timer)
  TCCR0B |= (1 << CS00);      // CS02 = 0, CS01 = 0, CS00 = 1: SEM PRESCALER (clock do timer = 16 MHz)
                              // Frequência do PWM = 16 MHz / 256 = 62,5 kHz
                              // (o timer só começa a contar depois desta linha)

  //INTERRUPÇÃO EXTERNA INT0 - BORDA DE DESCIDA
  EICRA |= (1 << ISC01);      // ISC01 = 1 e ISC00 = 0: interrupção na borda de descida (botão sendo apertado)
  EIMSK |= (1 << INT0);       // habilita a interrupção externa INT0
  sei();                      // habilita as interrupções globais

  for(;;){
    if(brightness == 0){
      TCCR0A &= ~(1 << COM0A1);              // desconecta o PWM do pino (COM0A1 = 0 -> pino volta a ser porta normal)
      PORTD &= ~pwm_out;                     // garante LED apagado
    }
    else{
      TCCR0A |= (1 << COM0A1);               // reconecta o PWM ao pino
      OCR0A = (brightness * 255) / 100;      // converte % (0-100) para 0-255
    }
  }
}
