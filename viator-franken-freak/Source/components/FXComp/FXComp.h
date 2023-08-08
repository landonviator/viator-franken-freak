/*
  ==============================================================================

    FXComp.h
    Created: 7 Aug 2023 9:11:11pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FXComp  : public juce::Component
{
public:
    FXComp();
    ~FXComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXComp)
};
