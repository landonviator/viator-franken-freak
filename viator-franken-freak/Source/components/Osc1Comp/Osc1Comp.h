/*
  ==============================================================================

    Osc1Comp.h
    Created: 7 Aug 2023 9:11:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Osc1Comp  : public juce::Component
{
public:
    Osc1Comp();
    ~Osc1Comp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc1Comp)
};
