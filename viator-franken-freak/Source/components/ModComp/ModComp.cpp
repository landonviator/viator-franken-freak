#include <JuceHeader.h>
#include "ModComp.h"

ModComp::ModComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setSliderProps();
    setPowerButtonProps();
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
    const auto sliderY = getHeight() * 0.37;
    const auto sliderSize = getWidth() * 0.23;
    for (auto& dial : _sliders)
    {
        dial->setBounds(sliderX, sliderY, sliderSize, sliderSize);
        sliderX += sliderSize;
    }
    
    // buttons
    const auto btnSize = _editorWidth * 0.035;
    const auto btnX = getWidth() - btnSize;
    const auto btnY = 0;
    for (auto& btn : _powerButtons)
    {
        btn->setBounds(btnX, btnY, btnSize, btnSize);
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

void ModComp::setPowerButtonProps()
{
    auto btnImageOff = juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize);
    auto btnImageOn = juce::ImageCache::getFromMemory(BinaryData::led_on_png, BinaryData::led_on_pngSize);
    _powerButtons.add(std::make_unique<viator_gui::ImageButton>(btnImageOff, btnImageOn, "", ""));
    _powerButtonAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, ViatorParameters::modPowerID, _powerButtons[0]->getButton()));
    addAndMakeVisible(*_powerButtons[0]);
}
