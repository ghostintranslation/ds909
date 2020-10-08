#ifndef Snare_h
#define Snare_h

#include <Audio.h>
#include "AudioPlayPitchedMemory.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

/*
// GUItool: begin automatically generated code
AudioSynthNoiseWhite     white;         //xy=61,129
AudioFilterStateVariable filter;         //xy=184,140
AudioEffectEnvelope      snareEnvelope;  //xy=334,143
AudioSynthSimpleDrum     snareDrum;      //xy=348,100
AudioMixer4              snareMixer;     //xy=502,134
AudioOutputI2S           i2s1;           //xy=680,102
AudioOutputUSB           usb1;           //xy=695,169
AudioOutputI2S           i2s2; //xy=989,453
AudioOutputUSB           usb2; //xy=990,495
AudioConnection          patchCord1(white, 0, filter, 0);
AudioConnection          patchCord2(filter, 1, snareEnvelope, 0);
AudioConnection          patchCord3(snareEnvelope, 0, snareMixer, 1);
AudioConnection          patchCord4(snareDrum, 0, snareMixer, 0);
AudioConnection          patchCord5(snareMixer, 0, i2s1, 0);
AudioConnection          patchCord6(snareMixer, 0, i2s1, 1);
AudioConnection          patchCord7(snareMixer, 0, usb1, 0);
AudioConnection          patchCord8(snareMixer, 0, usb1, 1);
// GUItool: end automatically generated code
*/

/*
 * Snare
 */
class Snare{
  private:
    AudioSynthNoiseWhite     *white;
    AudioSynthSimpleDrum     *snareDrum;
    AudioSynthSimpleDrum     *snareDrum2;
    AudioEffectEnvelope      *snareEnvelope;
    AudioMixer4              *snareMixer;
    AudioFilterStateVariable *filter;
    AudioConnection* patchCords[22];
    AudioMixer4 *output;
    

  public:
    Snare();
    
    AudioMixer4 * getOutput();
    void noteOn(byte velocity);
    void setPitch(byte pitch);
    void setTone(byte tone);
    void setDecay(byte decay);
};


/**
 * Constructor
 */
inline Snare::Snare(){
  this->white = new AudioSynthNoiseWhite();
  this->white->amplitude(1);

  this->snareDrum = new AudioSynthSimpleDrum();
  this->snareDrum->pitchMod(0.5);
  this->snareDrum->frequency(180);
  this->snareDrum->length(150);
  this->snareDrum->secondMix(0.7);
  
  this->snareDrum2 = new AudioSynthSimpleDrum();
  this->snareDrum2->pitchMod(0.9);
  this->snareDrum2->frequency(50);
  this->snareDrum2->length(45);
  this->snareDrum2->secondMix(0);
  
  this->snareEnvelope = new AudioEffectEnvelope();
  this->snareEnvelope->attack(4);
  this->snareEnvelope->sustain(0);
  this->snareEnvelope->release(1);
  this->snareEnvelope->decay(300);

  this->snareMixer = new AudioMixer4();
  this->snareMixer->gain(0, 1);
  this->snareMixer->gain(1, 0.4);
  this->snareMixer->gain(2, 2);
 
  this->filter = new AudioFilterStateVariable();
  this->filter->frequency(2000);
  this->filter->resonance(2);
  this->filter->octaveControl(3);
  
  this->output = new AudioMixer4();
  this->output->gain(0, 0.5);

  this->patchCords[0] = new AudioConnection(*this->white, 0, *this->filter, 0);
  this->patchCords[1] = new AudioConnection(*this->filter, 1, *this->snareEnvelope, 0);
  this->patchCords[2] = new AudioConnection(*this->snareDrum, 0, *this->snareMixer, 0);
  this->patchCords[3] = new AudioConnection(*this->snareEnvelope, 0, *this->snareMixer, 1);
  this->patchCords[2] = new AudioConnection(*this->snareDrum2, 0, *this->snareMixer, 2);
  this->patchCords[4] = new AudioConnection(*this->snareMixer, 0, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Snare::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Snare::noteOn(byte velocity) {
  this->output->gain(0, map((float)velocity, 0, 255, 0, 1));
  this->snareDrum->noteOn();
  this->snareDrum2->noteOn();
  this->snareEnvelope->noteOn();
}


/**
 * Set the pitch
 * @param[byte] pitch The pitch
 */
inline void Snare::setPitch(byte pitch){
  unsigned int mappedFrequency = map(pitch, 0, 255, 100, 250);
  unsigned int mappedFrequency2 = map(pitch, 0, 255, 70, 100);
  this->snareDrum->frequency(mappedFrequency);
  this->snareDrum2->frequency(mappedFrequency2);
}

/**
 * Set the decay
 * @param[byte] decay The decay
 */
inline void Snare::setDecay(byte decay){
  unsigned int mappedSnareDecay = map(decay, 0, 255, 50, 120);
  unsigned int mappedSnareNoiseDecay = map(decay, 0, 255, 200, 500);

  this->snareDrum->length(mappedSnareDecay);
  this->snareEnvelope->decay(mappedSnareNoiseDecay);
}

/**
 * Set the tone
 * @param tone The tone
 */
inline void Snare::setTone(byte tone){
  unsigned int mappedFilter = map(tone, 0, 255, 2000, 2500);
  this->filter->frequency(mappedFilter);
}


#endif
