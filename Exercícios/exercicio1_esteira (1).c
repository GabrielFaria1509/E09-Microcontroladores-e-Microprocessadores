#include <stdio.h>
#include <stdint.h>

// Posicao de cada sinal dentro do registrador "status"
#define LIGA     0
#define DESLIGA  1
#define S1       2
#define MOTOR    3
#define ALARME   4

uint8_t status = 0;

void atualizaEsteira(void) {
    if (status & (1 << S1)) {
        // prioridade maxima: pecas amontoadas -> para tudo e liga alarme
        status = status & ~(1 << MOTOR);
        status = status | (1 << ALARME);
    }
    else if (status & (1 << DESLIGA)) {
        status = status & ~(1 << MOTOR);
    }
    else if (status & (1 << LIGA)) {
        if ((status & (1 << ALARME)) && !(status & (1 << S1))) {
            // pecas ja desamontoadas -> reset do alarme
            status = status & ~(1 << ALARME);
            status = status | (1 << MOTOR);
        }
        else if (!(status & (1 << ALARME))) {
            status = status | (1 << MOTOR);
        }
    }
}

void mostrarStatus(const char *etapa) {
    printf("%-45s -> MOTOR=%d  ALARME=%d\n", etapa,
           (status & (1 << MOTOR)) ? 1 : 0,
           (status & (1 << ALARME)) ? 1 : 0);
}

int main(void) {
    // Cenario 1: pressiona LIGA
    status = 0;
    status = status | (1 << LIGA);
    atualizaEsteira();
    mostrarStatus("Cenario 1: LIGA pressionado");

    // Cenario 2: pecas se amontoam (S1 = HIGH)
    status = status | (1 << S1);
    atualizaEsteira();
    mostrarStatus("Cenario 2: S1 = HIGH (amontoamento)");

    // Cenario 3: ainda amontoado, LIGA pressionado (nao deve funcionar)
    status = status | (1 << LIGA);
    atualizaEsteira();
    mostrarStatus("Cenario 3: LIGA pressionado, S1 ainda HIGH");

    // Cenario 4: pecas desamontoadas, LIGA pressionado -> reseta alarme
    status = status & ~(1 << S1);
    status = status | (1 << LIGA);
    atualizaEsteira();
    mostrarStatus("Cenario 4: S1 = LOW, LIGA pressionado -> reset do alarme");

    // Cenario 5: esteira rodando, pressiona DESLIGA
    status = status & ~(1 << LIGA);
    status = status | (1 << DESLIGA);
    atualizaEsteira();
    mostrarStatus("Cenario 5: DESLIGA pressionado");

    return 0;
}
