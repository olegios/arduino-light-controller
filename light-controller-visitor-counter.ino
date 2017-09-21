/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

The lighting control controller with visitor counter
whit two Infrared Distance Ranging Sensor E18-D80NK 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
#include <Arduino.h>
#include <DelayOn.h>

#define SWITCH_PIN       	2
#define REED_SWITCH_PIN  	4
#define SENSOR_OUTSIDE_PIN	5
#define SENSOR_INSIDE_PIN   	6
#define RELAY_FAN_PIN    	11
#define RELAY_LIGHT_PIN  	12
#define DELAY_ON_LIGHT   	5000 
#define DELAY_ON_FAN     	60000 //ms
//#define DEBUG			//for debugging must uncomment 

bool sensorOutsideState = false;
bool sensorInsideState = false;
bool sensorOutsideAlreadyTrigered = false;
bool sensorInsideAlreadyTrigered = false;
bool sensorTogetherAlreadyTrigered = false;
int whatSensorIsFirst=0;
int counterPerson = 0;

DelayOn TimerFan(RELAY_FAN_PIN, DELAY_ON_FAN); //create object timer for delay off
DelayOn TimerLight(RELAY_LIGHT_PIN,DELAY_ON_LIGHT);

void setup() {
  #ifdef DEBUG
  Serial.begin(9600); //Start serial communication boud rate at 9600
  #endif
  pinMode(RELAY_LIGHT_PIN, OUTPUT);   //Configure out for reley switch light
  pinMode(RELAY_FAN_PIN, OUTPUT);     //Configure out for reley fan
  pinMode(REED_SWITCH_PIN, INPUT);    //Configure input for reed switch
  pinMode(SENSOR_OUTSIDE_PIN, INPUT);     //IrSensor outside
  pinMode(SENSOR_INSIDE_PIN, INPUT);     //IrSensor inside
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);     
  attachInterrupt(0, Switch, CHANGE);
}

void loop(){
	if(digitalRead(REED_SWITCH_PIN) == LOW){   //when door is open start testing
	    ////////// check ir sensors   
		sensorOutsideState = !digitalRead(SENSOR_OUTSIDE_PIN); 	//inverse
	    sensorInsideState = !digitalRead(SENSOR_INSIDE_PIN); 	//inverse
	    if(!sensorOutsideState && !sensorInsideState){ 		//sensor inside off and sensor outside off
	     	////////// Analyze 
	     	if(whatSensorIsFirst > 0 && sensorTogetherAlreadyTrigered && sensorOutsideAlreadyTrigered && sensorInsideAlreadyTrigered){
	      		if(whatSensorIsFirst == 1){ 
	        		counterPerson++; 
	          			detachInterrupt(0);
	          			TimerFan.TurnOff();                  //fan turn off
	      		}else if (whatSensorIsFirst == 2){ 
	          				if(counterPerson > 0) { counterPerson--; }
	          				if(counterPerson == 0){
	            			attachInterrupt(0, Switch, CHANGE);
	            			TimerFan.TurnOn();              //start timer for fan off   
	            			TimerLight.TurnOn();            //start timer for light off
	          			}
	        		}
				#ifdef DEBUG        
			    Serial.println("SENSOR INSIDE OFF, SENSOR OUTSIDE OFF");
			    Serial.print("counterPerson=");
			    Serial.println(counterPerson);
				#endif      
		    }
		    sensorOutsideAlreadyTrigered = 0;
		    sensorInsideAlreadyTrigered = 0;
		    sensorTogetherAlreadyTrigered = 0;
		    whatSensorIsFirst = 0;
	    }  
	    else if(sensorOutsideState && !sensorInsideState){ //sensor inside on and sensor outside off
		    sensorOutsideAlreadyTrigered = 1;
		    if(!sensorInsideAlreadyTrigered) whatSensorIsFirst = 1; 
		    #ifdef DEBUG
		    Serial.print("whatSensorIsFirst = ");
		    Serial.print(whatSensorIsFirst);
		    Serial.println(" SENSOR INSIDE ON, SENSOR OUTSIDE OFF");
			#endif     
	    }  
	    else if(!sensorOutsideState && sensorInsideState){ //sensor inside off and sensor outside on
	     	sensorInsideAlreadyTrigered = 1;
	     	if(!sensorOutsideAlreadyTrigered) whatSensorIsFirst = 2;
		 	#ifdef DEBUG
	     	Serial.print("whatSensorIsFirst = ");
	     	Serial.print(whatSensorIsFirst);
	     	Serial.println(" SENSOR INSIDE OFF, SENSOR OUTSIDE ON");
		 	#endif
	    }  
	    else if(sensorOutsideState && sensorInsideState){ //sensor inside on and sensor outside on
		   sensorTogetherAlreadyTrigered = 1;
		   #ifdef DEBUG
		   Serial.print("whatSensorIsFirst = ");
		   Serial.print(whatSensorIsFirst);
		   Serial.print(" sensorTogetherAlreadyTrigered");
		   Serial.println(" SENSOR INSIDE ON, SENSOR OUTSIDE ON");
		   #endif
	    }  
  	} //READ_SWITCH
  	TimerFan.Check();   
    if(counterPerson > 0){ 
    	digitalWrite(RELAY_LIGHT_PIN, HIGH); //light turn on
	}else{	TimerLight.Check(); }
} // loop()

void Switch(){ 	//interrupt handling
  static unsigned long millis_prev; 
  if(millis()-100 > millis_prev){ 	//bounce protection
		TimerLight.TurnOn();		//start light off timer
    	#ifdef DEBUG
    	Serial.println("INTERUPT Switch()");
    	#endif
	}
  millis_prev = millis(); 
}   
