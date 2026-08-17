#include <stdio.h>
#include<stdint.h>


//Estados
typedef enum {
    INICIO,
    RAIO_X,
    CAMINHO_RETIRADA,
    RETIRADA,
    PARADA_EMERGENCIA,
    CAMINHO_ENTRADA

}Estados_esteira;

int main(void)
{
    uint8_t BI = 0;
    uint8_t BE = 0;
    uint16_t S2 = 0;
    uint8_t MOTOR = 0;
    
    Estados_esteira = estado INICIO;
    
    for(;;){
        switch(estado){

            case INICIO: 
            MOTOR = 0;

            if(BI == 1){
                estado = RAIO_X;
            }
            if(BE == 1){
                estado = PARADA_EMERGENCIA;
            }
            break;

            case RAIO_X:
            MOTOR = 1;

            if(_delay_ms == 5000){
                estado = CAMINHO_RETIRADA;
            }
            break;
            
            if(BE==1){
                estado = PARADA_EMERGENCIA;
            }
            break;

            case  CAMINHO_RETIRADA :
            MOTOR = 0;

            if(S2 == 1){
                estado = RETIRADA;
            }
            if(BE == 1){
                estado = PARADA_EMERGENCIA;
            }
            break;
            
            case RETIRADA:
            MOTOR = 0;
            break;

            if(BE == 1){
                estado = PARADA_EMERGENCIA;
            }
            break;

            case PARADA_EMERGENCIA;
            MOTOR = 1;
            break;

            default:
                break;

        }    
    }
}
