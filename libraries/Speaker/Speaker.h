#ifndef Speaker_h
#define Speaker_h

#include <Arduino.h>

class Speaker {
  public:
    Speaker(int pwmPin);
    void begin();
    void flatTone(int frequency, int duration);
    void texasFight(int tempo);
    int frequency(char note);
  private:
    int _digitalPin;
};



#endif
