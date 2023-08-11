#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
// Param data
struct SliderParameterData
{
    enum SkewType
    {
        kSkew,
        kNoSkew
    };
    
    enum NumericType
    {
        kInt,
        kFloat
    };
    
    public:
        juce::String paramID;
        juce::String paramName;
        float min;
        float max;
        float initial;
        SkewType isSkew;
        float center;
        NumericType isInt;
};

struct ButtonParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        bool initial;
};

struct MenuParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        juce::StringArray choices;
        int defaultIndex;
};

    class Params
    {
    public:
        Params();
        
        // Get a ref to the param data
        std::vector<ViatorParameters::SliderParameterData>& getSliderParams(){return _sliderParams;};
        std::vector<ViatorParameters::ButtonParameterData>& getButtonParams(){return _buttonParams;};
        std::vector<ViatorParameters::MenuParameterData>& getMenuParams(){return _menuParams;};
        
        //
        std::vector<ViatorParameters::SliderParameterData>& getOsc1SliderParams(){return _osc1SliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getOsc2SliderParams(){return _osc2SliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getADSRSliderParams(){return _adsrSliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getModSliderParams(){return _modSliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getLadderSliderParams(){return _ladderSliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getCrusherSliderParams(){return _crusherSliderParams;};
        std::vector<ViatorParameters::SliderParameterData>& getReverbSliderParams(){return _reverbSliderParams;};
        
    private:
        // Adds params to the vector
        void initSliderParams();
        void initButtonParams();
        void initMenuParams();
        
        
    private:
        // Vector holding param data
        std::vector<ViatorParameters::SliderParameterData> _sliderParams;
        std::vector<ViatorParameters::ButtonParameterData> _buttonParams;
        std::vector<ViatorParameters::MenuParameterData> _menuParams;
        
        //
        std::vector<ViatorParameters::SliderParameterData> _osc1SliderParams;
        std::vector<ViatorParameters::SliderParameterData> _osc2SliderParams;
        std::vector<ViatorParameters::SliderParameterData> _adsrSliderParams;
        std::vector<ViatorParameters::SliderParameterData> _modSliderParams;
        std::vector<ViatorParameters::SliderParameterData> _ladderSliderParams;
        std::vector<ViatorParameters::SliderParameterData> _crusherSliderParams;
        std::vector<ViatorParameters::SliderParameterData> _reverbSliderParams;
        
    };
}
