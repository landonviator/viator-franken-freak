#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class Osc2Comp  : public juce::Component
{
public:
    Osc2Comp(ViatorfrankenfreakAudioProcessor&);
    ~Osc2Comp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    viator_gui::Menu _oscMenu;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> _menuAttach;
    void setMenuProps();
    
    juce::OwnedArray<viator_gui::ImageFader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachments;
    void setSliderProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc2Comp)
};
