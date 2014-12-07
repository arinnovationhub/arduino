#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial softSerial(7,  8); // RX, TX
Servo motor1;
Servo motor2;

void setup(){
  softSerial.begin(9600);
  motor1.attach(5);
  motor2.attach(6);
  
  motor1.write(90);
  motor2.write(90);
 
  pinMode(13, OUTPUT);
  blinkReadyLight();
}

void loop(){
    while (softSerial.available()>0) {
      int motor1speed = softSerial.parseInt();
      int motor2speed = softSerial.parseInt();
      if(softSerial.read() =='\n'){
        motor1.write(motor1speed);
        motor2.write(motor2speed);
      }
 
    }
  delay(50);  
}

void blinkReadyLight(){
  for(int i=0; i<3; i++){
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13,LOW);
    delay(200); 
  }
}

