#include <EnableInterrupt.h>
#include "QuadratureEncoder.h"


// initialize all instance of encoder to null.

Encoders *Encoders::_instances[MAX_NUM_ENCODERS] = {NULL, NULL,NULL, NULL};
uint8_t Encoders::_whichEncoder = 0;
Encoders::Encoders(byte pinA, byte pinB){
   _encoderPINA = pinA;
   _encoderPINB = pinB;
   pinMode(_encoderPINA, INPUT_PULLUP);  
   pinMode(_encoderPINB, INPUT_PULLUP);
   _whichEncoder++;
   switch(_whichEncoder){
    case 1:
        enableInterrupt(_encoderPINB, interruptEncoder1, CHANGE);
        enableInterrupt(_encoderPINA,  interruptEncoder1, CHANGE);  
        _instances[0] = this;
        break;
     case 2:
        enableInterrupt(_encoderPINB, interruptEncoder2, CHANGE);
        enableInterrupt(_encoderPINA,  interruptEncoder2, CHANGE);  
        _instances[1] = this;
        break;
     case 3:
        enableInterrupt(_encoderPINB, interruptEncoder3, CHANGE);
        enableInterrupt(_encoderPINA,  interruptEncoder3, CHANGE); 
        _instances[2] = this; 
        break;
     case 4:
        enableInterrupt(_encoderPINB, interruptEncoder4, CHANGE);
        enableInterrupt(_encoderPINA,  interruptEncoder4, CHANGE);  
        _instances[3] = this;
        break;
   }
}




void Encoders::encoderCount(){
  int EncoderPhaseA = digitalRead(this->_encoderPINA);  // MSB
  int EncoderPhaseB = digitalRead(this->_encoderPINB);  // LSB

  int currentEncoded = (EncoderPhaseA << 1) | EncoderPhaseB;
  int sum = (this->_lastEncoded << 2) | currentEncoded;
  switch(sum){
    case 0b0001:
    case 0b0111:
    case 0b1110:
    case 0b1000:
      this->_encoderCount--;
      break;
    case 0b0010:
    case 0b1011:
    case 0b1101:
    case 0b0100:
      this->_encoderCount++;
      break;
    default:
      this->_encoderErrors++;
      break;
  }
  this->_lastEncoded = currentEncoded;
}

long Encoders::getEncoderCount(){
  return _encoderCount;
}
void Encoders::setEncoderCount(long setEncoderVal){
  this->_encoderCount = setEncoderVal;
}

long Encoders::getEncoderErrorCount(){
  return _encoderErrors;
}
