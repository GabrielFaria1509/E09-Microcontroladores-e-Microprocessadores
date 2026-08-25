#include <stdio.h>
#include<stdint.h>

int main(void) {
    //Exercício 1
    unsigned char valor = 0b01111111; // 127 em binário

    printf("Valor original: ");
    for (int i = 7; i >= 0; i--) printf("%d", (valor >> i) & 1);
    printf("\n");

    // Ativando o bit mais significativo (bit 7)
    valor = valor | 0b10000000; // 01111111 OU 10000000 = 11111111
    printf("Apos ativar bit 7: ");
    for (int i = 7; i >= 0; i--) printf("%d", (valor >> i) & 1);
    printf("\n");

    // Desativando os 2 bits menos significativos
    unsigned char mascara = 0b00000011; // bits que quero desativar
    unsigned char mascaraInvertida = ~mascara; // NOT: 11111100
    valor = valor & mascaraInvertida; // 11111111 E 11111100 = 11111100
    printf("Apos desativar bits 0 e 1: ");
    for (int i = 7; i >= 0; i--) printf("%d", (valor >> i) & 1);
    printf("\n");

    // Ativando apenas o bit 5
    valor = valor | 0b00100000; // 11111100 OU 00100000 = 11111100
    printf("Apos ativar bit 5: ");
    for (int i = 7; i >= 0; i--) printf("%d", (valor >> i) & 1);
    printf("\n");

    //Teste se o bit 6 está Ativando
    if(valor & (1<<6)){
    printf("Bit 6 ativo\n");
    } else {
    printf("Bit 6 desativado\n");
    }

    //Vendo se bit 3 está em 0
    if(!(valor & (1<<3))){
    printf("Bit 3 desativado\n");
    } else {
    printf("Bit 3 ativo\n");
    }

    //Exercício 2

    uint8_t status = 0b11100000; // 

    if(status & (1<<7)){
        printf("Sensor 1 ativado, ligando motor 2\n");
        status = status | (1<<1);
    }

    if(status & (1<<6)){
        printf("Sensor 2 ativado, ligando motor 1 \n");
        status = status | (1<<0);
    }

    if(status & (1<<5)){
        status = status^((1<<0)+(1<<1));
    }

    if(!(status & ((1<<7)+(1<<6)+(1<<5)))){
        printf("Sensores desligados,desligando motores");
        status = status &~((1<<1)+(1<<0));
    }

    


    return 0;
}
