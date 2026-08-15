#include <stdio.h>
#include<stdint.h>


//Implemente a função uint16_t proxima_leitura(void), que retorna, a cada chamada, um
//número sequencial começando em 0 (0, 1, 2, 3...), sem usar variável global. Utilize static
//para preservar o contador entre chamadas.
uint16_t proxima_leitura(void){
    static uint16_t contador = 0;
    return contador++;
}


int main(void){
    
    printf("Primeira leitura : %u\n",proxima_leitura()+1);
    printf("Segunda leitura : %u\n",proxima_leitura()+1);
    printf("Terceira leitura : %u\n",proxima_leitura()+1);
    printf("Quarta leitura : %u\n",proxima_leitura()+1);

    return 0;
}

    
