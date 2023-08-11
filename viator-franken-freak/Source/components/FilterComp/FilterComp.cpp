#include <JuceHeader.h>
#include "FilterComp.h"

FilterComp::FilterComp(ViatorfrankenfreakAudioProcessor& p) : audioProcessor(p)
{
    setMenuProps();
    setSliderProps();
}

FilterComp::~FilterComp()
{
}

void FilterComp::paint (juce::Graphics& g)
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

void FilterComp::resized()
{
    const auto menuX = getWidth() * 0.05;
    const auto menuY = getHeight() * 0.1;
    const auto menuWidth = getWidth() * 0.3;
    const auto menuHeight = getHeight() * 0.1;
    _filterMenu.setBounds(menuX, menuY, menuWidth, menuHeight);
    
    auto sliderX = getWidth() * 0.06;
    const auto sliderY = getHeight() * 0.29;
    const auto sliderSize = getWidth() * 0.29;
    for (auto& dial : _sliders)
    {
        dial->setBounds(sliderX, sliderY, sliderSize, sliderSize);
        sliderX += sliderSize;
    }
}

void FilterComp::setMenuProps()
{
    auto params = audioProcessor._parameterMap;
    
    addAndMakeVisible(_filterMenu);
    _filterMenu.setTextWhenNothingSelected("Filter Type");
    _filterMenu.setMenuShouldHover(false);
    _filterMenu.addItemList(params.getMenuParams()[3].choices, 1);
    _menuAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor._treeState, params.getMenuParams()[3].paramID, _filterMenu);
}

void FilterComp::setSliderProps()
{
    auto params = audioProcessor._parameterMap.getLadderSliderParams();
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
