#ifndef LM35_H
#define LM35_H

class LM35 {
  public:
    LM35(int pin);
    float readCelsius();
    float readFahrenheit();

  private:
    int pin;
};

#endif
