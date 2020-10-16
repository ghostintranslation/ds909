#ifndef Clap_h
#define Clap_h

#include <Audio.h>

/*
// GUItool: begin automatically generated code
AudioSynthNoisePink      pink;           //xy=55,203
AudioFilterStateVariable filter;         //xy=72,92
AudioSynthSimpleDrum     clapDrum;      //xy=214,308
AudioEffectEnvelope      clapEnvelope;  //xy=229,349
AudioEffectEnvelope      clapEnvelope3;      //xy=232,118
AudioEffectEnvelope      clapEnvelope;   //xy=233,30
AudioEffectEnvelope      clapEnvelope5;      //xy=233,215
AudioEffectEnvelope      clapEnvelope2;      //xy=234,72
AudioEffectEnvelope      clapEnvelope4;      //xy=235,154
AudioFilterStateVariable clapFilter;        //xy=413,241
AudioMixer4              clapMixer;         //xy=417,329
AudioMixer4              clapMixer;         //xy=456,58
AudioMixer4              clapMixer2;         //xy=474,144
AudioMixer4              mixer;          //xy=570,246
AudioOutputI2S           i2s1;           //xy=729,219
AudioOutputUSB           usb1;           //xy=730,261
AudioConnection          patchCord1(pink, 0, filter, 0);
AudioConnection          patchCord2(pink, clapEnvelope5);
AudioConnection          patchCord3(filter, 1, snareEnvelope, 0);
AudioConnection          patchCord4(filter, 1, clapEnvelope2, 0);
AudioConnection          patchCord5(filter, 1, clapEnvelope, 0);
AudioConnection          patchCord6(filter, 1, clapEnvelope3, 0);
AudioConnection          patchCord7(filter, 1, clapEnvelope4, 0);
AudioConnection          patchCord8(snareDrum, 0, snareMixer, 0);
AudioConnection          patchCord9(snareEnvelope, 0, snareMixer, 1);
AudioConnection          patchCord10(clapEnvelope3, 0, clapMixer, 2);
AudioConnection          patchCord11(clapEnvelope, 0, clapMixer, 0);
AudioConnection          patchCord12(clapEnvelope5, 0, clapFilter, 0);
AudioConnection          patchCord13(clapEnvelope2, 0, clapMixer, 1);
AudioConnection          patchCord14(clapEnvelope4, 0, clapMixer, 3);
AudioConnection          patchCord15(clapFilter, 1, clapMixer2, 1);
AudioConnection          patchCord16(snareMixer, 0, mixer, 1);
AudioConnection          patchCord17(clapMixer, 0, clapMixer2, 0);
AudioConnection          patchCord18(clapMixer2, 0, filter, 1);
AudioConnection          patchCord19(clapMixer2, 0, clapFilter, 1);
AudioConnection          patchCord20(clapMixer2, 0, mixer, 0);
AudioConnection          patchCord21(mixer, 0, i2s1, 0);
AudioConnection          patchCord22(mixer, 0, i2s1, 1);
AudioConnection          patchCord23(mixer, 0, usb1, 0);
AudioConnection          patchCord24(mixer, 0, usb1, 1);
// GUItool: end automatically generated code
*/

/*
 * Clap
 */
class Clap{
  private:
    byte tone;
    byte decay;
    AudioSynthNoiseWhite     *white;
    AudioEffectMultiply      *clapMultiply;
    AudioEffectEnvelope      *clapEnvelope;
    AudioEffectEnvelope      *clapEnvelope2;
    AudioEffectEnvelope      *clapEnvelope3;
    AudioEffectEnvelope      *clapEnvelope4;
    AudioEffectEnvelope      *clapEnvelope5;
    AudioFilterStateVariable *clapFilter;
    AudioMixer4              *clapMixer;
    AudioMixer4              *clapMixer2;
    AudioMixer4              *mixer;
    AudioFilterStateVariable *filter;
    AudioConnection* patchCords[22];
    AudioMixer4 *output;


  public:
    Clap();
    
    AudioMixer4 * getOutput();
    void noteOn();
    void setTone(byte tone);
    void setDecay(byte decay);
};

/**
 * Constructor
 */
inline Clap::Clap(){
  this->white = new AudioSynthNoiseWhite();
  this->white->amplitude(1);

  // Clap

  this->clapEnvelope = new AudioEffectEnvelope();
  this->clapEnvelope->attack(0.0 );
  this->clapEnvelope->sustain(0);
  this->clapEnvelope->release(1);
  this->clapEnvelope->decay(10);

  this->clapEnvelope2 = new AudioEffectEnvelope();
  this->clapEnvelope2->delay(12);
  this->clapEnvelope2->attack(0.0 );
  this->clapEnvelope2->sustain(0);
  this->clapEnvelope2->release(1);
  this->clapEnvelope2->decay(10);

  this->clapEnvelope3 = new AudioEffectEnvelope();
  this->clapEnvelope3->delay(24);
  this->clapEnvelope3->attack(0.0 );
  this->clapEnvelope3->sustain(0);
  this->clapEnvelope3->release(1);
  this->clapEnvelope3->decay(10);

  this->clapEnvelope4 = new AudioEffectEnvelope();
  this->clapEnvelope4->delay(36);
  this->clapEnvelope4->attack(0.0 );
  this->clapEnvelope4->sustain(0);
  this->clapEnvelope4->release(1);
  this->clapEnvelope4->decay(40);
  
  this->clapEnvelope5 = new AudioEffectEnvelope();
  this->clapEnvelope5->delay(44);
  this->clapEnvelope5->attack(0.0);
  this->clapEnvelope5->sustain(0);
  this->clapEnvelope5->release(1);
  this->clapEnvelope5->decay(150);

  this->clapFilter = new AudioFilterStateVariable();
  this->clapFilter->frequency(750);
  this->clapFilter->resonance(3);

  this->clapMixer = new AudioMixer4();
  this->clapMixer->gain(0, .8);
  this->clapMixer->gain(1, 1);
  this->clapMixer->gain(2, .7);
  this->clapMixer->gain(3, .4);
  
  this->clapMixer2 = new AudioMixer4();
  this->clapMixer2->gain(0, 1);
  this->clapMixer2->gain(1, .02);

  this->mixer = new AudioMixer4();
  this->mixer->gain(0, 1);
  this->mixer->gain(1, 0);

  
  this->filter = new AudioFilterStateVariable();
  this->filter->frequency(2000);
  this->filter->resonance(5);
  this->filter->octaveControl(3);
  
  this->output = new AudioMixer4();
  this->output->gain(0, 0.4);

  this->patchCords[0] = new AudioConnection(*this->white, 0, *this->filter, 0);
  this->patchCords[1] = new AudioConnection(*this->filter, 1, *this->clapEnvelope, 0);
  this->patchCords[2] = new AudioConnection(*this->filter, 1, *this->clapEnvelope2, 0);
  this->patchCords[3] = new AudioConnection(*this->filter, 1, *this->clapEnvelope3, 0);
  this->patchCords[4] = new AudioConnection(*this->filter, 1, *this->clapEnvelope4, 0);
  this->patchCords[5] = new AudioConnection(*this->white, 0, *this->clapEnvelope5, 0);
  this->patchCords[6] = new AudioConnection(*this->clapEnvelope, 0, *this->clapMixer, 0);
  this->patchCords[7] = new AudioConnection(*this->clapEnvelope2, 0, *this->clapMixer, 1);
  this->patchCords[8] = new AudioConnection(*this->clapEnvelope3, 0, *this->clapMixer, 2);
  this->patchCords[9] = new AudioConnection(*this->clapEnvelope4, 0, *this->clapMixer, 3);
  this->patchCords[10] = new AudioConnection(*this->clapEnvelope5, 0, *this->clapFilter, 0);
  this->patchCords[12] = new AudioConnection(*this->clapFilter, 1, *this->clapMixer2, 1);
 
  this->patchCords[18] = new AudioConnection(*this->clapMixer, 0, *this->clapMixer2, 0);
  this->patchCords[19] = new AudioConnection(*this->clapMixer2, 0, *this->mixer, 0);
  this->patchCords[21] = new AudioConnection(*this->mixer, 0, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Clap::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Clap::noteOn() {
  this->clapEnvelope->noteOn();
  this->clapEnvelope2->noteOn();
  this->clapEnvelope3->noteOn();
  this->clapEnvelope4->noteOn();
  this->clapEnvelope5->noteOn();
}

/**
 * Set the decay
 * 
 * @param decay The decay
 */
inline void Clap::setDecay(byte decay){
  this->decay = decay;
  float mappedClapDecay = (float)map((float)decay, 0, 255, 30, 400);

  this->clapEnvelope5->decay(mappedClapDecay);
}

/**
 * Set the tone
 * 
 * @param tone The tone
 */
inline void Clap::setTone(byte tone){
  this->tone = tone;

  unsigned int mappedFilter = map(tone, 0, 255, 300, 2000);
  this->filter->frequency(mappedFilter);
}
#endif
