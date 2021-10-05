#include "Rotaryencoder.h"
#include <Arduino.h> 
 #include "config.h"
float counter = 0; 
int aState;
int aLastState; 

unsigned long mappingEncoder(int A, int B,int valMax){
    aState = digitalRead(A); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState){     
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(B) != aState) {
        if(counter >0){
          counter -=1;
        }
      } else {
        if(counter<valMax){ 
          counter +=1;
        }
      }
      //Serial.println("Counter: " + String(counter));
    } 
    aLastState = aState; // Updates the previous state of the outputA with the current state
    
    return counter;
   
  }
void encoderInit(int A, int B){
    pinMode (A, INPUT);
    pinMode (B, INPUT);
    aLastState = digitalRead(A);
}
