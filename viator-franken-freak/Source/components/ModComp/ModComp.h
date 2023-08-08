/*
  ==============================================================================

    ModComp.h
    Created: 7 Aug 2023 9:11:20pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModComp  : public juce::Component
{
public:
    ModComp();
    ~ModComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModComp)
};
