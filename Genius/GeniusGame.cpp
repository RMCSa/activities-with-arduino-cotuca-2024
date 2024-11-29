#include "GeniusGame.h"

const int leds[] = {ledVerde, ledVermelho, ledAmarelo, ledAzul};

GeniusGame::GeniusGame() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(btnVerde, INPUT_PULLUP);
  pinMode(btnAmarelo, INPUT_PULLUP);
  pinMode(btnVermelho, INPUT_PULLUP);
  pinMode(btnAzul, INPUT_PULLUP);
  pinMode(btnIniciarParar, INPUT_PULLUP);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
}

void GeniusGame::inicia() {
  int jogo = analogRead(0);
  randomSeed(jogo);

  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    digitalWrite(leds[i], LOW);
  }
  delay(500);

  for (int i = 0; i < tamanhoSequencia; i++) {
    sequenciaLuzes[i] = sorteiaCor();
  }
}

int GeniusGame::sorteiaCor() {
  return random(ledVerde, ledAzul + 1);
}

void GeniusGame::loop() {
  if (digitalRead(btnIniciarParar) == LOW) {
    restart_game();
  }

  switch (estadoAtual()) {
    case PROXIMA_RODADA:
      preparaNovaRodada();
      break;
    case ESPERANDO_RESPOSTA:
      processaRespostaUsuario();
      break;
    case SUCESSO:
      sucesso();
      break;
    case ERRO:
      erro();
      break;
    case PAUSADO:
      break;
  }
  delay(500);
}

void GeniusGame::restart_game() {
  rodada = 0;
  ledsRespondidos = 0;
  jogoIniciado = false;
  inicia();
}

void GeniusGame::preparaNovaRodada() {
  rodada++;
  ledsRespondidos = 0;
  if (rodada <= tamanhoSequencia) {
    tocaLedsRodada();
  }
}

void GeniusGame::processaRespostaUsuario() {
  int resposta = checaRespostaJogador();
  if (resposta == indefinido) {
    return;
  }
  if (resposta == sequenciaLuzes[ledsRespondidos]) {
    ledsRespondidos++;
  }
  else {
    rodada = tamanhoSequencia + 2;
  }
}

int GeniusGame::estadoAtual() {
  if (!jogoIniciado) {
    if (digitalRead(btnIniciarParar) == LOW) {
      jogoIniciado = true;
      return PROXIMA_RODADA;
    }
    else {
      return PAUSADO;
    }
  }

  if (rodada <= tamanhoSequencia) {
    if (ledsRespondidos == rodada) {
      return PROXIMA_RODADA;
    }
    else {
      return ESPERANDO_RESPOSTA;
    }
  }
  else if (rodada == tamanhoSequencia + 1) {
    jogoIniciado = false;
    return SUCESSO;
  }
  else {
    jogoIniciado = false;
    return ERRO;
  }
}

void GeniusGame::tocaLedsRodada() {
  for (int i = 0; i < rodada; i++) {
    piscaLed(sequenciaLuzes[i]);
  }
}

int GeniusGame::checaRespostaJogador() {
  if (digitalRead(btnVerde) == LOW) {
    return piscaLed(ledVerde);
  }
  if (digitalRead(btnAmarelo) == LOW) {
    return piscaLed(ledAmarelo);
  }
  if (digitalRead(btnVermelho) == LOW) {
    return piscaLed(ledVermelho);
  }
  if (digitalRead(btnAzul) == LOW) {
    return piscaLed(ledAzul);
  }
  return indefinido;
}

void GeniusGame::sucesso() {
  delay(250);
  tocaSom(5000);
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    piscaLedSucesso(leds[i]);
    delay(10);
  }
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    piscaLedSucesso(leds[i]);
    delay(10);
  }
}

void GeniusGame::erro() {
  for(int i = 0; i < 2; i++){
    delay(250);
    tocaSom(400);
    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
      digitalWrite(leds[i], LOW);
    }
    delay(250);
  }
}

int GeniusGame::piscaLed(int portaLed) {
  verificaSomDoLed(portaLed);
  digitalWrite(portaLed, HIGH);
  delay(1000);
  digitalWrite(portaLed, LOW);
  delay(250);
  return portaLed;
}

int GeniusGame::piscaLedSucesso(int portaLed) {
  verificaSomDoLed(portaLed);
  digitalWrite(portaLed, HIGH);
  delay(250);
  digitalWrite(portaLed, LOW);
  delay(250);
  return portaLed;
}

void GeniusGame::tocaSom(int frequencia) {
  tone(pinBuzzer, frequencia, 100);
}

void GeniusGame::verificaSomDoLed(int portaLed) {
  switch (portaLed) {
    case ledVerde:
      tocaSom(2000);
      break;
    case ledAmarelo:
      tocaSom(2200);
      break;
    case ledVermelho:
      tocaSom(2400);
      break;
    case ledAzul:
      tocaSom(2500);
      break;
  }
}
