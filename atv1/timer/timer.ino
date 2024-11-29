#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int segundosTotais = 1260; 
int tempoRestante;   
int minutos;           
int segundos;             

void setup() {
  lcd.begin(16, 2);
  tempoRestante = segundosTotais; 
}

void loop() {
  
  minutos = tempoRestante / 60;
  segundos = tempoRestante % 60;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cotuca Timer");
  lcd.setCursor(5, 1);
  lcd.print(minutos);
  lcd.print("m ");
  lcd.print(segundos);
  lcd.print("s");

  delay(1000); 
  tempoRestante--;


  if (tempoRestante < 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tchelo da o cu");
    lcd.setCursor(5, 1);
    lcd.print("Café");
    while (true) {} // Fica em um loop infinito
  }
}
