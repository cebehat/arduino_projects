#include <Arduino.h>
#include <Servo.h>

#define BUTTON_PIN 3

int buttonState = HIGH;
int previousButtonState = HIGH;
Servo myServo1;
Servo myServo2;
int pos = 90;
//0 open; 1 closed;
int helmetState = 0;
int helmetStateChanged = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myServo1.attach(9);
  myServo2.attach(10);
}

void changeHelmetState(){
  if(helmetStateChanged == true) return;
  switch(helmetState){
    case 0:
    helmetState = 1;
    helmetStateChanged = true;
    break;
    case 1:
    helmetState = 0;
    break;
    default:
    break;
  }
  helmetStateChanged = true;
  delay(20);
}

void loop() {
  // Serial.println(digitalRead(BUTTON_PIN));
  int currentBtnState = digitalRead(BUTTON_PIN);

  if(currentBtnState == LOW && currentBtnState != previousButtonState){
    changeHelmetState();
    Serial.println("button pressed");    
  }
  previousButtonState = currentBtnState;
  delay(100);

  // for(pos = 0; pos <= 180; pos++){
  //   myServo.write(pos);
  //   delay(15);
  // }
  // for(pos = 180; pos >= 0; pos--){
  //   myServo.write(pos);
  //   delay(15);
  // }
  
  if(helmetStateChanged){
    switch(helmetState){
      case 1:
      pos = 135;
      myServo1.write(135);
      myServo2.write(45);
      changeHelmetState();
      delay(200);
      myServo1.write(90);
      myServo2.write(90);
      break;
      case 0:
      pos = 45;
      myServo1.write(45);
      myServo2.write(135);
      changeHelmetState();
      delay(200);
      myServo1.write(90);
      myServo2.write(90);
      break;
      default:
      myServo1.write(90);
      myServo2.write(90);
      break;
    }
    helmetStateChanged = false;
  }
}