/*
  ==============================================================================

    ADSRComp.h
    Created: 7 Aug 2023 9:10:52pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComp  : public juce::Component
{
public:
    ADSRComp();
    ~ADSRComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComp)
};
