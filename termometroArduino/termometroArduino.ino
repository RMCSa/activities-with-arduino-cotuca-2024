/**
* Autores: Rafael Moreira Cavalcante de Souza - 23333
*          Marcelo Henrique Morello Manzo      -23326
*/
#include <LiquidCrystal.h>
#define pin_lm35 A0 //Pino o qual o sensor está conectado

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
int btn = 10;
int cont = 0;


void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600); // Inicia a comunicação com
  pinMode(pin_lm35, INPUT); // Define o sensor como uma entrada de sinal
  pinMode(btn, INPUT);
}
 
void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura");
  float valor_analog_lm35 = float(analogRead(pin_lm35)); // Obtém o valor analógico que varia de 0 a 1023
  float tensao = (valor_analog_lm35 * 5) / 1023; // Vamos converter esse valor para tensão elétrica
  float temperatura = tensao / 0.010; // dividimos a tensão por 0.010 que representa os 10 mV
  
  if (digitalRead(btn) == HIGH){
    cont++;
    delay(100);
  }

  if (cont % 2 == 0){
    lcd.setCursor(5,1);
    lcd.print(temperatura);
    lcd.print("C");
    delay(100);
  }
  else{
    float conversao_fahrenheit = (temperatura * 9/5) + 32;
    lcd.setCursor(5,1);
    lcd.print(conversao_fahrenheit);
    lcd.print("F");
    delay(100);
  }
  delay(100);
  
}

