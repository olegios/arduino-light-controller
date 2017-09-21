#ifndef DELAY_ON_H
#define DELAY_ON_H
  
#include <Arduino.h>

class DelayOn {
  private:
    int _pinOut;
    long _interval;
    unsigned long _currentMillis;
    long _previousMillis;
  public:
    DelayOn(int pin, long time);
    void TurnOn();  
    void TurnOff();     
    void Check();

};
#endif