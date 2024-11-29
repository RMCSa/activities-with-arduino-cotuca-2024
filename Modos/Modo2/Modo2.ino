// Rafael Moreira C de Souza - 23333
// Marcelo Manzo             - 23326
// 2: 2s On / 2s Off

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
int ledPin = 13;

void setup()
{
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
 
  // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0x7A12;
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
}

void loop() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Modo 02");
  delay(1000);
} 
 
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  TCNT1 = 0x7A12;                 // Renicia TIMER
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //inverte estado do led
}