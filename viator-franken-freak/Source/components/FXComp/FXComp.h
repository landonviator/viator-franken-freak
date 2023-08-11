#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class FXComp  : public juce::Component
{
public:
    FXComp(ViatorfrankenfreakAudioProcessor&);
    ~FXComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    juce::OwnedArray<viator_gui::ImageFader> _crusherSliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _crusherSliderAttachments;
    void setCrusherSliderProps();
    
    juce::OwnedArray<viator_gui::ImageFader> _reverbSliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _reverbSliderAttachments;
    void setReverbSliderProps();
    
    juce::OwnedArray<viator_gui::ImageButton> _powerButtons;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::ButtonAttachment> _powerButtonAttachments;
    void setPowerButtonProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXComp)
};
