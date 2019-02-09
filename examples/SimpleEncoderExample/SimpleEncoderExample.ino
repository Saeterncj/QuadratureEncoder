
#include <QuadratureEncoder.h>

// Use any 2 pins for interrupt, this utilizes EnableInterrupt Library. 
// Even analog pins can be used.
Encoders leftEncoder(2,3);

Encoders rightEncoder(5,14);
void setup() {
  Serial.begin(115200);
  
}
unsigned long lastMilli = 0;

void loop() {
  // put your main code here, to run repeatedly:
//  static int pwm = 3;
  if(millis()-lastMilli > 50){
    long currentLeftEncoderCount = leftEncoder.getEncoderCount();
    long currentRightEncoderCount = rightEncoder.getEncoderCount();

    double actualLeftPosition = ((double)currentLeftEncoderCount / 2527.08) * 360; 
    double actualRightPosition = ((double)currentRightEncoderCount / 2527.08) * 360; 
    
    lastMilli = millis();
    Serial.print(currentLeftEncoderCount);
    Serial.print(" , ");
    Serial.print(currentRightEncoderCount);
    Serial.print(" , ");
    Serial.print((int)actualLeftPosition%360);
    Serial.print(" , ");
    Serial.println((int)actualRightPosition%360);
  }
   
}
