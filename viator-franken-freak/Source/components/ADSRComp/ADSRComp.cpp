#include <JuceHeader.h>
#include "ADSRComp.h"

ADSRComp::ADSRComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setSliderProps();
}

ADSRComp::~ADSRComp()
{
}

void ADSRComp::paint (juce::Graphics& g)
{
    g.setColour(_offWhite);
    g.drawRect(getLocalBounds());
}

void ADSRComp::resized()
{
    auto sliderX = getWidth() * 0.1;
    const auto sliderY = getHeight() * 0.05;
    const auto sliderWidth = getWidth() * 0.2;
    const auto sliderHeight = getHeight() * 0.9;
    for (auto& slider : _adsrSliders)
    {
        slider->setBounds(sliderX, sliderY, sliderWidth, sliderHeight);
        sliderX += sliderWidth;
    }
    
}

void ADSRComp::setSliderProps()
{
    auto params = audioProcessor._parameterMap.getADSRSliderParams();
    auto image = juce::ImageCache::getFromMemory(BinaryData::slider_vertical_png, BinaryData::slider_vertical_pngSize);
    
    for (int i = 0; i < params.size(); ++i)
    {
        _adsrSliders.add(std::make_unique<viator_gui::ImageFader>());
        _adsrSliders[i]->setFaderImageAndNumFrames(image, 129);
        _adsrSliders[i]->setSliderStyle(juce::Slider::LinearVertical);
        _adsrSliders[i]->setName(params[i].paramName);
        addAndMakeVisible(*_adsrSliders[i]);
        _attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params[i].paramID, *_adsrSliders[i]));
    }
}
