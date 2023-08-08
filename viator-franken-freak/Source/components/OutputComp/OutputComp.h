/*
  ==============================================================================

    OutputComp.h
    Created: 7 Aug 2023 9:11:53pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OutputComp  : public juce::Component
{
public:
    OutputComp();
    ~OutputComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputComp)
};
