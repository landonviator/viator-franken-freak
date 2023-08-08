#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorfrankenfreakAudioProcessor::ViatorfrankenfreakAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
, _treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    _frankenFreak.addSound(new FrankenSynthSound());
    _frankenFreak.addVoice(new FrankenSynthVoice());
    
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
}

ViatorfrankenfreakAudioProcessor::~ViatorfrankenfreakAudioProcessor()
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
}

//==============================================================================
const juce::String ViatorfrankenfreakAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ViatorfrankenfreakAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ViatorfrankenfreakAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ViatorfrankenfreakAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ViatorfrankenfreakAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ViatorfrankenfreakAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ViatorfrankenfreakAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ViatorfrankenfreakAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ViatorfrankenfreakAudioProcessor::getProgramName (int index)
{
    return {};
}

void ViatorfrankenfreakAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ViatorfrankenfreakAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        auto param = _parameterMap.getSliderParams()[i];
        auto range = juce::NormalisableRange<float>(param.min, param.max);
        
        if (param.isSkew == ViatorParameters::SliderParameterData::SkewType::kSkew)
        {
            range.setSkewForCentre(param.center);
        }

        if (param.isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            params.push_back (std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, param.paramName, range, param.initial, valueToTextFunction, textToValueFunction));
        }
        
        else
        {
            params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, range, param.initial));
        }
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        auto param = _parameterMap.getButtonParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, _parameterMap.getButtonParams()[i].initial));
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        auto param = _parameterMap.getMenuParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, param.choices, param.defaultIndex));
    }
    
    return { params.begin(), params.end() };
}

void ViatorfrankenfreakAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)

{
    if (_frankenFreak.getSampleRate() < 44100.0f)
        return;
    
    if (parameterID == ViatorParameters::osc1ChoiceID || parameterID == ViatorParameters::osc2ChoiceID)
    {
        auto oscType = static_cast<FrankenSynthVoice::OscType>(_treeState.getRawParameterValue(ViatorParameters::osc1ChoiceID)->load());
        auto osc2Type = static_cast<FrankenSynthVoice::OscType>(_treeState.getRawParameterValue(ViatorParameters::osc2ChoiceID)->load());
        
        for (int i = 0; i < _frankenFreak.getNumVoices(); i++)
        {
            if (auto voice = dynamic_cast<FrankenSynthVoice*>(_frankenFreak.getVoice(i)))
            {
                voice->setOscType(oscType, osc2Type);
            }
        }
    }
    
    updateParameters();
    
}

void ViatorfrankenfreakAudioProcessor::updateParameters()
{
    auto attack = _treeState.getRawParameterValue(ViatorParameters::attackID)->load();
    auto decay = _treeState.getRawParameterValue(ViatorParameters::decayID)->load();
    auto sustain = _treeState.getRawParameterValue(ViatorParameters::sustainID)->load();
    auto release = _treeState.getRawParameterValue(ViatorParameters::releaseID)->load();
    
    auto osc1Volume = _treeState.getRawParameterValue(ViatorParameters::osc1GainID)->load();
    auto osc1Tune = _treeState.getRawParameterValue(ViatorParameters::osc1TuneID)->load();
    auto osc1Timbre = _treeState.getRawParameterValue(ViatorParameters::osc1TimbreID)->load();
    
    auto osc2Volume = _treeState.getRawParameterValue(ViatorParameters::osc2GainID)->load();
    auto osc2Tune = _treeState.getRawParameterValue(ViatorParameters::osc2TuneID)->load();
    auto osc2Timbre = _treeState.getRawParameterValue(ViatorParameters::osc2TimbreID)->load();
    
    for (int i = 0; i < _frankenFreak.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<FrankenSynthVoice*>(_frankenFreak.getVoice(i)))
        {
            voice->setADSRParams(attack, decay, sustain, release);
            
            voice->setOscParams(osc1Volume, osc2Volume);
            voice->setOscTune(osc1Tune, osc2Tune);
            voice->setOscTimbre(osc1Timbre, osc2Timbre);
        }
    }
}

//==============================================================================
void ViatorfrankenfreakAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _frankenFreak.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < _frankenFreak.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<FrankenSynthVoice*>(_frankenFreak.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, sampleRate, getTotalNumOutputChannels());
        }
    }
    
    updateParameters();
}

void ViatorfrankenfreakAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ViatorfrankenfreakAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ViatorfrankenfreakAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    _frankenFreak.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool ViatorfrankenfreakAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ViatorfrankenfreakAudioProcessor::createEditor()
{
    return new ViatorfrankenfreakAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void ViatorfrankenfreakAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ViatorfrankenfreakAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ViatorfrankenfreakAudioProcessor();
}
