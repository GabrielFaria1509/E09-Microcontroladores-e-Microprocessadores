#include <stdio.h>
#include<stdint.h>

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

    
