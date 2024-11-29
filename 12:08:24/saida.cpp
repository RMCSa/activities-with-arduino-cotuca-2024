
/*Corpo da classe Saída*/
#include "saida.h"

// Construtor
Saida::Saida(int pino)
{
    pinMode(_pino, OUTPUT);
    _pino = pino;
}

//Outros Métodos da classe
void Saida::ligar()
{
    digitalWrite(_pino, HIGH);
}

void Saida::desligar()
{
    digitalWrite(_pino, LOW);
}

void Saida::inverter()
{
    digitalWrite(_pino, !digitalRead(_pino));
}

void Saida::setPino(int pino)
{
    _pino = pino;
}

int Saida::getPino()
{
    return _pino;
}

bool Saida::getEstado()
{
    return digitalRead(_pino);
}

void Saida::setEstado(bool estado)
{
    digitalWrite(_pino, estado);
}

