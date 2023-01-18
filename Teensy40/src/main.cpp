#include <Arduino.h>
#include "Waveforms.h"

#define oneHzSample 1000000/maxSamplesNum  // sample for the 1Hz signal expressed in microseconds

int i = 0;

void setup() {
  analogWriteResolution(16);
  analogReadResolution(16);
}

void loop() {
    analogWrite(A0, waveformsTable[0][i]);

    i++;
    if(i == maxSamplesNum)
      i = 0;

    delayMicroseconds(oneHzSample);
}