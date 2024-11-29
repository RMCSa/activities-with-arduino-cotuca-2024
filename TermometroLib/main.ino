/*
  Autor: Rafael Moreia Cavalcante de Souza
  RA: 23333
*/

#include "LM35.h"

#define PIN_LM35 A0
#define BTN_PIN 10

LM35 sensor(PIN_LM35);
bool wasPressed = true;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  
  if (digitalRead(BTN_PIN) == HIGH) {
    Serial.println(digitalRead(BTN_PIN) + " estado btn");
    wasPressed = !wasPressed;
    delay(100);
  }

  if (wasPressed) {
    float temperaturaC = sensor.readCelsius();
    Serial.print("Temperatura: ");
    Serial.print(temperaturaC);
    Serial.println("° C"); 
    delay(1000); 
  } else {
    float temperaturaF = sensor.readFahrenheit();
    Serial.print("Temperatura: ");
    Serial.print(temperaturaF);
    Serial.println("° F");
    delay(1000); 
  }
}
