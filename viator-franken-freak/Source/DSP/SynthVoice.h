#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class FrankenSynthVoice : public juce::SynthesiserVoice
{
public:
    FrankenSynthVoice();
    
    bool canPlaySound (juce::SynthesiserSound *) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double samplerate, int samplesPerBlock, int numOutputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void setADSRParams(float attack, float decay, float sustain, float release);
    void setOscParams(float osc1Volume);
    void setOscTune(int newTuneInterval);
    void setOscTimbre(float newTimbre);
    
    enum class OscType
    {
        kSin,
        kSquare,
        kSaw
    };
    
    void setOscType(OscType newOscType);
    
    
private:
    juce::dsp::ProcessSpec _spec;
    juce::dsp::Oscillator<float> _osc1 {[this](float x){return std::sin(x);}};
    juce::dsp::Oscillator<float> _carrierOsc {[this](float x){return std::sin(x);}};
    juce::dsp::Gain<float> _osc1Gain;
    juce::ADSR _adsr;
    juce::ADSR::Parameters _adsrParams;
    juce::AudioBuffer<float> _synthBuffer;
    
    OscType _oscType = OscType::kSin;
    static constexpr float _piInv = 1.0 / juce::MathConstants<float>::pi;
    
    float gain             {0.0};
    int   tune             {0};
    
    float timbre           {1.0};
    float timbreCompensate {0.55};
    float waveCompensate   {0.25};
    float softCoeffA       {1.5};
    float softCoeffB       {-0.5};
    void applyTimbre(juce::dsp::AudioBlock<float>& block);
};
