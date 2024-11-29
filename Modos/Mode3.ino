// Rafael Moreira C de Souza - 23333
// Marcelo Manzo             - 23326
// 3: 2s On / 1s Off

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int ledPin = 13;
int mode = 3;
void setup()
{
  pinMode(ledPin, OUTPUT);
 
  // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  if (mode == 3) {
    mode = 2;
  }

  setupTimer();   // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  TCNT1 = 0x7A12;
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
}

void loop() {} 


void setupTimer()
{
 
  switch (mode) {
      case 1:
      mode = 2;
      break;
      case 2:
      mode = 1;
      break;
  }
  
  switch (mode) {
    case 1:
      TCNT1 = 0xC2F7;
      break;
    case 2:
      TCNT1 = 0x7A12;
      break;
  }
}
 
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 
{
  setupTimer();                     // Renicia TIMER
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //inverte estado do led
}