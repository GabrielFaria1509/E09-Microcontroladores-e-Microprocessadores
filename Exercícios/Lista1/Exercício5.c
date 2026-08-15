#include <stdio.h>
#include<stdint.h>

//Crie uma macro IS_BIT_SET(reg, bit) que retorne 1 se o bit indicado estiver ligado em reg, e 
//0 caso contrário. Reescreva a verificação do campo erro do Exercício 3 (item status->erro) 
//utilizando essa macro. 

//Cabeçalho de referência: 

//#define IS_BIT_SET(reg, bit) (((reg) >> (bit)) & 1) 

#define IS_BIT_SET(reg,bit) (((reg)>> (bit)) & 1) //macro permite definir um código reutilizável, como uma operação

int main(void){
    
    uint8_t reg; // é o número base
    uint8_t bit; // é a posição que quero checar, deslocar os bits de reg bit vezes pra direitra

    bit = 7;
    reg = 1;

    if (IS_BIT_SET(reg,bit)){
        printf("Bit na posição %u ligado em %u",bit,reg);
        return 1;
    }else{
        printf("Bit desativado na posição %u em %u",bit,reg);
        return 0;
    }

}
