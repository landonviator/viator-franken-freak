#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class ADSRComp  : public juce::Component
{
public:
    ADSRComp(ViatorfrankenfreakAudioProcessor&);
    ~ADSRComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    juce::OwnedArray<viator_gui::ImageFader> _adsrSliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    void setSliderProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComp)
};
