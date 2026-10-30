#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define FOSC 16000000U            // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC / 16 / BAUD - 1)

char msg_tx[20];
volatile char msg_rx[32];
volatile int pos_msg_rx = 0;
int tamanho_msg_rx = 3;           // 3 dígitos: 000 a 100
volatile unsigned char msg_completa = 0;  // Avisa que os 3 dígitos já chegaram
unsigned int valor = 0;           // Duty cycle em % (0 a 100)

// Protótipos das funções
void UART_Init(unsigned int ubrr);
void UART_Transmit(char *dados);
void PWM_Init(void);

int main(void)
{
    UART_Init(MYUBRR);
    PWM_Init();
    sei();

    UART_Transmit("Digite o duty cycle com 3 digitos (000 a 100):\n");

    // Super-loop
    while (1)
    {
        if (msg_completa)                    // Chegaram os 3 caracteres?
        {
            msg_completa = 0;

            // Converte os caracteres ASCII em número (como no exemplo do roteiro)
            valor = (msg_rx[0] - 48) * 100 +
                    (msg_rx[1] - 48) * 10 +
                    (msg_rx[2] - 48) * 1;

            if (valor <= 100)                // Valor válido?
            {
                OCR0A = (valor * 255) / 100; // Converte 0-100% para 0-255 (8 bits)

                UART_Transmit("Duty cycle: ");
                itoa(valor, msg_tx, 10);
                UART_Transmit(msg_tx);
                UART_Transmit("%\n");
            }
            else
            {
                UART_Transmit("Valor invalido! Use 000 a 100\n");
            }
        }
    }
}

// Configura o Timer0 em Fast PWM no pino OC0A (PD6)
void PWM_Init(void)
{
    DDRD |= (1 << PD6);                          // PD6 (OC0A) como saída
    // Fast PWM (WGM01 e WGM00), saída não invertida em OC0A (COM0A1)
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    // Prescaler 64 (CS01 e CS00): frequência do PWM = 16 MHz / (64 * 256) ≈ 976 Hz
    TCCR0B = (1 << CS01) | (1 << CS00);
    OCR0A = 0;                                   // Começa com duty cycle 0%
}

// Interrupção de recepção da UART
ISR(USART_RX_vect)
{
    msg_rx[pos_msg_rx++] = UDR0;
    if (pos_msg_rx == tamanho_msg_rx)
    {
        pos_msg_rx = 0;
        msg_completa = 1;                // Os 3 dígitos chegaram: main pode converter
    }
}

void UART_Transmit(char *dados)
{
    while (*dados != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *dados;
        dados++;
    }
}

void UART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
