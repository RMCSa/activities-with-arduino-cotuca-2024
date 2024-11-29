#include "LM35.h"
#include <Arduino.h>

LM35::LM35(int pin) : pin(pin) {
  pinMode(pin, INPUT);
}

float LM35::readCelsius() {
  float valorLM35 = float(analogRead(pin));
  float tensao = (valor_analogico * 5) / 1023;
  return tensao / 0.010;
}

float LM35::readFahrenheit() {
  float celsius = readCelsius();
  return (celsius * 9 / 5) + 32;
}
