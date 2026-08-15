#include <stdio.h>
#include<stdint.h>

//Implemente a função void inverter_bits(uint8_t *buffer, uint8_t tamanho), que inverte
//(operador ~) cada byte de um buffer, alterando os dados originais diretamente através do
//ponteiro recebido — sem criar ou retornar um novo buffer.
//Cabeçalho de referência: 

//void inverter_bits(uint8_t *buffer, uint8_t tamanho); 

//Dica: use um laço for percorrendo o buffer pelo índice, e aplique ~buffer[i] a cada posição

void inverter_bits(uint8_t*buffer,uint8_t tamanho){

        for(uint8_t i = 0; i < tamanho; i++){
            buffer[i] = ~buffer[i];  //Já acessa diretamente, não precisa*
        }

        for(uint8_t i = 0; i < tamanho; i++){
            printf("Valor novo : %u\n",buffer[i]);
        }
    }

int main(void){
    
    uint8_t tam = 4;
    uint8_t buff[4];

    buff[0] = 1;
    buff[1] = 5;
    buff[2] = 3;
    buff[3] = 10;

    //buff sozinho já decai para * uint8_t
    inverter_bits(buff,tam);
    


    return 0;

}
