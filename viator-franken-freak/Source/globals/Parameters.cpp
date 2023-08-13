#include "Parameters.h"


ViatorParameters::Params::Params()
{
    initSliderParams();
    initButtonParams();
    initMenuParams();
}

void ViatorParameters::Params::initSliderParams()
{
    using skew = SliderParameterData::SkewType;
    using type = SliderParameterData::NumericType;
    
    // osc 1
    _sliderParams.push_back({ViatorParameters::osc1TimbreID, ViatorParameters::osc1TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::osc1TuneID, ViatorParameters::osc1TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::osc1GainID, ViatorParameters::osc1GainName, -30.0f, 30.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _osc1SliderParams.push_back({ViatorParameters::osc1GainID, ViatorParameters::osc1GainName, -30.0f, 30.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc1SliderParams.push_back({ViatorParameters::osc1TimbreID, ViatorParameters::osc1TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc1SliderParams.push_back({ViatorParameters::osc1TuneID, ViatorParameters::osc1TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    
    // osc 2
    _sliderParams.push_back({ViatorParameters::osc2TimbreID, ViatorParameters::osc2TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::osc2TuneID, ViatorParameters::osc2TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::osc2GainID, ViatorParameters::osc2GainName, -30.0f, 30.0f, -0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _osc2SliderParams.push_back({ViatorParameters::osc2GainID, ViatorParameters::osc2GainName, -30.0f, 30.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc2SliderParams.push_back({ViatorParameters::osc2TimbreID, ViatorParameters::osc2TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc2SliderParams.push_back({ViatorParameters::osc2TuneID, ViatorParameters::osc2TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    
    // adsr
    _sliderParams.push_back({ViatorParameters::attackID, ViatorParameters::attackName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::decayID, ViatorParameters::decayName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::sustainID, ViatorParameters::sustainName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::releaseID, ViatorParameters::releaseName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _adsrSliderParams.push_back({ViatorParameters::attackID, ViatorParameters::attackName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::decayID, ViatorParameters::decayName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::sustainID, ViatorParameters::sustainName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::releaseID, ViatorParameters::releaseName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    // mod
    _sliderParams.push_back({ViatorParameters::amFreqID, ViatorParameters::amFreqName, 0.1f, 10.0f, 1.0f, skew::kSkew, 1.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::amDepthID, ViatorParameters::amDepthName, 0.0f, 1.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::driftFreqID, ViatorParameters::driftFreqName, 0.1f, 10.0f, 1.0f, skew::kSkew, 1.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::driftDepthID, ViatorParameters::driftDepthName, 0.0f, 100.0f, 0.0f, skew::kSkew, 15.0, type::kFloat});
    
    _modSliderParams.push_back({ViatorParameters::amFreqID, ViatorParameters::amFreqName, 0.1f, 10.0f, 1.0f, skew::kSkew, 1.0, type::kFloat});
    _modSliderParams.push_back({ViatorParameters::amDepthID, ViatorParameters::amDepthName, 0.0f, 1.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _modSliderParams.push_back({ViatorParameters::driftFreqID, ViatorParameters::driftFreqName, 0.1f, 10.0f, 1.0f, skew::kSkew, 1.0, type::kFloat});
    _modSliderParams.push_back({ViatorParameters::driftDepthID, ViatorParameters::driftDepthName, 0.0f, 100.0f, 0.0f, skew::kSkew, 15.0, type::kFloat});
    
    // filter
    _sliderParams.push_back({ViatorParameters::ladderCutoffID, ViatorParameters::ladderCutoffName, 20.0f, 20000.0f, 1000.0f, skew::kSkew, 1000.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::ladderResoID, ViatorParameters::ladderResoName, 0.0f, 0.95f, 0.05f, skew::kNoSkew, 0.0, type::kFloat});
    
    _ladderSliderParams.push_back({ViatorParameters::ladderCutoffID, ViatorParameters::ladderCutoffName, 20.0f, 20000.0f, 1000.0f, skew::kSkew, 1000.0, type::kInt});
    _ladderSliderParams.push_back({ViatorParameters::ladderResoID, ViatorParameters::ladderResoName, 0.0f, 0.95f, 0.05f, skew::kNoSkew, 0.0, type::kFloat});
    
    // crusher
    _sliderParams.push_back({ViatorParameters::ladderDriveID, ViatorParameters::ladderDriveName, 0.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::crusherBitDepthID, ViatorParameters::crusherBitDepthName, 1.0f, 16.0f, 1.0f, skew::kSkew, 14.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::crusherMixID, ViatorParameters::crusherMixName, 0.0f, 100.0f, 100.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::crusherVolumeID, ViatorParameters::crusherVolumeName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _crusherSliderParams.push_back({ViatorParameters::ladderDriveID, ViatorParameters::ladderDriveName, 0.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _crusherSliderParams.push_back({ViatorParameters::crusherBitDepthID, ViatorParameters::crusherBitDepthName, 1.0f, 16.0f, 1.0f, skew::kSkew, 14.0, type::kFloat});
    _crusherSliderParams.push_back({ViatorParameters::crusherMixID, ViatorParameters::crusherMixName, 0.0f, 100.0f, 100.0f, skew::kNoSkew, 0.0, type::kInt});
    _crusherSliderParams.push_back({ViatorParameters::crusherVolumeID, ViatorParameters::crusherVolumeName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    // reverb
    _sliderParams.push_back({ViatorParameters::verbSizeID, ViatorParameters::verbSizeName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::verbDampID, ViatorParameters::verbDampName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::verbMixID, ViatorParameters::verbMixName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::verbVolumeID, ViatorParameters::verbVolumeName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _reverbSliderParams.push_back({ViatorParameters::verbSizeID, ViatorParameters::verbSizeName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _reverbSliderParams.push_back({ViatorParameters::verbDampID, ViatorParameters::verbDampName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _reverbSliderParams.push_back({ViatorParameters::verbMixID, ViatorParameters::verbMixName, 0.0f, 100.0f, 50.0f, skew::kNoSkew, 0.0, type::kInt});
    _reverbSliderParams.push_back({ViatorParameters::verbVolumeID, ViatorParameters::verbVolumeName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    // arp
    _sliderParams.push_back({ViatorParameters::arpSpeedID, ViatorParameters::arpSpeedName, 0.0f, 1.0f, 0.5f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::arpDirID, ViatorParameters::arpDirName, 0.0f, 2.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::arpOctaveID, ViatorParameters::arpOctaveName, 0.0f, 2.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    
    _arpSliderParams.push_back({ViatorParameters::arpSpeedID, ViatorParameters::arpSpeedName, 0.0f, 1.0f, 0.5f, skew::kNoSkew, 0.0, type::kFloat});
    _arpSliderParams.push_back({ViatorParameters::arpDirID, ViatorParameters::arpDirName, 0.0f, 2.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _arpSliderParams.push_back({ViatorParameters::arpOctaveID, ViatorParameters::arpOctaveName, 0.0f, 2.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
}

void ViatorParameters::Params::initButtonParams()
{
    _buttonParams.push_back({ViatorParameters::filterPowerID, ViatorParameters::filterPowerName, false});
    _buttonParams.push_back({ViatorParameters::crusherPowerID, ViatorParameters::crusherPowerName, false});
    _buttonParams.push_back({ViatorParameters::verbPowerID, ViatorParameters::verbPowerName, false});
    _buttonParams.push_back({ViatorParameters::arpPowerID, ViatorParameters::arpPowerName, false});
}

void ViatorParameters::Params::initMenuParams()
{
    juce::StringArray choices = {"Sine", "Square", "Saw"};
    juce::StringArray ladderChoices = {"LP12", "HP12", "BP12", "LP24", "HP24", "BP24"};
    _menuParams.push_back({ViatorParameters::osc1ChoiceID, ViatorParameters::osc1ChoiceName, choices, 0});
    _menuParams.push_back({ViatorParameters::osc2ChoiceID, ViatorParameters::osc2ChoiceName, choices, 0});
    _menuParams.push_back({ViatorParameters::amOscChoiceID, ViatorParameters::amOscChoiceName, choices, 0});
    _menuParams.push_back({ViatorParameters::ladderChoiceID, ViatorParameters::ladderChoiceName, ladderChoices, 0});
}
