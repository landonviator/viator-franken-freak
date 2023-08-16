#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class Osc1Comp  : public juce::Component
{
public:
    Osc1Comp(ViatorfrankenfreakAudioProcessor&);
    ~Osc1Comp() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setEditorWidth(float newWidth){_editorWidth = newWidth;};

private:
    ViatorfrankenfreakAudioProcessor& audioProcessor;
    
    viator_gui::Menu _oscMenu;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> _menuAttach;
    void setMenuProps();
    
    juce::OwnedArray<viator_gui::ImageFader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _sliderAttachments;
    void setSliderProps();
    
    juce::OwnedArray<viator_gui::ImageButton> _powerButtons;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::ButtonAttachment> _powerButtonAttachments;
    void setPowerButtonProps();
    
    juce::Colour _offWhite = juce::Colours::whitesmoke.withAlpha(0.5f);
    float _editorWidth = 0.0f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc1Comp)
};
