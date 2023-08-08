/*
  ==============================================================================

    Osc1Comp.cpp
    Created: 7 Aug 2023 9:11:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Osc1Comp.h"

//==============================================================================
Osc1Comp::Osc1Comp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Osc1Comp::~Osc1Comp()
{
}

void Osc1Comp::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Osc1Comp", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Osc1Comp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
