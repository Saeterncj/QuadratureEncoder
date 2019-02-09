#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

#define MAX_NUM_ENCODERS 4

class Encoders{
  public:  
    Encoders(byte pinA, byte pinB);
    static void interruptEncoder1(){
      if(Encoders::_instances[0] != NULL)
      Encoders::_instances[0]->encoderCount();
    }
    static void interruptEncoder2(){
      if(Encoders::_instances[1] != NULL)
      Encoders::_instances[1]->encoderCount();
    }
    static void interruptEncoder3(){
      if(Encoders::_instances[2] != NULL)
      Encoders::_instances[2]->encoderCount();
    }
    static void interruptEncoder4(){
      if(Encoders::_instances[3] != NULL)
      Encoders::_instances[3]->encoderCount();
    }
    
    void encoderCount();
    long getEncoderCount();
    void setEncoderCount(long);
    long getEncoderErrorCount();
    static Encoders *_instances[MAX_NUM_ENCODERS];
    
  private:
    static uint8_t _whichEncoder;
    uint8_t _encoderPINA;
    uint8_t _encoderPINB;
    volatile long _encoderCount = 0;
    volatile int _lastEncoded = 0;
    volatile long _encoderErrors = 0;
};

#endif
