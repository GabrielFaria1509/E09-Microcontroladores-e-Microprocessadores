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
// (nesse caso, simulando uma interrupção de hardware alterando a variável por fora)
// sem isso, o compilador acharia que só o próprio programa pode mudar o valor dela


void esperar_flag(void){
    
  
    while(!sinal_pronto); 
    // enquanto sinal_pronto for 0, !sinal_pronto é verdadeiro -> loop continua rodando (vazio, o ";" fecha o while sem corpo)
    // a cada volta do loop, o compilador é OBRIGADO a ir na memória e ler o valor
    // atual de sinal_pronto de novo
    // sem "volatile", o compilador poderia pensar: "ninguém dentro dessa função
    // muda sinal_pronto, então vou ler o valor UMA vez, guardar num registrador,
    // e reusar sempre esse mesmo valor" -> isso geraria um loop infinito de verdade,
    // porque ele nunca iria checar a memória de novo pra ver se o valor mudou
    // com "volatile", essa otimização é proibida, garantindo que o loop sempre
    // vai perceber quando sinal_pronto mudar (por exemplo, por uma interrupção)

}


int main(void){
    
    
    esperar_flag(); //chama função 

    return 0;


}
