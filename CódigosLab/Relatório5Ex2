#include <stdio.h>
#include <stdint.h>

// Posicao de cada sinal dentro do registrador "status"
#define BOTAO_A   0
#define BOTAO_B   1
#define BOTAO_C   2
#define MOTOR_M1  3   // 30HP
#define MOTOR_M2  4   // 50HP
#define MOTOR_M3  5   // 70HP

uint8_t status = 0;

uint16_t calculaPotencia(void) {
    uint16_t total = 0;
    if (status & (1 << MOTOR_M1)) total += 30;
    if (status & (1 << MOTOR_M2)) total += 50;
    if (status & (1 << MOTOR_M3)) total += 70;
    return total;
}

void atualizaMotores(void) {
    // espelha cada botao no motor correspondente
    if (status & (1 << BOTAO_A)) status = status | (1 << MOTOR_M1);
    else                         status = status & ~(1 << MOTOR_M1);

    if (status & (1 << BOTAO_B)) status = status | (1 << MOTOR_M2);
    else                         status = status & ~(1 << MOTOR_M2);

    if (status & (1 << BOTAO_C)) status = status | (1 << MOTOR_M3);
    else                         status = status & ~(1 << MOTOR_M3);

    // se passar de 90HP, desliga primeiro o de MENOR potencia (M1)
    if (calculaPotencia() > 90) {
        status = status & ~(1 << MOTOR_M1);
    }

    // se mesmo assim continuar acima de 90HP, desliga o de SEGUNDA menor potencia (M2)
    if (calculaPotencia() > 90) {
        status = status & ~(1 << MOTOR_M2);
    }
}

void mostrarStatus(const char *etapa) {
    printf("%-25s -> M1=%d M2=%d M3=%d | Potencia total = %dHP\n", etapa,
           (status & (1 << MOTOR_M1)) ? 1 : 0,
           (status & (1 << MOTOR_M2)) ? 1 : 0,
           (status & (1 << MOTOR_M3)) ? 1 : 0,
           calculaPotencia());
}

int main(void) {
    // Cenario 1: so botao A -> 30HP (ok)
    status = 0;
    status = status | (1 << BOTAO_A);
    atualizaMotores();
    mostrarStatus("Cenario 1 (A)");

    // Cenario 2: A + B -> 80HP (ok)
    status = status | (1 << BOTAO_B);
    atualizaMotores();
    mostrarStatus("Cenario 2 (A+B)");

    // Cenario 3: A + B + C -> 150HP, precisa desligar M1 e M2
    status = status | (1 << BOTAO_C);
    atualizaMotores();
    mostrarStatus("Cenario 3 (A+B+C)");

    // Cenario 4: B + C -> 120HP, so desligar M2 resolve (M1 nem tava ligado)
    status = status & ~(1 << BOTAO_A);
    atualizaMotores();
    mostrarStatus("Cenario 4 (B+C)");

    return 0;
}
