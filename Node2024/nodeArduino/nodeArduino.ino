const int leds[] = {8,9};
char efeito;

void setup()
{
  Serial.begin(9600);
  Serial.println("Passou no setup");

  for (int i = 0; i < 2; i++)  {
  	pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    char readFromNode;
    readFromNode = (char) Serial.read();
    convertToState(readFromNode);
  }

  switch (efeito){
    case '1':
      for (int i = 0; i < 2; i++) {
      digitalWrite(leds[i], HIGH);
      delay(100);
      }
      break;

    case '2':
      for (int i = 0; i < 2; i ++) {
      digitalWrite(leds[i], LOW);
      delay(100);
      }
      break;

  }
}

void convertToState(char chr) {
  if (chr == '1' || chr == '2') {
    efeito = chr;
  }

  delay(100);
}