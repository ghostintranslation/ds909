/*
 __    _  _____   ___      ___ _  _     __    _ ______ _    
/__|_|/ \(_  |     | |\|    | |_)|_||\|(_ |  |_| |  | / \|\|
\_|| |\_/__) |    _|_| |    | | \| || |__)|__| | | _|_\_/| |

DS909
v1.1.0

Support my work:
https://www.paypal.com/paypalme/ghostintranslation

https://www.ghostintranslation.com/
https://ghostintranslation.bandcamp.com/
https://www.instagram.com/ghostintranslation/
https://www.youtube.com/channel/UCcyUTGTM-hGLIz4194Inxyw
https://github.com/ghostintranslation
*/

#include <Audio.h>
#include "DS909.h"

// Instanciation of DS909
DS909 * ds909 = DS909::getInstance();

// Connecting DS909 to general audio output
AudioOutputI2S  i2s2;
AudioOutputUSB usb;
AudioConnection patchCord1(*ds909->getOutput(), 0, i2s2, 0);
AudioConnection patchCord2(*ds909->getOutput(), 0, i2s2, 1);
AudioConnection patchCord3(*ds909->getOutput(), 0, usb, 0);
AudioConnection patchCord4(*ds909->getOutput(), 0, usb, 1);
AudioControlSGTL5000 audioBoard;
 
void setup() {
  Serial.begin(115200);
  
  while (!Serial && millis() < 2500); // wait for serial monitor
  
  ds909->init();
  
  // Audio connections require memory to work.
  AudioMemory(40);

  audioBoard.enable();
  audioBoard.volume(0.5);
  
  // Starting sequence
  Serial.println("Ready!");
}

void loop() {
  ds909->update();
}
