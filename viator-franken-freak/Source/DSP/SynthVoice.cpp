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
    _freq1 = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + tune);
    _freq2 = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + tune2);
    _timbreFilter1.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, _mainOsc.getFrequency() * 2.0);
    _timbreFilter2.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, _auxOsc.getFrequency() * 2.0);
    _adsr1.noteOn();
    _adsr2.noteOn();
}

void FrankenSynthVoice::stopNote (float velocity, bool allowTailOff)
{
    _adsr1.noteOff();
    _adsr2.noteOff();
    
    if (!allowTailOff || !_adsr1.isActive() || !_adsr2.isActive())
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
    _adsrParams1.attack = attack;
    _adsrParams1.decay = decay;
    _adsrParams1.sustain = sustain;
    _adsrParams1.release = release;
    _adsr1.setParameters(_adsrParams1);
    _adsrParams2.attack = attack;
    _adsrParams2.decay = decay;
    _adsrParams2.sustain = sustain;
    _adsrParams2.release = release;
    _adsr2.setParameters(_adsrParams2);
}

void FrankenSynthVoice::setOscType(OscType newOscType, OscType newOsc2Type)
{
    _oscType = newOscType;
    _osc2Type = newOsc2Type;
    
    switch (_oscType)
    {
        case OscType::kSin:
        {
            _mainOsc.reset();
            _mainOsc.initialise([this](float x){return std::sin(x) * sinCompensate;});
            break;
        }
            
        case OscType::kSquare:
        {
            _mainOsc.reset();
            _mainOsc.initialise([this](float x){return x >= 0 ? 1.0 * waveCompensate : -1.0 * waveCompensate;});
            break;
        }
            
        case OscType::kSaw:
        {
            _mainOsc.reset();
            _mainOsc.initialise([this](float x){return juce::jmap(static_cast<float>(x), -juce::MathConstants<float>::pi, juce::MathConstants<float>::pi, -1.0f * waveCompensate, 1.0f * waveCompensate);});
            break;
        }
    }
    
    switch (_osc2Type)
    {
        case OscType::kSin:
        {
            _auxOsc.reset();
            _auxOsc.initialise([this](float x){return std::sin(x) * sinCompensate;});
            break;
        }
            
        case OscType::kSquare:
        {
            _auxOsc.reset();
            _auxOsc.initialise([this](float x){return x >= 0 ? 1.0 * waveCompensate : -1.0 * waveCompensate;});
            break;
        }
            
        case OscType::kSaw:
        {
            _auxOsc.reset();
            _auxOsc.initialise([this](float x){return juce::jmap(static_cast<float>(x), -juce::MathConstants<float>::pi, juce::MathConstants<float>::pi, -1.0f * waveCompensate, 1.0f * waveCompensate);});
            break;
        }
    }
}

void FrankenSynthVoice::setOscParams(float osc1Volume, float osc2Volume)
{
    gain = osc1Volume;
    gain2 = osc2Volume;
}

void FrankenSynthVoice::setOscTune(int newTuneInterval, int newTuneInterval2)
{
    tune = newTuneInterval;
    tune2 = newTuneInterval2;
}

void FrankenSynthVoice::setOscTimbre(float newTimbre, float newTimbre2)
{
    timbre.setTargetValue(juce::jmap(newTimbre, -10.0f, 10.0f, 1.0f, 5.0f));
    
    if (newTimbre < 0.0)
    {
        timbreCompensate.setTargetValue(juce::Decibels::decibelsToGain(-newTimbre * 2.0));
    }
    
    else
    {
        timbreCompensate.setTargetValue(juce::Decibels::decibelsToGain(-newTimbre));
    }
    
    // convert timbre to high shelf gain with compensation
    auto timbreGain = juce::jmap(newTimbre, -10.0f, 10.0f, -15.0f, 15.0f);
    _timbreFilter1.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, timbreGain);
    
    timbre2.setTargetValue(juce::jmap(newTimbre2, -10.0f, 10.0f, 1.0f, 5.0f));
    
    if (newTimbre2 < 0.0)
    {
        timbreCompensate2.setTargetValue(juce::Decibels::decibelsToGain(-newTimbre2 * 2.0));
    }
    
    else
    {
        timbreCompensate2.setTargetValue(juce::Decibels::decibelsToGain(-newTimbre2));
    }
    
    // convert timbre to high shelf gain with compensation
    auto timbreGain2 = juce::jmap(newTimbre2, -10.0f, 10.0f, -15.0f, 15.0f);
    _timbreFilter2.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, timbreGain2);
}

void FrankenSynthVoice::setOscAmParams(float newAmFreq, float newAmDepth, float newDrift, float newDriftDepth)
{
    _amOsc1.setFrequency(newAmFreq);
    _amOsc2.setFrequency(newAmFreq);
    _driftOsc1.setFrequency(newAmFreq);
    _driftOsc2.setFrequency(newAmFreq);
    _amDepth = newAmDepth;
    _driftDepth = newDriftDepth;
    _driftFreq = newDrift;
}

void FrankenSynthVoice::setPower(bool osc1Power, bool osc2Power, bool oscMod1Power, bool oscMod2Power)
{
    _osc1Power = osc1Power;
    _osc2Power = osc2Power;
    _oscMod1Power = oscMod1Power;
    _oscMod2Power = oscMod2Power;
}

void FrankenSynthVoice::prepareToPlay(double samplerate, int samplesPerBlock, int numOutputChannels)
{
    _spec.sampleRate = samplerate;
    _spec.maximumBlockSize = samplesPerBlock;
    _spec.numChannels = numOutputChannels;
    
    // osc 1
    _mainOsc.prepare(_spec);
    _mainOsc.reset();
    _mainOscGain.prepare(_spec);
    _mainOscGain.setRampDurationSeconds(0.05);
    _mainOscCompensation.prepare(_spec);
    _mainOscCompensation.setRampDurationSeconds(0.01);
    _mainOscCompensation.setGainDecibels(0.0);
    _timbreFilter1.prepare(_spec);
    _timbreFilter1.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighShelf);
    _timbreFilter1.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, 0.75);
    
    // osc 2
    _auxOsc.prepare(_spec);
    _auxOsc.reset();
    _auxOscGain.prepare(_spec);
    _auxOscGain.setRampDurationSeconds(0.01);
    _auxOscCompensation.prepare(_spec);
    _auxOscCompensation.setRampDurationSeconds(0.01);
    _auxOscCompensation.setGainDecibels(0.0);
    _timbreFilter2.prepare(_spec);
    _timbreFilter2.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighShelf);
    _timbreFilter2.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, 0.75);
    
    _adsr1.setSampleRate(samplerate);
    _adsr2.setSampleRate(samplerate);
    
    // mod
    _amOsc1.prepare(_spec);
    _amOsc1.reset();
    _amOsc2.prepare(_spec);
    _amOsc2.reset();
    _driftOsc1.prepare(_spec);
    _driftOsc1.reset();
    _driftOsc2.prepare(_spec);
    _driftOsc1.reset();
    
    timbre.reset(_spec.sampleRate, 0.05);
    timbreCompensate.reset(_spec.sampleRate, 0.05);
    timbre2.reset(_spec.sampleRate, 0.05);
    timbreCompensate2.reset(_spec.sampleRate, 0.05);
}

void FrankenSynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;
    
    _synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    _synthBuffer.clear();
    _synthBuffer2.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    _synthBuffer2.clear();
    
    juce::dsp::AudioBlock<float> block1 {_synthBuffer};
    juce::dsp::AudioBlock<float> block2 {_synthBuffer2};
    
    _mainOsc.setFrequency(_freq1 * 0.5);
    
    // mod
    if (_oscMod1Power)
    {
        applyAM(block1, _amDepth, _amOsc1);
        _driftOsc1.setFrequency(_driftFreq);
    }
    
    applyDrift1();
    
    // timbre
    if (_oscType == OscType::kSin)
    {
        applyTimbre(block1);
    }
    
    else
    {
        _timbreFilter1.process(juce::dsp::ProcessContextReplacing<float>(block1));
        _mainOscCompensation.process(juce::dsp::ProcessContextReplacing<float>(block1));
    }
    
    // osc 1
    if (_osc1Power)
    {
        _mainOscGain.setGainDecibels(gain);
        _mainOscGain.process(juce::dsp::ProcessContextReplacing<float>(block1));
    }
    
    // adsr
    _adsr1.applyEnvelopeToBuffer(_synthBuffer, 0, _synthBuffer.getNumSamples());
    
    _auxOsc.setFrequency(_freq2 * 0.5);
    
    // mod
    if (_oscMod2Power)
    {
        applyAM(block2, _amDepth, _amOsc2);
        _driftOsc2.setFrequency(_driftFreq);
    }
    
    applyDrift2();
    
    // timbre
    if (_osc2Type == OscType::kSin)
    {
        applyTimbre2(block2);
    }
    
    else
    {
        _timbreFilter2.process(juce::dsp::ProcessContextReplacing<float>(block2));
        _auxOscCompensation.process(juce::dsp::ProcessContextReplacing<float>(block2));
    }
    
    // osc 2
    if (_osc2Power)
    {
        _auxOscGain.setGainDecibels(gain2);
        _auxOscGain.process(juce::dsp::ProcessContextReplacing<float>(block2));
    }
    
    // adsr
    _adsr2.applyEnvelopeToBuffer(_synthBuffer2, 0, _synthBuffer2.getNumSamples());
    
    // add synth buffers to main buffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, _synthBuffer, channel, 0, numSamples);
        outputBuffer.addFrom(channel, startSample, _synthBuffer2, channel, 0, numSamples);
        
        if (!_adsr1.isActive() || !_adsr2.isActive())
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
            data[sample] = (std::tanh(-timbre.getNextValue() * x + x) - std::tanh(pow(x, 3.0f))) * timbreCompensate.getNextValue();
        }
    }
}

void FrankenSynthVoice::applyTimbre2(juce::dsp::AudioBlock<float> &block)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* data = block.getChannelPointer(channel);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            auto x = data[sample];
            data[sample] = (std::tanh(-timbre2.getNextValue() * x + x) - std::tanh(pow(x, 3.0f))) * timbreCompensate2.getNextValue();
        }
    }
}

void FrankenSynthVoice::applyAM(juce::dsp::AudioBlock<float> &block, float depth, juce::dsp::Oscillator<float> &modulator)
{
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* data = block.getChannelPointer(channel);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            auto x = data[sample];
            data[sample] = x * (1.0f + depth * modulator.processSample(x));
        }
    }
}

void FrankenSynthVoice::applyDrift1()
{
    auto data = _synthBuffer.getArrayOfWritePointers();
    
    for (int sample = 0; sample < _synthBuffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < _synthBuffer.getNumChannels(); ++channel)
        {
            auto x = data[channel][sample];
            
            auto driftSignal = _driftOsc1.processSample(x) * _oscMod1Power;
            auto driftFreq = driftSignal * _driftDepth;
            
            if (_oscMod1Power)
            {
                _mainOsc.setFrequency(_freq1 * 0.5 + driftFreq);
            }
            
            data[channel][sample] = _mainOsc.processSample(x) * _osc1Power;
        }
    }
}

void FrankenSynthVoice::applyDrift2()
{
    auto data = _synthBuffer2.getArrayOfWritePointers();
    
    for (int sample = 0; sample < _synthBuffer2.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < _synthBuffer2.getNumChannels(); ++channel)
        {
            auto x = data[channel][sample];
            
            auto driftSignal = _driftOsc2.processSample(x) * _oscMod2Power;
            auto driftFreq = driftSignal * _driftDepth;
            
            if (_oscMod2Power)
            {
                _auxOsc.setFrequency(_freq2 * 0.5 + driftFreq);
            }
            
            data[channel][sample] = _auxOsc.processSample(x) * _osc2Power;
        }
    }
}
