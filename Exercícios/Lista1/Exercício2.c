#include <stdio.h>
#include<stdint.h>


//Escreva uma função void esperar_flag(void) que permaneça em loop enquanto uma flag 
//global sinal_pronto (simulando ser alterada por uma interrupção) estiver em 0. Declare a 
//flag com o qualificador correto para garantir que o compilador não otimize a leitura.

//Cabeçalho de referência: 
//void esperar_flag(void);

volatile uint16_t sinal_pronto = 0; //Flag alterada dentro de uma interrupção
// "volatile" avisa o compilador: "esse valor pode mudar a qualquer momento,
// por um motivo que você (compilador) não consegue enxergar no código"
// sem isso, o compilador acharia que só o próprio programa pode mudar o valor dela


void esperar_flag(void){
    
    while(!sinal_pronto); 
}


int main(void){
    
    
    esperar_flag(); //chama função 

    return 0;
}
