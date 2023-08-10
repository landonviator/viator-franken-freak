#include <JuceHeader.h>
#include "ModComp.h"

ModComp::ModComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setSliderProps();
}

ModComp::~ModComp()
{
}

void ModComp::paint (juce::Graphics& g)
{
    g.setColour(_offWhite);
    g.drawRect(getLocalBounds());
}

void ModComp::resized()
{
    auto sliderX = getWidth() * 0.04;
    const auto sliderY = getHeight() * 0.22;
    const auto sliderSize = getWidth() * 0.23;
    for (auto& dial : _sliders)
    {
        dial->setBounds(sliderX, sliderY, sliderSize, sliderSize);
        sliderX += sliderSize;
    }
}

void ModComp::setSliderProps()
{
    auto params = audioProcessor._parameterMap.getModSliderParams();
    auto dialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_03_png, BinaryData::Knob_03_pngSize);
    
    for (int i = 0; i < params.size(); i++)
    {
        _sliders.add(std::make_unique<viator_gui::ImageFader>());
        _sliders[i]->setName(params[i].paramName);
        _sliderAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params[i].paramID, *_sliders[i]));
        _sliders[i]->setFaderImageAndNumFrames(dialImage, 128);
        _sliders[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        
        if (params[i].isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            _sliders[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        addAndMakeVisible(*_sliders[i]);
    }
}
