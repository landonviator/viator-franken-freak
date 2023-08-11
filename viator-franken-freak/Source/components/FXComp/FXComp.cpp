#include <JuceHeader.h>
#include "FXComp.h"

FXComp::FXComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setCrusherSliderProps();
    setReverbSliderProps();
    setPowerButtonProps();
}

FXComp::~FXComp()
{
}

void FXComp::paint (juce::Graphics& g)
{
    g.setColour(_offWhite);
    g.drawRect(getLocalBounds());
}

void FXComp::resized()
{
    // crusher
    auto sliderX = getWidth() * 0.06;
    auto sliderY = getHeight() * 0.1;
    const auto sliderSize = getWidth() * 0.2;
    for (auto& dial : _crusherSliders)
    {
        dial->setBounds(sliderX, sliderY, sliderSize, sliderSize);
        sliderX += sliderSize;
    }
    
    // reset for next pass
    sliderX = getWidth() * 0.06;
    sliderY += sliderSize * 1.16;
    
    // reverb
    for (auto& dial : _reverbSliders)
    {
        dial->setBounds(sliderX, sliderY, sliderSize, sliderSize);
        sliderX += sliderSize;
    }
    
    // buttons
    const auto btnX = getWidth() * 0.87;
    auto btnY = getHeight() * 0.17;
    const auto btnSize = getWidth() * 0.1;
    for (auto& btn : _powerButtons)
    {
        btn->setBounds(btnX, btnY, btnSize, btnSize);
        btnY += btnSize * 2.38;
    }
}

void FXComp::setCrusherSliderProps()
{
    auto params = audioProcessor._parameterMap.getCrusherSliderParams();
    auto dialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
    
    for (int i = 0; i < params.size(); i++)
    {
        _crusherSliders.add(std::make_unique<viator_gui::ImageFader>());
        _crusherSliders[i]->setName(params[i].paramName);
        _crusherSliderAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params[i].paramID, *_crusherSliders[i]));
        _crusherSliders[i]->setFaderImageAndNumFrames(dialImage, 128);
        _crusherSliders[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        
        if (params[i].isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            _crusherSliders[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        addAndMakeVisible(*_crusherSliders[i]);
    }
}

void FXComp::setReverbSliderProps()
{
    auto params = audioProcessor._parameterMap.getReverbSliderParams();
    auto dialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
    
    for (int i = 0; i < params.size(); i++)
    {
        _reverbSliders.add(std::make_unique<viator_gui::ImageFader>());
        _reverbSliders[i]->setName(params[i].paramName);
        _reverbSliderAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params[i].paramID, *_reverbSliders[i]));
        _reverbSliders[i]->setFaderImageAndNumFrames(dialImage, 128);
        _reverbSliders[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        
        if (params[i].isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            _reverbSliders[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        addAndMakeVisible(*_reverbSliders[i]);
    }
}

void FXComp::setPowerButtonProps()
{
    auto btnImageOff = juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize);
    auto btnImageOn = juce::ImageCache::getFromMemory(BinaryData::led_on_png, BinaryData::led_on_pngSize);
    _powerButtons.add(std::make_unique<viator_gui::ImageButton>(btnImageOff, btnImageOn, "", ""));
    _powerButtons.add(std::make_unique<viator_gui::ImageButton>(btnImageOff, btnImageOn, "", ""));
    _powerButtonAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, ViatorParameters::crusherPowerID, _powerButtons[0]->getButton()));
    _powerButtonAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, ViatorParameters::verbPowerID, _powerButtons[1]->getButton()));
    addAndMakeVisible(*_powerButtons[0]);
    addAndMakeVisible(*_powerButtons[1]);
}
