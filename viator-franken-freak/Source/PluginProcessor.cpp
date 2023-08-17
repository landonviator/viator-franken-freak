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
            int rangeStart = static_cast<int>(range.start);
            int rangeEnd = static_cast<int>(range.end);
            params.push_back (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, rangeStart, rangeEnd, param.initial));
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
    
    if (parameterID == ViatorParameters::ladderChoiceID)
    {
        auto filterType = _treeState.getRawParameterValue(ViatorParameters::ladderChoiceID)->load();
        _synthFilter.setMode(static_cast<juce::dsp::LadderFilter<float>::Mode>(filterType));
    }
    
    if (parameterID == ViatorParameters::arpOctaveID)
    {
        notes.clear();
    }
    
    updateParameters();
    
}

void ViatorfrankenfreakAudioProcessor::updateParameters()
{
    // synth
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
    
    auto amFreq = _treeState.getRawParameterValue(ViatorParameters::amFreqID)->load();
    auto amDepth = _treeState.getRawParameterValue(ViatorParameters::amDepthID)->load();
    auto driftFreq = _treeState.getRawParameterValue(ViatorParameters::driftFreqID)->load();
    auto driftDepth = _treeState.getRawParameterValue(ViatorParameters::driftDepthID)->load();
    
    auto osc1Power = _treeState.getRawParameterValue(ViatorParameters::osc1PowerID)->load();
    auto osc2Power = _treeState.getRawParameterValue(ViatorParameters::osc2PowerID)->load();
    auto oscModPower = _treeState.getRawParameterValue(ViatorParameters::modPowerID)->load();
    
    for (int i = 0; i < _frankenFreak.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<FrankenSynthVoice*>(_frankenFreak.getVoice(i)))
        {
            voice->setOscParams(osc1Volume, osc2Volume);
            voice->setOscTimbre(osc1Timbre, osc2Timbre);
            voice->setOscTune(osc1Tune, osc2Tune);
            voice->setOscAmParams(amFreq, amDepth, driftFreq, driftDepth);
            voice->setADSRParams(attack, decay, sustain, release);
            voice->setPower(osc1Power, osc2Power, oscModPower, oscModPower);
        }
    }

    // filter
    auto filterCutoff = _treeState.getRawParameterValue(ViatorParameters::ladderCutoffID)->load();
    auto filterReso = _treeState.getRawParameterValue(ViatorParameters::ladderResoID)->load();
    _synthFilter.setCutoffFrequencyHz(filterCutoff);
    _synthFilter.setResonance(filterReso);
    
    // fx
    auto bitDepth = _treeState.getRawParameterValue(ViatorParameters::crusherBitDepthID)->load();
    auto crusherMix = _treeState.getRawParameterValue(ViatorParameters::crusherMixID)->load();
    auto drive = _treeState.getRawParameterValue(ViatorParameters::ladderDriveID)->load();
    auto crusherVolume = _treeState.getRawParameterValue(ViatorParameters::crusherVolumeID)->load();
    _bitCrusher.setBitDepth(bitDepth);
    _bitCrusher.setDrive(drive);
    _bitCrusher.setMix(crusherMix);
    _bitCrusher.setVolume(crusherVolume);
    
    auto verbSize = _treeState.getRawParameterValue(ViatorParameters::verbSizeID)->load() * 0.01;
    auto verbDamp = _treeState.getRawParameterValue(ViatorParameters::verbDampID)->load() * 0.01;
    auto verbVolume = _treeState.getRawParameterValue(ViatorParameters::verbVolumeID)->load();
    auto verbMix = _treeState.getRawParameterValue(ViatorParameters::verbMixID)->load() * 0.01;
    _reverbParams.roomSize = verbSize;
    _reverbParams.damping = verbDamp;
    _reverbParams.width = 1.0;
    _reverbParams.wetLevel = verbMix;
    _reverbParams.dryLevel = 1.0;
    _reverb.setParameters(_reverbParams);
    _reverbVolume.setGainDecibels(verbVolume);
    
    // arp
    auto arpDir = _treeState.getRawParameterValue(ViatorParameters::arpDirID)->load();
    _arpDirection = static_cast<ArpDirection>(arpDir);
}

//==============================================================================
void ViatorfrankenfreakAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _spec.sampleRate = sampleRate;
    _spec.numChannels = getTotalNumOutputChannels();
    _spec.maximumBlockSize = samplesPerBlock;
    
    _frankenFreak.setCurrentPlaybackSampleRate(_spec.sampleRate);
    
    for (int i = 0; i < _frankenFreak.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<FrankenSynthVoice*>(_frankenFreak.getVoice(i)))
        {
            voice->prepareToPlay(_spec.sampleRate, _spec.maximumBlockSize, getTotalNumOutputChannels());
        }
    }
    
    _synthFilter.prepare(_spec);
    auto filterType = _treeState.getRawParameterValue(ViatorParameters::ladderChoiceID)->load();
    _synthFilter.setMode(static_cast<juce::dsp::LadderFilter<float>::Mode>(filterType));
    
    _bitCrusher.prepare(_spec);
    _reverb.prepare(_spec);
    _reverbCompensate.prepare(_spec);
    _reverbCompensate.setGainDecibels(-6.1);
    _reverbVolume.prepare(_spec);
    _reverbVolume.setRampDurationSeconds(0.02);
    
    juce::ignoreUnused (samplesPerBlock);

    notes.clear();
    currentNote = 0;
    lastNoteValue = -1;
    time = 0;
    rate = static_cast<float> (sampleRate);
    
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
    //updateParameters();
    
    //juce::dsp::AudioBlock<float> block {buffer};
//    auto filterPower = _treeState.getRawParameterValue(ViatorParameters::filterPowerID)->load();
//    auto crusherPower = _treeState.getRawParameterValue(ViatorParameters::crusherPowerID)->load();
//    auto verbPower = _treeState.getRawParameterValue(ViatorParameters::verbPowerID)->load();
//    auto arpPower = _treeState.getRawParameterValue(ViatorParameters::arpPowerID)->load();
//    auto arpSpeed = _treeState.getRawParameterValue(ViatorParameters::arpSpeedID)->load();
//    auto numOctaves = _treeState.getRawParameterValue(ViatorParameters::arpOctaveID)->load();
//
//    if (arpPower)
//    {
//        populateArp(midiMessages, numOctaves);
//        arpeggiate(buffer, midiMessages, arpSpeed, numOctaves);
//    }
                
    _frankenFreak.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
 
//    if (filterPower)
//    {
//        _synthFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
//    }
//
//    if (crusherPower)
//    {
//        _bitCrusher.processBuffer(buffer);
//    }
//
//    if (verbPower)
//    {
//        _reverb.process(juce::dsp::ProcessContextReplacing<float>(block));
//        _reverbCompensate.process(juce::dsp::ProcessContextReplacing<float>(block));
//        _reverbVolume.process(juce::dsp::ProcessContextReplacing<float>(block));
//    }
//
//    // safe clip
//    viator_utils::utils::hardClipBlock(block);
}

void ViatorfrankenfreakAudioProcessor::arpeggiate(juce::AudioBuffer<float>& buffer, juce::MidiBuffer &midiMessages, float arpSpeed, float numOctaves)
{
    // however we use the buffer to get timing information
    auto numSamples = buffer.getNumSamples();

    // Calculate the note duration based on a fixed musical note length (e.g., quarter note)
    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (arpSpeed)))));

    if ((time + numSamples) >= noteDuration)
    {
        auto offset = juce::jmax (0, juce::jmin ((int) (noteDuration - time), numSamples - 1));

        if (lastNoteValue > 0)
        {
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), offset);
            lastNoteValue = -1;
        }

        if (notes.size() > 0)
        {
            if (_arpDirection == ArpDirection::kForward)
            {
                currentNote = (currentNote + 1) % notes.size();
            }
            
            else if (_arpDirection == ArpDirection::kBackward)
            {
                currentNote = (currentNote - 1 + notes.size()) % notes.size();
            }
            
            else
            {
                currentNote = juce::Random::getSystemRandom().nextInt (notes.size());
            }
            
            lastNoteValue = notes[currentNote];
            midiMessages.addEvent (juce::MidiMessage::noteOn  (1, lastNoteValue, (uint8_t) 127), offset);
        }
    }
    
    time = (time + numSamples) % noteDuration;
}

void ViatorfrankenfreakAudioProcessor::populateArp(juce::MidiBuffer &midiMessages, float numOctaves)
{
    // add notes including the octaves to the array
    for (int octaveOffset = 0; octaveOffset < numOctaves; ++octaveOffset)
    {
        for (const auto metadata : midiMessages)
        {
            const auto msg = metadata.getMessage();
            
            if (msg.isNoteOn())
            {
                int noteValue = msg.getNoteNumber() + (octaveOffset * 12); // Add octave offset in semitones
                notes.add(noteValue);
            }
            
            else if (msg.isNoteOff())
            {
                int noteValue = msg.getNoteNumber() + (octaveOffset * 12); // Add octave offset in semitones
                notes.removeValue(noteValue);
            }
        }
    }
    
    midiMessages.clear();
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
    // Save params
    //_treeState.state.appendChild(_variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream (stream);
}

void ViatorfrankenfreakAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    //_variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        _treeState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ViatorfrankenfreakAudioProcessor();
}
