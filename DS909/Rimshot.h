#ifndef Rimshot_h
#define Rimshot_h

#include <Audio.h>
#include "AudioPlayPitchedMemory.h"


/*
// GUItool: begin automatically generated code
AudioSynthNoiseWhite     white;          //xy=103,127
AudioEffectEnvelope      clickEnvelope;  //xy=264,128
AudioSynthSimpleDrum     rim;      //xy=278,85
AudioMixer4              mixer;     //xy=432,119
AudioFilterStateVariable filter1;        //xy=560,121
AudioOutputI2S           i2s1;           //xy=718,93
AudioOutputUSB           usb1;           //xy=719,144
AudioOutputI2S           i2s2; //xy=989,453
AudioOutputUSB           usb2; //xy=990,495
AudioOutputI2S           is24; //xy=1002,491
AudioOutputUSB           usb4; //xy=1003,533
AudioOutputI2S           is23;           //xy=1063,522
AudioOutputUSB           usb3;           //xy=1064,564
AudioOutputI2S           is25;           //xy=1076,560
AudioOutputUSB           usb5;           //xy=1077,602
AudioConnection          patchCord1(white, clickEnvelope);
AudioConnection          patchCord2(clickEnvelope, 0, mixer, 1);
AudioConnection          patchCord3(rim, 0, mixer, 0);
AudioConnection          patchCord4(mixer, 0, filter1, 0);
AudioConnection          patchCord5(filter1, 2, usb1, 0);
AudioConnection          patchCord6(filter1, 2, usb1, 1);
AudioConnection          patchCord7(filter1, 2, i2s1, 1);
AudioConnection          patchCord8(filter1, 2, i2s1, 0);
// GUItool: end automatically generated code

*/

/*
 * Rimshot
 */
class Rimshot{
  private:
    AudioSynthNoiseWhite     *white;
    AudioSynthSimpleDrum     *rim;
    AudioEffectEnvelope      *clickEnvelope;
    AudioMixer4              *mixer;
    AudioFilterStateVariable *filter;
    AudioConnection* patchCords[22];
    AudioMixer4 *output;
    

  public:
    Rimshot();
    
    AudioMixer4 * getOutput();
    void noteOn(byte velocity);
    void setPitch(byte pitch);
    void setTone(byte tone);
};

/**
 * Constructor
 */
inline Rimshot::Rimshot(){
  this->white = new AudioSynthNoiseWhite();
  this->white->amplitude(1);

  this->rim = new AudioSynthSimpleDrum();
  this->rim->pitchMod(0.5);
  this->rim->frequency(180);
  this->rim->length(30);
  this->rim->secondMix(0.2);
  
  this->clickEnvelope = new AudioEffectEnvelope();
  this->clickEnvelope->attack(1);
  this->clickEnvelope->sustain(0);
  this->clickEnvelope->release(1);
  this->clickEnvelope->decay(5);

  this->mixer = new AudioMixer4();
  this->mixer->gain(0, 4);
  this->mixer->gain(1, 2);
  
  this->filter = new AudioFilterStateVariable();
  this->filter->frequency(800);
  this->filter->resonance(2);
  this->filter->octaveControl(3);
  
  this->output = new AudioMixer4();
  this->output->gain(0, 1.7);

  this->patchCords[0] = new AudioConnection(*this->white, 0, *this->clickEnvelope, 0);
  this->patchCords[2] = new AudioConnection(*this->rim, 0, *this->mixer, 0);
  this->patchCords[3] = new AudioConnection(*this->clickEnvelope, 0, *this->mixer, 1);
  this->patchCords[4] = new AudioConnection(*this->mixer, 0, *this->filter, 0);
  this->patchCords[1] = new AudioConnection(*this->filter, 2, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Rimshot::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Rimshot::noteOn(byte velocity) {
  this->output->gain(0, map((float)velocity, 0, 255, 0, 1));
  this->rim->noteOn();
  this->clickEnvelope->noteOn();
}

/**
 * Set the pitch
 */
inline void Rimshot::setPitch(byte pitch) {
  unsigned int mappedFrequency = map(pitch, 0, 255, 300, 500);
  this->rim->frequency(mappedFrequency);
}

/**
 * Set the tone
 */
inline void Rimshot::setTone(byte tone) {
  float mappedTone = map((float)tone, 0, 255, 0, 0.2);
  this->mixer->gain(1, mappedTone);
}
#endif
