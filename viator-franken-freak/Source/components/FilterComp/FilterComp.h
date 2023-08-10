#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class FilterComp  : public juce::Component
{
public:
    FilterComp(ViatorfrankenfreakAudioProcessor&);
    ~FilterComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    viator_gui::Menu _filterMenu;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> _menuAttach;
    void setMenuProps();
    
    juce::OwnedArray<viator_gui::ImageFader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachments;
    void setSliderProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComp)
};
