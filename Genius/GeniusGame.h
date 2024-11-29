#ifndef GENIUSGAME_H
#define GENIUSGAME_H

#include <Arduino.h>

#define ledVerde 2
#define ledVermelho 3
#define ledAmarelo 4
#define ledAzul 5
#define btnVerde 8
#define btnVermelho 9
#define btnAmarelo 10
#define btnAzul 11
#define btnIniciarParar 7
#define pinBuzzer 13
#define indefinido -1
#define tamanhoSequencia 4

// Enum criado para auxiliar o programa na identificação do estado atual do jogo
enum Estados {
  PROXIMA_RODADA,
  ESPERANDO_RESPOSTA,
  SUCESSO,
  ERRO,
  PAUSADO
};

class GeniusGame {
public:
  GeniusGame();
  void inicia();
  void loop();

//Métodos, funções e variáveis responsáveis por garantir o funcionamento do jogo
private:
  int sequenciaLuzes[tamanhoSequencia];
  int rodada = 0;
  int ledsRespondidos = 0;
  bool jogoIniciado = false;

  void restart_game();
  void preparaNovaRodada();
  void processaRespostaUsuario();
  int estadoAtual();
  void tocaLedsRodada();
  int checaRespostaJogador();
  void sucesso();
  void erro();
  int piscaLed(int portaLed);
  int piscaLedSucesso(int portaLed);
  void tocaSom(int frequencia);
  void verificaSomDoLed(int portaLed);
  int sorteiaCor();
};

#endif
