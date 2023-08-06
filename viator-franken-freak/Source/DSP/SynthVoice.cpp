#include "SynthVoice.h"

FrankenSynthVoice::FrankenSynthVoice()
{
    
}

bool FrankenSynthVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void FrankenSynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    _osc1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + tune));
    _timbreFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, _osc1.getFrequency());
    _adsr.noteOn();
}

void FrankenSynthVoice::stopNote (float velocity, bool allowTailOff)
{
    _adsr.noteOff();
    
    if (!allowTailOff || !_adsr.isActive())
    {
        clearCurrentNote();
    }
}

void FrankenSynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void FrankenSynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void FrankenSynthVoice::setADSRParams(float attack, float decay, float sustain, float release)
{
    _adsrParams.attack = attack;
    _adsrParams.decay = decay;
    _adsrParams.sustain = sustain;
    _adsrParams.release = release;
    _adsr.setParameters(_adsrParams);
}

void FrankenSynthVoice::setOscType(OscType newOscType)
{
    _oscType = newOscType;
    
    switch (_oscType)
    {
        case OscType::kSin:
        {
            _osc1.reset();
            _osc1.initialise([this](float x){return std::sin(x);});
            break;
        }
            
        case OscType::kSquare:
        {
            _osc1.reset();
            _osc1.initialise([this](float x){return x >= 0 ? 1.0 * waveCompensate : -1.0 * waveCompensate;});
            break;
        }
            
        case OscType::kSaw:
        {
            _osc1.reset();
            _osc1.initialise([this](float x){return juce::jmap(static_cast<float>(x), -juce::MathConstants<float>::pi, juce::MathConstants<float>::pi, -1.0f * waveCompensate, 1.0f * waveCompensate);});
            break;
        }
    }
}

void FrankenSynthVoice::setOscParams(float osc1Volume)
{
    gain = osc1Volume;
}

void FrankenSynthVoice::setOscTune(int newTuneInterval)
{
    tune = newTuneInterval;
}

void FrankenSynthVoice::setOscTimbre(float newTimbre)
{
    timbre = newTimbre - 2.0;
    
    if (timbre < 1.0)
    {
        timbre = 1.0;
    }
    
    // compensate the volume drop between 1 and 3 by double
    if (timbre < 3.0)
    {
        timbreCompensate = juce::jmap(timbre, 3.0f, 1.0f, 0.55f, 1.1f);
    }
    
    else
    {
        timbreCompensate = 0.55;
    }
}

void FrankenSynthVoice::prepareToPlay(double samplerate, int samplesPerBlock, int numOutputChannels)
{
    _spec.sampleRate = samplerate;
    _spec.maximumBlockSize = samplesPerBlock;
    _spec.numChannels = numOutputChannels;
    
    _osc1.prepare(_spec);
    _osc1.reset();
    
    _carrierOsc.prepare(_spec);
    _carrierOsc.reset();
    
    _osc1Gain.prepare(_spec);
    _osc1Gain.setRampDurationSeconds(0.01);
    
    _timbreFilter.prepare(_spec);
    _timbreFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kBandShelf);
    _timbreFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, 0.3);
    
    _adsr.setSampleRate(samplerate);
}

void FrankenSynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;
    
    _synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    _synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> block {_synthBuffer};
    _osc1Gain.setGainDecibels(gain);
    
    _osc1.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    applyTimbre(block);
    
    _osc1Gain.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    _adsr.applyEnvelopeToBuffer(_synthBuffer, 0, _synthBuffer.getNumSamples());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, _synthBuffer, channel, 0, numSamples);
        
        if (!_adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}

void FrankenSynthVoice::applyTimbre(juce::dsp::AudioBlock<float> &block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* data = block.getChannelPointer(channel);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            auto x = data[sample];
            
            if (_oscType == OscType::kSin)
            {
                data[sample] = (std::tanh(-timbre * x + x) - std::tanh(pow(x, 3.0f))) * timbreCompensate;
            }
            
            else
            {
                data[sample] = x;
            }
        }
    }
}
