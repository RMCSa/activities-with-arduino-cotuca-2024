#ifndef LED_PISCA_H
#define LED_PISCA_H

#include <Arduino.h>

class LedPisca {
private:
    int *ledPins;           // Ponteiro para o array de pinos dos LEDs
    int numLeds;            // Número de LEDs no array
    long onTime;            // Tempo em milissegundos que o LED fica aceso
    long offTime;           // Tempo em milissegundos que o LED fica apagado
    int *ledStates;         // Array para guardar o estado de cada LED
    unsigned long previousMillis;   // Guarda o tempo da última mudança de estado

public:
    LedPisca(int *pins, int num, int on, int off); // Construtor
    long GetOnTime();       // Retorna o tempo que o LED fica aceso
    void SetOnTime(long on);    // Seta o tempo que o LED fica aceso
    long GetOffTime();      // Retorna o tempo que o LED fica apagado
    void SetOffTime(long off);   // Seta o tempo que o LED fica apagado
    void Update();          // Atualiza o estado de múltiplos LEDs
};

#endif
