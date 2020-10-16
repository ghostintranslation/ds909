#ifndef BassDrum_h
#define BassDrum_h

#include <Audio.h>

/*
// GUItool: begin automatically generated code
AudioSynthSimpleDrum     bassDrum;          //xy=228,217
AudioSynthSimpleDrum     click;          //xy=229,165
AudioMixer4              mixer1;         //xy=422,193
AudioOutputI2S           i2s1;           //xy=598,199
AudioConnection          patchCord1(bassDrum, 0, mixer1, 1);
AudioConnection          patchCord2(click, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 1);
// GUItool: end automatically generated code
*/

/*
 * BassDrum
 */
class BassDrum{
  private:
    byte clickFrequency;
    byte clickExtraFrequency;
    AudioSynthSimpleDrum     *bassDrum;
    AudioSynthSimpleDrum     *click;
    AudioConnection* patchCords[18];
    AudioMixer4 *output;


  public:
    BassDrum();
    
    AudioMixer4 * getOutput();
    void noteOn();
    void setPitch(byte pitch);
    void setTone(byte tone);
    void setDecay(byte decay);
    byte getPitch();
    byte getTone();
    byte getDecay();
};

/**
 * Constructor
 */
inline BassDrum::BassDrum(){
  this->click = new AudioSynthSimpleDrum();
  this->click->secondMix(0.2);
  this->bassDrum = new AudioSynthSimpleDrum();
  this->bassDrum->pitchMod(0.5);

  this->output = new AudioMixer4();
  this->output->gain(0, 0.8);
  this->output->gain(1, 1);

  this->patchCords[0] = new AudioConnection(*this->click, 0, *this->output, 0);
  this->patchCords[1] = new AudioConnection(*this->bassDrum, 0, *this->output, 1);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * BassDrum::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void BassDrum::noteOn() {
  this->click->noteOn();
  this->bassDrum->noteOn();
}

/**
 * Set the pitch
 * 
 * @param pitch The pitch
 */
inline void BassDrum::setPitch(byte pitch){
  byte mappedFrequency = map(pitch, 0, 255, 30, 70);
  this->clickFrequency = mappedFrequency;
  
  this->bassDrum->frequency(mappedFrequency);
  this->click->frequency(this->clickFrequency + this->clickExtraFrequency);
}

/**
 * Set the decay
 * 
 * @param decay The decay
 */
inline void BassDrum::setDecay(byte decay){
  unsigned int mappedDecay = map(decay, 0, 255, 400, 800);
  byte mappedClickDecay = map(decay, 0, 255, 150, 600);
  
  this->bassDrum->length(mappedDecay);
  this->click->length(mappedClickDecay);
}

/**
 * Set the tone
 * 
 * @param tone The tone
 */
inline void BassDrum::setTone(byte tone){
  float mappedTone = (float)map((float)tone, (float)0, (float)255, (float)0.7, (float)1);
  this->clickExtraFrequency = map(tone, 0, 255, 0, 15);
  
  this->click->pitchMod(mappedTone);
  this->click->frequency(this->clickFrequency + this->clickExtraFrequency);
}
#endif
