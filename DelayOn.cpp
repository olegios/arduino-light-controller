/*
  Delay object timer
*/
 
#include "DelayOn.h"
    
DelayOn::DelayOn(int pin, long time){
	_pinOut = pin;
  _interval = time;
  _currentMillis = 0;
  _previousMillis = 0;
}
    
void DelayOn::TurnOn(){
    _previousMillis = millis();
    if (digitalRead(_pinOut) == LOW){
       digitalWrite(_pinOut, HIGH); 
    } 
}

void DelayOn::TurnOff(){
    if (digitalRead(_pinOut) == HIGH){
        digitalWrite(_pinOut, LOW); 
    }
}

void DelayOn::Check(){
    _currentMillis = millis();
    if( (_currentMillis - _previousMillis) > _interval){
       _previousMillis = _currentMillis;  
       TurnOff();
	}

}