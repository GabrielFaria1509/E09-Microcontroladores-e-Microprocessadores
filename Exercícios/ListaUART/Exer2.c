
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>



void ADC_init(void) {

    // REFS0 = 1: utiliza AVcc (5V) como referencia de tensao
    // REFS1 = 0: completa a selecao da referencia AVcc
    // ADLAR = 0: resultado alinhado a direita
    // MUX = 0000: seleciona a entrada ADC0 (PC0)
    ADMUX = (1 << REFS0);

    // ADEN = 1: habilita o conversor ADC
    // ADPS2 = 1, ADPS1 = 1, ADPS0 = 1:
    // Prescaler = 128 (16 MHz / 128 = 125 kHz)
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
}



uint16_t ADC_read(void) {

    // ADSC = 1: inicia a conversao analogico-digital
    ADCSRA |= (1 << ADSC);

    // Aguarda enquanto a conversao estiver acontecendo
    
    while (ADCSRA & (1 << ADSC));

    // Retorna o resultado da conversao (10 bits: 0 a 1023)
    return ADC;
}

// ========================
// CONFIGURACAO DA UART
// ========================

void UART_init(void) {

    
    UBRR0 = 103;

    // TXEN0 = 1: habilita a transmissao UART
    UCSR0B = (1 << TXEN0);

    // UCSZ01 = 1 e UCSZ00 = 1:
    // 8 bits de dados
    // Sem paridade e 1 stop bit (configuracao padrao em zero)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}



void UART_send(uint8_t dado) {

    // Aguarda o registrador de transmissao ficar vazio
    while (!(UCSR0A & (1 << UDRE0)));

    // Coloca o dado no registrador para transmissao
    UDR0 = dado;
}



int main(void) {

    // Inicializa ADC e UART
    ADC_init();
    UART_init();

    uint16_t leitura;
    uint8_t temperatura;

    while (1) {

        // Realiza a leitura analogica do sensor
        leitura = ADC_read();

        // Converte a leitura ADC para temperatura em Celsius
        // Cada 10 mV corresponde a 1 grau Celsius
        temperatura = (leitura * 500UL) / 1023;

        // Envia a temperatura pela UART em 8 bits
        UART_send(temperatura);

        // Aguarda 500 milissegundos antes da proxima leitura
        _delay_ms(500);
    }
}
