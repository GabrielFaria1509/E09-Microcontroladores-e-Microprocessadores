#include <stdio.h>
#include<stdint.h>

//Escreva a função void ler_bateria(uint8_t *tensao, uint8_t *nivel), que simula a leitura da
//tensão da bateria (atribua um valor fixo, ex.: 37 para 3.7V) e calcula o nível correspondente
//(0 a 100), escrevendo os dois resultados diretamente nos endereços recebidos.
//Cabeçalho de referência: 

//void ler_bateria(uint8_t *tensao, uint8_t *nivel);


void ler_bateria(uint8_t *tensao, uint8_t *nivel){  //declaro os ponteiros
    *tensao = 37; //a função que define , uso os ponteiros que declarei na chamada
    *nivel = *tensao * 2;

}


int main(void){
    
    uint8_t tens;
    uint8_t bat;

    ler_bateria(&tens,&bat); // & pega o endereço de tens e bat, que é atribuído aos ponteiros tensao e nivel dentro da função
    //ao receber o endereço da variável , a função escreve direto no orginal, sem cópias

    printf("Tensao e bateria respectivamente : %u , %u\n",tens,bat);

    return 0;

}
