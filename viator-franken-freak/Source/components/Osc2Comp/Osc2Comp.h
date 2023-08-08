/*
  ==============================================================================

    Osc2Comp.h
    Created: 7 Aug 2023 9:11:43pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Osc2Comp  : public juce::Component
{
public:
    Osc2Comp();
    ~Osc2Comp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc2Comp)
};
