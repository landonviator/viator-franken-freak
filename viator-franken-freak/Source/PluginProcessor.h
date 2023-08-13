#pragma once
#include <JuceHeader.h>
#include "DSP/SynthSound.h"
#include "DSP/SynthVoice.h"
#include "globals/Parameters.h"

class ViatorfrankenfreakAudioProcessor  : public juce::AudioProcessor
, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ViatorfrankenfreakAudioProcessor();
    ~ViatorfrankenfreakAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // parameters
    ViatorParameters::Params _parameterMap;
    juce::AudioProcessorValueTreeState _treeState;

private:
    
    juce::Synthesiser _frankenFreak;
    juce::dsp::ProcessSpec _spec;
    juce::dsp::LadderFilter<float> _synthFilter;
    viator_dsp::BitCrusher<float> _bitCrusher;
    juce::dsp::Reverb _reverb;
    juce::dsp::Reverb::Parameters _reverbParams;
    juce::dsp::Gain<float> _reverbCompensate;
    juce::dsp::Gain<float> _reverbVolume;
    
    enum class ArpDirection
    {
      kForward,
      kRandom,
      kBackward
    };
    
    ArpDirection _arpDirection = ArpDirection::kForward;
    
    juce::SortedSet<int> notes;
    int currentNote, lastNoteValue;
    int time;
    float rate;
    void arpeggiate(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, float arpSpeed);
    juce::Optional<double> projectBPM;
    double bpm = 120.0;
    juce::Optional<juce::AudioPlayHead::PositionInfo> positionInfo;
    int phaseOffsetSamples {0};
    int accumulatedTime {0};
    double quarterNoteDuration {0};
    int samplePosition {0};
    
    // parameters
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    static juce::String valueToTextFunction(float x) { return juce::String(static_cast<int>(x)); }
    static float textToValueFunction(const juce::String& str) { return static_cast<int>(str.getFloatValue()); }
    void updateParameters();
    
    const int _versionNumber = 1;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorfrankenfreakAudioProcessor)
};
