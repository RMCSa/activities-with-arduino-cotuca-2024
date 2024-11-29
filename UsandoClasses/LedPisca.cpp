/*
    Corpo da class onde escrevemos os codigos do construtor
    e dos métodos da class
*/
#include <Arduino.h>
#include "LedPisca.h"

LedPisca::LedPisca(int *pins, int num, int on, int off) {
    ledPins = pins;
    numLeds = num;
    onTime = on;
    offTime = off;
    ledStates = new int[numLeds]; // Aloca memória para o array de estados dos LEDs

    // Configura os pinos dos LEDs como saída
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        ledStates[i] = LOW;
    }
    
    previousMillis = 0;
}

long LedPisca::GetOnTime() {
    return onTime;
}

void LedPisca::SetOnTime(long on) {
    onTime = on;
}

long LedPisca::GetOffTime() {
    return offTime;
}

void LedPisca::SetOffTime(long off) {
    offTime = off;
}

void LedPisca::Update() {
    unsigned long currentMillis = millis();

    for (int i = 0; i < numLeds; i++) {
        if ((ledStates[i] == HIGH) && (currentMillis - previousMillis >= onTime)) {
            ledStates[i] = LOW;
            digitalWrite(ledPins[i], ledStates[i]);
            delay(500);
        } else if ((ledStates[i] == LOW) && (currentMillis - previousMillis >= offTime)) {
            ledStates[i] = HIGH;
            digitalWrite(ledPins[i], ledStates[i]);
            delay(500);
        }
    }

    // Atualiza o tempo anterior somente uma vez
    if (currentMillis - previousMillis >= max(onTime, offTime)) {
        previousMillis = currentMillis;
    }
}
