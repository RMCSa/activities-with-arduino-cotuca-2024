#define MI 659
#define FA 698
#define SOL 784
#define LA 880
#define SI 987
#define DO 523
#define RE 587
#define Pausa 0

String serialData;
int pin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}
 
void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.readStringUntil('\n');
    Serial.println(serialData);
  }
  if (serialData.equals("RA23333")) {
    Serial.println("Musica 01");
    tocarMusica01();
  } else if (serialData.equals("RA23326")) {
    Serial.println("Musica 02 ");
    tocarMusica02();
  } else {
    noTone(pin);
  }
}

void tocarMusica01(){
  tone(pin, MI, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, MI, 400);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, MI, 400);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, SOL, 200);
    delay(200);
    tone(pin, DO, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, LA, 400);
    delay(400);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, SI, 400);
    delay(400);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, SI, 400);
    delay(400);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, SOL, 200);
    delay(200);
    tone(pin, DO, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, LA, 400);
    delay(400);
    noTone(pin);
}

void tocarMusica02(){
  tone(pin, MI, 200);
    delay(200);
    tone(pin, SOL, 200);
    delay(200);
    tone(pin, LA, 400);
    delay(400);
    tone(pin, FA, 400);
    delay(400);
    tone(pin, MI, 400);
    delay(400);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, RE, 400);
    delay(400);
    tone(pin, DO, 400);
    delay(400);
    tone(pin, SI, 400);
    delay(400);
    tone(pin, DO, 200);
    delay(200);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, MI, 400);
    delay(400);
    tone(pin, RE, 400);
    delay(400);
    tone(pin, DO, 200);
    delay(200);
    tone(pin, SI, 200);
    delay(200);
    tone(pin, DO, 400);
    delay(400);
    tone(pin, RE, 400);
    delay(400);
    tone(pin, MI, 400);
    delay(400);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, SOL, 400);
    delay(400);
    tone(pin, FA, 400);
    delay(400);
    tone(pin, MI, 400);
    delay(400);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, SOL, 400);
    delay(400);
    tone(pin, FA, 400);
    delay(400);
    tone(pin, MI, 400);
    delay(400);
    tone(pin, RE, 200);
    delay(200);
    tone(pin, MI, 200);
    delay(200);
    tone(pin, DO, 400);
    delay(400);
    tone(pin, SI, 400);
    delay(400);
    noTone(pin);
}
