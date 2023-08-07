#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "components/Header.h"

class ViatorfrankenfreakAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ViatorfrankenfreakAudioProcessorEditor (ViatorfrankenfreakAudioProcessor&);
    ~ViatorfrankenfreakAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    // header
    Header _headerComp;
    
    // placement rects
    juce::Rectangle<int> _osc1Area;
    juce::Rectangle<int> _osc2Area;
    juce::Rectangle<int> _effectsArea;
    juce::Rectangle<int> _arpArea;
    juce::Rectangle<int> _adsrArea;
    juce::Rectangle<int> _modArea;
    juce::Rectangle<int> _filterArea;
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorfrankenfreakAudioProcessorEditor)
};
