#include <JuceHeader.h>
#include "ArpComp.h"

ArpComp::ArpComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setSliderProps();
    setPowerButtonProps();
}

ArpComp::~ArpComp()
{
}

void ArpComp::paint (juce::Graphics& g)
{
    g.setColour(_offWhite);
    g.drawRect(getLocalBounds());
}

void ArpComp::resized()
{
    auto sliderX = getWidth() * 0.06;
    const auto sliderY = getHeight() * 0.29;
    const auto sliderSize = getWidth() * 0.29;
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

void ArpComp::setSliderProps()
{
    auto params = audioProcessor._parameterMap.getArpSliderParams();
    auto image = juce::ImageCache::getFromMemory(BinaryData::Knob_03_png, BinaryData::Knob_03_pngSize);
    
    for (int i = 0; i < params.size(); ++i)
    {
        _sliders.add(std::make_unique<viator_gui::ImageFader>());
        _sliders[i]->setFaderImageAndNumFrames(image, 129);
        _sliders[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        _sliders[i]->setName(params[i].paramName);
        addAndMakeVisible(*_sliders[i]);
        _attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params[i].paramID, *_sliders[i]));
    }
}

void ArpComp::setPowerButtonProps()
{
    auto btnImageOff = juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize);
    auto btnImageOn = juce::ImageCache::getFromMemory(BinaryData::led_on_png, BinaryData::led_on_pngSize);
    _powerButtons.add(std::make_unique<viator_gui::ImageButton>(btnImageOff, btnImageOn, "", ""));
    _powerButtonAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, ViatorParameters::arpPowerID, _powerButtons[0]->getButton()));
    addAndMakeVisible(*_powerButtons[0]);
}
