#pragma once
#include <JuceHeader.h>

class FrankenSynthSound : public juce::SynthesiserSound
{
public:
    FrankenSynthSound(){};
    
    bool appliesToNote    (int midiNoteNumber) override {return true;};
    bool appliesToChannel (int midiChannel) override {return true;};
};
