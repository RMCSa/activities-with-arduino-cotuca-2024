/* Header  */

#ifndef SAIDA_H
#define SAIDA_H

#include <Arduino.h>


class Saida
{
    private:
        int _pino;

    public:
        Saida(int pino);
        void ligar();
        void desligar();
        void inverter();
        void setPino(int pino);
        int getPino();
        bool getEstado();
        void setEstado(bool estado); 

}

#endif