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
    
    _sliderParams.push_back({ViatorParameters::osc1TuneID, ViatorParameters::osc1TuneName, -24.0f, 24.0f, 0.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::osc1GainID, ViatorParameters::osc1GainName, -30.0f, 30.0f, -3.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::attackID, ViatorParameters::attackName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::decayID, ViatorParameters::decayName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::sustainID, ViatorParameters::sustainName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::releaseID, ViatorParameters::releaseName, 0.0f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
}

void ViatorParameters::Params::initButtonParams()
{
}

void ViatorParameters::Params::initMenuParams()
{
    juce::StringArray choices = {"Sine", "Square", "Saw"};
    _menuParams.push_back({ViatorParameters::osc1ChoiceID, ViatorParameters::osc1ChoiceName, choices, 0});
}
