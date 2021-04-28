#ifndef DS909_h
#define DS909_h

#include "Motherboard9.h"
#include "BassDrum.h"
#include "Snare.h"
#include "Clap.h"
#include "Rimshot.h"
#include "Tom.h"
#include "HiHat.h"
#include "Cymbal.h"

/*
 * DS909
 */
class DS909{
  private:
    static DS909 *instance;
    DS909();
   
    // Motherboard
    Motherboard9 *device;
    
    // Bass Drum
    BassDrum *bassDrum;
    // Snare
    Snare *snare;
    // Clap
    Clap *clap;
    // Rimshot
    Rimshot *rimshot;
    // Hi Tom
    Tom *hiTom;
    // Mid Tom
    Tom *midTom;
    // Low Tom
    Tom *lowTom;
    // Hihat
    Hihat *hihat;
    // Cymbal
    Cymbal *cymbal;
    
    // Output
    AudioMixer4 *mixer1;
    AudioMixer4 *mixer2;
    AudioMixer4 *mixer3;
    AudioMixer4 *output;
    AudioConnection* patchCords[3];
    
  public:
    static DS909 *getInstance();
    void init();
    void update();
    AudioMixer4 * getOutput();

    // Callbacks
    static void onBDChange(byte inputIndex, float value, int diffToPrevious);
    static void onSNChange(byte inputIndex, float value, int diffToPrevious);
    static void onCPChange(byte inputIndex, float value, int diffToPrevious);
    static void onRMChange(byte inputIndex, float value, int diffToPrevious);
    static void onHTChange(byte inputIndex, float value, int diffToPrevious);
    static void onMTChange(byte inputIndex, float value, int diffToPrevious);
    static void onLTChange(byte inputIndex, float value, int diffToPrevious);
    static void onHHChange(byte inputIndex, float value, int diffToPrevious);
    static void onCYChange(byte inputIndex, float value, int diffToPrevious);
    // Midi callbacks
    static void onMidiNoteOn(byte channel, byte note, byte velocity);
    static void onMidiBDChange(byte channel, byte note, byte velocity);
    static void onMidiSNChange(byte channel, byte note, byte velocity);
    static void onMidiCPChange(byte channel, byte note, byte velocity);
    static void onMidiRMChange(byte channel, byte note, byte velocity);
    static void onMidiHTChange(byte channel, byte note, byte velocity);
    static void onMidiMTChange(byte channel, byte note, byte velocity);
    static void onMidiLTChange(byte channel, byte note, byte velocity);
    static void onMidiHHChange(byte channel, byte note, byte velocity);
    static void onMidiCYChange(byte channel, byte note, byte velocity);
    
};

// Singleton pre init
DS909 * DS909::instance = nullptr;

/**
 * Constructor
 */
inline DS909::DS909(){
  this->bassDrum = new BassDrum();
  this->snare = new Snare();
  this->clap = new Clap();
  this->hiTom = new Tom();
  this->midTom = new Tom();
  this->lowTom = new Tom();
  this->rimshot = new Rimshot();
  this->hihat = new Hihat();
  this->cymbal = new Cymbal();
  
  this->device = Motherboard9::getInstance();
  
  this->mixer1 = new AudioMixer4();
  this->mixer1->gain(0, 1 );
  this->mixer1->gain(1, 1 );
  this->mixer1->gain(2, 1 );
  this->mixer1->gain(3, 1 );

  this->mixer2 = new AudioMixer4();
  this->mixer2->gain(0, 1 );
  this->mixer2->gain(1, 1 );
  this->mixer2->gain(2, 1 );
  this->mixer2->gain(3, 1 );
  
  this->mixer3 = new AudioMixer4();
  this->mixer3->gain(0, 1 );
  this->mixer3->gain(1, 1 );
  
  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
  this->output->gain(1, 1 );
  this->output->gain(2, 1 );

  this->patchCords[0] = new AudioConnection(*this->bassDrum->getOutput(), 0, *this->mixer1, 0);
  this->patchCords[0] = new AudioConnection(*this->snare->getOutput(), 0, *this->mixer1, 1);
  this->patchCords[0] = new AudioConnection(*this->clap->getOutput(), 0, *this->mixer1, 2);
  this->patchCords[0] = new AudioConnection(*this->hiTom->getOutput(), 0, *this->mixer1, 3);
  this->patchCords[0] = new AudioConnection(*this->midTom->getOutput(), 0, *this->mixer2, 0);
  this->patchCords[0] = new AudioConnection(*this->lowTom->getOutput(), 0, *this->mixer2, 1);
  this->patchCords[0] = new AudioConnection(*this->rimshot->getOutput(), 0, *this->mixer2, 2);
  this->patchCords[0] = new AudioConnection(*this->hihat->getOutput(), 0, *this->mixer2, 3);
  this->patchCords[0] = new AudioConnection(*this->cymbal->getOutput(), 0, *this->mixer3, 0);
  this->patchCords[0] = new AudioConnection(*this->mixer1,  0, *this->output, 0);
  this->patchCords[1] = new AudioConnection(*this->mixer2, 0, *this->output, 1);
  this->patchCords[1] = new AudioConnection(*this->mixer3, 0, *this->output, 2);
}

/**
 * Singleton instance
 */
inline DS909 *DS909::getInstance()    {
  if (!instance){
     instance = new DS909;
  }
  return instance;
}

/**
 * Init
 */
inline void DS909::init(){
  device->init(
    "DS909",
    {
      Potentiometer, Potentiometer, Potentiometer,
      Potentiometer, Potentiometer, Potentiometer,
      Potentiometer, Potentiometer, Potentiometer
    }
  );

  // Device callbacks
  this->device->setHandlePotentiometerChange(0, onBDChange);
  this->device->setHandlePotentiometerChange(1, onSNChange);
  this->device->setHandlePotentiometerChange(2, onCPChange);
  this->device->setHandlePotentiometerChange(3, onLTChange);
  this->device->setHandlePotentiometerChange(4, onMTChange);
  this->device->setHandlePotentiometerChange(5, onHTChange);
  this->device->setHandlePotentiometerChange(6, onRMChange);
  this->device->setHandlePotentiometerChange(7, onHHChange);
  this->device->setHandlePotentiometerChange(8, onCYChange);
  // MIDI callbacks
  this->device->setHandleMidiNoteOn(onMidiNoteOn);
  this->device->setHandleMidiControlChange(0, 0, "BD", onMidiBDChange);
  this->device->setHandleMidiControlChange(0, 1, "SN", onMidiSNChange);
  this->device->setHandleMidiControlChange(0, 2, "CP", onMidiCPChange);
  this->device->setHandleMidiControlChange(0, 3, "LT", onMidiLTChange);
  this->device->setHandleMidiControlChange(0, 4, "MT", onMidiMTChange);
  this->device->setHandleMidiControlChange(0, 5, "HT", onMidiHTChange);
  this->device->setHandleMidiControlChange(0, 6, "RM", onMidiRMChange);
  this->device->setHandleMidiControlChange(0, 7, "HH", onMidiHHChange);
  this->device->setHandleMidiControlChange(0, 8, "CY", onMidiCYChange);
  
}

/**
 * Update
 */
inline void DS909::update(){
  this->device->update();
}

/**
 * Note on
 * 
 * @param channel The midi chnnnel
 * @param note The midi note
 * @param velocity The midi velocity
 */
inline void DS909::onMidiNoteOn(byte channel, byte note, byte velocity){
  switch(note){
    // Bass Drum
    case 36:
      getInstance()->bassDrum->noteOn();
      getInstance()->device->setLED(0, 4);
    break;
    // Snare
    case 40:
      getInstance()->snare->noteOn(velocity);
      getInstance()->device->setLED(1, 4);
    break;
    // Clap
    case 39:
      getInstance()->clap->noteOn();
      getInstance()->device->setLED(2, 4);
    break;
    // low Tom
    case 45:
      getInstance()->lowTom->noteOn();
      getInstance()->device->setLED(3, 4);
    break;
    // Mid Tom
    case 48:
      getInstance()->midTom->noteOn();
      getInstance()->device->setLED(4, 4);
    break;
    // High Tom
    case 50:
      getInstance()->hiTom->noteOn();
      getInstance()->device->setLED(5, 4);
    break;
    // Rimshot
    case 37:
      getInstance()->rimshot->noteOn(velocity);
      getInstance()->device->setLED(6, 4);
    break;
    // Closed High Hat
    case 42:
      getInstance()->hihat->noteOn(false);
      getInstance()->device->setLED(7, 4);
    break;
    // Open High Hat
    case 46:
      getInstance()->hihat->noteOn(true);
      getInstance()->device->setLED(7, 4);
    break;
    // Cymbal
    case 51:
      getInstance()->cymbal->noteOn(false);
      getInstance()->device->setLED(8, 4);
    break;
    // Crash
    case 49:
      getInstance()->cymbal->noteOn(true);
      getInstance()->device->setLED(8, 4);
    break;
    
    default:
    break;
  }
}

/**
 * Return the audio output
 */
inline AudioMixer4 * DS909::getOutput(){
  return this->output;
}

/**
 * On Bass Drum Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onBDChange(byte inputIndex, float value, int diffToPrevious){
  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte tune = constrain(100*cos(mix) + pow(mix,2), 0, 255);
  byte tone1 = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);
  byte decay = constrain(100*cos(mix+0.5*PI) + pow(mix,2), 0, 255);
  byte tone2 = constrain(100*cos(mix+PI) + pow(mix,2), 0, 255);

  byte tone = constrain(tone1 + tone2, 0,255);

  getInstance()->bassDrum->setPitch(tune);
  getInstance()->bassDrum->setDecay(decay);
  getInstance()->bassDrum->setTone(tone);
  
}

/**
 * On MIDI BD Change
 */
void DS909::onMidiBDChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onBDChange(control, mapValue, 255);
}

/**
 * On Snare Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onSNChange(byte inputIndex, float value, int diffToPrevious){
   float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte tone = constrain(100*cos(mix) + pow(mix,2), 0, 255);
  byte decay = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);
  byte pitch = constrain(100*cos(mix+0.5*PI) + pow(mix,2), 0, 255);
//  byte tone = constrain(100*cos(mix+PI) + pow(mix,2), 0, 255);

  getInstance()->snare->setTone(tone);
  getInstance()->snare->setDecay(decay);
  getInstance()->snare->setPitch(pitch);
}

/**
 * On MIDI SN Change
 */
void DS909::onMidiSNChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onSNChange(control, mapValue, 255);
}

/**
 * On Clap Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onCPChange(byte inputIndex, float value, int diffToPrevious){
  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte tone = constrain(100*cos(mix) + pow(mix,2), 0, 255);
  byte decay = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);

  getInstance()->clap->setDecay(decay);
  getInstance()->clap->setTone(tone);
}

/**
 * On MIDI CP Change
 */
void DS909::onMidiCPChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onCPChange(control, mapValue, 255);
}

/**
 * On Rimshot Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onRMChange(byte inputIndex, float value, int diffToPrevious){
float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte pitch = constrain(100*cos(mix) + pow(mix,2), 0, 255);
  byte tone = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);

  getInstance()->rimshot->setPitch(pitch);
  getInstance()->rimshot->setTone(tone);
}

/**
 * On MIDI RM Change
 */
void DS909::onMidiRMChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onRMChange(control, mapValue, 255);
}

/**
 * On Low Tom Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onLTChange(byte inputIndex, float value, int diffToPrevious){
  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte pitch = constrain(100*cos(mix) + pow(mix,2), 0, 10);
  byte decay = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);

  getInstance()->lowTom->setDecay(decay);
  getInstance()->lowTom->setPitch(pitch);
}

/**
 * On MIDI LT Change
 */
void DS909::onMidiLTChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onLTChange(control, mapValue, 255);
}

/**
 * On Mid Tom Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onMTChange(byte inputIndex, float value, int diffToPrevious){
  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte pitch = constrain(100*cos(mix) + pow(mix,2), 20, 30);
  byte decay = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);

  getInstance()->midTom->setDecay(decay);
  getInstance()->midTom->setPitch(pitch);
}

/**
 * On MIDI MT Change
 */
void DS909::onMidiMTChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onMTChange(control, mapValue, 255);
}

/**
 * On High Tom Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onHTChange(byte inputIndex, float value, int diffToPrevious){
  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    4*PI
  );
  
  byte pitch = constrain(100*cos(mix) + pow(mix,2), 60, 80);
  byte decay = constrain(100*cos(mix+1.5*PI) + pow(mix,2), 0, 255);

  getInstance()->hiTom->setDecay(decay);
  getInstance()->hiTom->setPitch(pitch);
}

/**
 * On MIDI HT Change
 */
void DS909::onMidiHTChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onHTChange(control, mapValue, 255);
}

/**
 * On Hihat Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onHHChange(byte inputIndex, float value, int diffToPrevious){
  float tune = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    200,
    800
  );
    
  getInstance()->hihat->setPitch(tune);
}

/**
 * On MIDI HH Change
 */
void DS909::onMidiHHChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onHHChange(control, mapValue, 255);
}

/**
 * On Cymbal Change
 * 
 * @param inputIndex The input index
 * @param value The input value
 * @param diffToPrevious The diff value to previous value
 */
inline void DS909::onCYChange(byte inputIndex, float value, int diffToPrevious){
  float tune = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    200,
    800
  );
    
  getInstance()->cymbal->setPitch(tune);
}

/**
 * On MIDI CY Change
 */
void DS909::onMidiCYChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onCYChange(control, mapValue, 255);
}
#endif
