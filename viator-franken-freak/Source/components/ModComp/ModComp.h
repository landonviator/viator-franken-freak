#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class ModComp  : public juce::Component
{
public:
    ModComp(ViatorfrankenfreakAudioProcessor&);
    ~ModComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setEditorWidth(float newWidth){_editorWidth = newWidth;};

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    juce::OwnedArray<viator_gui::ImageFader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachments;
    void setSliderProps();
    
    juce::OwnedArray<viator_gui::ImageButton> _powerButtons;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::ButtonAttachment> _powerButtonAttachments;
    void setPowerButtonProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    float _editorWidth = 0.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModComp)
};
