#include <Servo.h>

Servo motor1;
Servo motor2;

void setup() {
motor1.attach(5);
motor2.attach(6);

}

void loop() {
  int sensorValue = analogRead(A0);
  if(sensorValue > 350){
   motor1.write(0);
    motor2.write(180); 
  }else{
   motor1.write(90);
    motor2.write(90); 
  }

}
