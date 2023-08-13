#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class ArpComp  : public juce::Component
{
public:
    ArpComp(ViatorfrankenfreakAudioProcessor&);
    ~ArpComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    juce::OwnedArray<viator_gui::ImageFader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    void setSliderProps();
    
    juce::OwnedArray<viator_gui::ImageButton> _powerButtons;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::ButtonAttachment> _powerButtonAttachments;
    void setPowerButtonProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpComp)
};
