#include <stdio.h>      // biblioteca de entrada/saída padrão do C (equivalente ao <iostream>
#include<stdint.h>       // define tipos inteiros de tamanho fixo, como uint16_t (inteiro sem sinal de 16 bits)

uint16_t proxima_leitura(void){
    // "(void)" aqui é explícito e obrigatório em C para dizer "essa função não recebe parâmetros"
    // em C++ "()" já basta, mas em C puro "()" sozinho significa algo diferente (lista de parâmetros não especificada)

    static uint16_t contador = 0;
    // "static" dentro de função = variável que é inicializada só na primeira chamada
    // e mantém seu valor entre uma chamada e outra (não é recriada/zerada a cada execução)
    // é local à função (só ela enxerga), mas "sobrevive" no tempo, como se tivesse memória própria

    return contador++;
    
}

int main(void){

    printf("Primeira leitura : %u\n",proxima_leitura()+1);
  
    // "%u" é o especificador para inteiro sem sinal (unsigned), combina com uint16_t
   
    

    printf("Segunda leitura : %u\n",proxima_leitura()+1);
   

    printf("Terceira leitura : %u\n",proxima_leitura()+1);
   

    printf("Quarta leitura : %u\n",proxima_leitura()+1);
    

    return 0;
    
}
