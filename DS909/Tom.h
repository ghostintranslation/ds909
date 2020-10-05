#ifndef Tom_h
#define Tom_h

#include <Audio.h>

/*
 * Tom
 */
class Tom{
  private:
    AudioSynthSimpleDrum *tom;
    AudioConnection* patchCords[22];
    AudioMixer4 *output;

  public:
    Tom();
    
    void setPitch(byte pitch);
    void setDecay(byte decay);
    AudioMixer4 * getOutput();
    void noteOn();
};

/**
 * Constructor
 */
inline Tom::Tom(){
  this->tom = new AudioSynthSimpleDrum();
  this->tom->secondMix(0.2);
  this->tom->pitchMod(0.6);

  this->output = new AudioMixer4();
  this->output->gain(0, 0.8);

  this->patchCords[1] = new AudioConnection(*this->tom, 0, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Tom::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Tom::noteOn() {
  this->tom->noteOn();
}


/**
 * Set the pitch
 * @param[byte] pitch The pitch
 */
inline void Tom::setPitch(byte pitch){
  unsigned int mappedFrequency = map(pitch, 0, 255, 80, 400);
  this->tom->frequency(mappedFrequency);
}

/**
 * Set the decay
 * @param[byte] decay The decay
 */
inline void Tom::setDecay(byte decay){
  unsigned int mappedDecay = map(decay, 0, 255, 300, 1500);
  this->tom->length(mappedDecay);
}

#endif
