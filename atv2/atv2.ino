
#include <LiquidCrystal.h>
#define pin_lm35 A0 //Pino o qual o sensor está conectado

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600); // Inicia a comunicação com
  pinMode(pin_lm35, INPUT); // Define o sensor como uma entrada de sinal
}
 
void loop()
  lcd.clear();
  lcd.setCursor(0, 0);

  float valor_analog_lm35 = float(analogRead(pin_lm35)); // Obtém o valor analógico que varia de 0 a 1023
  float tensao = (valor_analog_lm35 * 5) / 1023; // Vamos converter esse valor para tensão elétrica
  float temperatura = tensao / 0.010; // dividimos a tensão por 0.010 que representa os 10 mV
  float conversao_fahrenheit = (temperatura * 9/5) + 32;
  
  Serial.print("A temperatura eh ");
  lcd.setCursor(0,1);
  Serial.println(conversao_fahrenheit); // Mostra na serial a temperatura do sensor
  delay(1000);
}

