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
    
    _sliderParams.push_back({ViatorParameters::osc2TimbreID, ViatorParameters::osc2TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::osc2TuneID, ViatorParameters::osc2TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::osc2GainID, ViatorParameters::osc2GainName, -30.0f, 30.0f, -0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _osc2SliderParams.push_back({ViatorParameters::osc2GainID, ViatorParameters::osc2GainName, -30.0f, 30.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc2SliderParams.push_back({ViatorParameters::osc2TimbreID, ViatorParameters::osc2TimbreName, 0.0f, 10.0f, 5.0f, skew::kNoSkew, 0.0, type::kFloat});
    _osc2SliderParams.push_back({ViatorParameters::osc2TuneID, ViatorParameters::osc2TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    
    _sliderParams.push_back({ViatorParameters::attackID, ViatorParameters::attackName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::decayID, ViatorParameters::decayName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::sustainID, ViatorParameters::sustainName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::releaseID, ViatorParameters::releaseName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    _adsrSliderParams.push_back({ViatorParameters::attackID, ViatorParameters::attackName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::decayID, ViatorParameters::decayName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::sustainID, ViatorParameters::sustainName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _adsrSliderParams.push_back({ViatorParameters::releaseID, ViatorParameters::releaseName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
}

void ViatorParameters::Params::initButtonParams()
{
}

void ViatorParameters::Params::initMenuParams()
{
    juce::StringArray choices = {"Sine", "Square", "Saw"};
    _menuParams.push_back({ViatorParameters::osc1ChoiceID, ViatorParameters::osc1ChoiceName, choices, 0});
    _menuParams.push_back({ViatorParameters::osc2ChoiceID, ViatorParameters::osc2ChoiceName, choices, 0});
}
