#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 4
#define PIN_BUTTON 7
#define NUM_PIXELS 120

Adafruit_NeoPixel Neopixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

//state of saber blade, 0 = off, 10 = igniting, 20 = idle on, 30 = shutting off 
int saberState = 0;
bool readyForStateChange = true;

int buttonState = 0;
int lastButtonState = 0;
bool isStartupDone = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Neopixel.begin();
  Neopixel.setBrightness(50);
}

void Ignite(){
  int ascending = 0;
  int descending = 120;
  for (int pixel = 0; pixel < NUM_PIXELS / 2; pixel++) { // for each pixel
      Neopixel.setPixelColor(ascending, Neopixel.Color(75, 75, 100)); // it only takes effect if pixels.show() is called
      Neopixel.setPixelColor(descending, Neopixel.Color(75, 75, 100)); // it only takes effect if pixels.show() is called
      Neopixel.show();   // send the updated pixel colors to the NeoPixel hardware.
      ascending++;
      descending--;
      delay(33); // pause between each pixel
    }
    saberState++;
    readyForStateChange = true;
}

void Shutoff(){
  int ascending = 60;
  int descending = 59;
  for (int pixel = NUM_PIXELS; pixel > 0; pixel--) { // for each pixel
    Neopixel.setPixelColor(ascending, Neopixel.Color(0, 0, 0)); // it only takes effect if pixels.show() is called
    Neopixel.setPixelColor(descending, Neopixel.Color(0, 0, 0)); // it only takes effect if pixels.show() is called
    Neopixel.show();   // send the updated pixel colors to the NeoPixel hardware.

    ascending++;
    descending--;
    delay(10); // pause between each pixel
  }
  saberState = 0;
  readyForStateChange = true;
}

void loop() {
  if(!isStartupDone){
    buttonState = digitalRead(PIN_BUTTON);
    delay(1000);
    isStartupDone = true;
  }
  buttonState = digitalRead(PIN_BUTTON);

  if(buttonState != lastButtonState){
    if(buttonState == LOW){
        
          saberState++;
      delay(100);
    }
    lastButtonState = buttonState;
  }
  
  if(saberState == 0){
    Neopixel.clear();
    Neopixel.show();
    readyForStateChange = true;
  }

  //activate
  // if(saberState == 10){
  //   Ignite();
  // }

  switch (saberState)
  {
  case 1:
    Ignite();
    break;
  case 3:
    Shutoff();
    break;
  default:
    break;
  }
  
  //idle/pulse

  // int count = 0;
  // while(count < 500){
  //   int pixelId = random(1, NUM_PIXELS);
  //   long brightPercent = random(0.6, 1);
  //   Neopixel.setPixelColor(pixelId, Neopixel.Color(100 / brightPercent,100 / brightPercent, 100 / brightPercent));
  //   Neopixel.show();
  //   delay(20);
  //   count++;
  // }

  // delay(4000);

  //deactivate
  // if(saberState == 30){
  //   Shutoff();
  // }
}



