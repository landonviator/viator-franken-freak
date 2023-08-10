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
    void setOscParams(float osc1Volume, float osc2Volume);
    void setOscTune(int newTuneInterval, int newTuneInterval2);
    void setOscTimbre(float newTimbre, float newTimbre2);
    void setOscAmParams(float newAmFreq, float newAmDepth, float newDrift, float newDriftDepth);
    
    enum class OscType
    {
        kSin,
        kSquare,
        kSaw
    };
    
    void setOscType(OscType newOscType, OscType newOsc2Type);
    
    
private:
    juce::dsp::ProcessSpec _spec;
    juce::ADSR _adsr1;
    juce::ADSR::Parameters _adsrParams1;
    juce::ADSR _adsr2;
    juce::ADSR::Parameters _adsrParams2;
    
    float sinCompensate = 0.3;
    
    // osc 1
    juce::dsp::Oscillator<float> _mainOsc {[this](float x){return std::sin(x) * sinCompensate;}};
    juce::dsp::Gain<float> _mainOscGain;
    juce::dsp::Gain<float> _mainOscCompensation;
    juce::AudioBuffer<float> _synthBuffer;
    OscType _oscType = OscType::kSin;
    float gain             {0.0};
    float gainCompensate   {0.0};
    int   tune             {0};
    float timbre           {1.0};
    float timbreCompensate {0.55};
    float waveCompensate   {0.25};
    float softCoeffA       {1.5};
    float softCoeffB       {-0.5};
    void applyTimbre(juce::dsp::AudioBlock<float>& block);
    viator_dsp::SVFilter<float> _timbreFilter1;
    float _freq1 = 440.0f;
    
    // osc 2
    juce::dsp::Oscillator<float> _auxOsc {[this](float x){return std::sin(x) * sinCompensate;}};
    juce::dsp::Gain<float> _auxOscGain;
    juce::dsp::Gain<float> _auxOscCompensation;
    juce::AudioBuffer<float> _synthBuffer2;
    OscType _osc2Type = OscType::kSin;
    float gain2             {0.0};
    float gainCompensate2   {0.0};
    int   tune2             {0};
    float timbre2           {1.0};
    float timbreCompensate2 {0.55};
    float waveCompensate2   {0.25};
    viator_dsp::SVFilter<float> _timbreFilter2;
    float softCoeffA2       {1.5};
    float softCoeffB2       {-0.5};
    void applyTimbre2(juce::dsp::AudioBlock<float>& block);
    float _freq2 = 440.0f;
    
    // am
    juce::dsp::Oscillator<float> _amOsc1 {[this](float x){return std::sin(x);}};
    juce::dsp::Oscillator<float> _amOsc2 {[this](float x){return std::sin(x);}};
    juce::dsp::Oscillator<float> _driftOsc1 {[this](float x){return std::sin(x);}};
    juce::dsp::Oscillator<float> _driftOsc2 {[this](float x){return std::sin(x);}};
    float _amDepth = 1.0;
    float _driftDepth = 1.0;
    float _driftFreq = 1.0;
    
    void applyDrift(juce::AudioBuffer<float>& buffer, juce::dsp::Oscillator<float>& carrier, juce::dsp::Oscillator<float>& modulator, float carrierFreq, float driftDepth);
    
    static constexpr float _piInv = 1.0 / juce::MathConstants<float>::pi;
};
