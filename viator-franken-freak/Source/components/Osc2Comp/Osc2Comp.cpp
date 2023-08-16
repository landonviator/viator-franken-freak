#include <JuceHeader.h>
#include "Osc2Comp.h"

Osc2Comp::Osc2Comp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setMenuProps();
    setSliderProps();
    setPowerButtonProps();
}

Osc2Comp::~Osc2Comp()
{
}

void Osc2Comp::paint (juce::Graphics& g)
{
    g.setColour(_offWhite);
    g.drawRect(getLocalBounds());
    
    auto menu = juce::ImageCache::getFromMemory(BinaryData::text_box_png, BinaryData::text_box_pngSize);
    const auto menuX = getWidth() * 0.05;
    const auto menuY = getHeight() * 0.1;
    const auto menuWidth = getWidth() * 0.3;
    const auto menuHeight = getHeight() * 0.1;
    g.drawImageWithin(menu, menuX, menuY, menuWidth, menuHeight, juce::RectanglePlacement::stretchToFit);
}

void Osc2Comp::resized()
{
    const auto menuX = getWidth() * 0.05;
    const auto menuY = getHeight() * 0.1;
    const auto menuWidth = getWidth() * 0.3;
    const auto menuHeight = getHeight() * 0.1;
    _oscMenu.setBounds(menuX, menuY, menuWidth, menuHeight);
    
    auto sliderX = menuX;
    const auto sliderY = menuY + menuHeight * 2.0;
    const auto sliderWidth = menuWidth;
    for (auto& dial : _sliders)
    {
        dial->setBounds(sliderX, sliderY, sliderWidth, sliderWidth);
        sliderX += sliderWidth;
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

void Osc2Comp::setSliderProps()
{
    auto params = audioProcessor._parameterMap.getOsc2SliderParams();
    auto dialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_05_png, BinaryData::Knob_05_pngSize);
    
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

void Osc2Comp::setMenuProps()
{
    auto params = audioProcessor._parameterMap;
    
    addAndMakeVisible(_oscMenu);
    _oscMenu.setTextWhenNothingSelected("Osc Shape");
    _oscMenu.setMenuShouldHover(false);
    _oscMenu.addItemList(params.getMenuParams()[0].choices, 1);
    _menuAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor._treeState, params.getMenuParams()[1].paramID, _oscMenu);
}

void Osc2Comp::setPowerButtonProps()
{
    auto btnImageOff = juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize);
    auto btnImageOn = juce::ImageCache::getFromMemory(BinaryData::led_on_png, BinaryData::led_on_pngSize);
    _powerButtons.add(std::make_unique<viator_gui::ImageButton>(btnImageOff, btnImageOn, "", ""));
    _powerButtonAttachments.add(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, ViatorParameters::osc2PowerID, _powerButtons[0]->getButton()));
    addAndMakeVisible(*_powerButtons[0]);
}
