#include "LedPisca.h"

const int ledPins[] = {13, 12, 11}; // pinos LEDs
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // sizeof retorna o tamanho em bytes. Então, se dividirmos o tamanho total da array em bytes pelo tamanho de um elemento, obtemos o número de elementos na array.

LedPisca leds = LedPisca(ledPins, numLeds, 500, 500);

void setup() {

}

void loop() {
    leds.Update();
    delay(100);
}
