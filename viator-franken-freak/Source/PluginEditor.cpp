#include "PluginProcessor.h"
#include "PluginEditor.h"

ViatorfrankenfreakAudioProcessorEditor::ViatorfrankenfreakAudioProcessorEditor (ViatorfrankenfreakAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, _osc1Comp(audioProcessor)
, _osc2Comp(audioProcessor)
{
    // header
    addAndMakeVisible(_headerComp);
    
    // osc 1
    addAndMakeVisible(_osc1Comp);
    
    // osc 2
    addAndMakeVisible(_osc2Comp);
    
    // window
    viator_utils::PluginWindow::setPluginWindowSize(0, 0, *this, 1.5, 1.0);
}

ViatorfrankenfreakAudioProcessorEditor::~ViatorfrankenfreakAudioProcessorEditor()
{
}

//==============================================================================
void ViatorfrankenfreakAudioProcessorEditor::paint (juce::Graphics& g)
{
    // bg color
    g.fillAll (juce::Colours::black);
    
    // image bg
    auto bgImage = juce::ImageCache::getFromMemory(BinaryData::back_a_png, BinaryData::back_a_pngSize);
    auto bgWidth = getWidth() * 0.9;
    auto bgHeight = getHeight() * 0.82;
    auto bgY = getHeight() * 0.13;
    g.drawImage(bgImage, getLocalBounds().toFloat().withSizeKeepingCentre(bgWidth, bgHeight).withY(bgY));
}

void ViatorfrankenfreakAudioProcessorEditor::resized()
{
    // header
    const auto headerHeightMult = 0.1;
    const auto headerHeight = getHeight() * headerHeightMult;
    _headerComp.setBounds(0, 0, getWidth(), headerHeight);
    
    // osc 1
    const auto osc1AreaX = getWidth() * 0.1;
    const auto osc1AreaY = getHeight() * 0.16;
    const auto osc1AreaWidth = getWidth() * 0.25;
    const auto osc1AreaHeight = getHeight() * 0.2;
    _osc1Area.setBounds(osc1AreaX, osc1AreaY, osc1AreaWidth, osc1AreaHeight);
    _osc1Comp.setBounds(osc1AreaX, osc1AreaY, osc1AreaWidth, osc1AreaHeight);
    
    // osc 2
    const auto osc2YMult = 0.125;
    const auto osc2AreaY = _osc1Area.getBottom() + osc1AreaHeight * osc2YMult;
    _osc2Area.setBounds(osc1AreaX, osc2AreaY, osc1AreaWidth, osc1AreaHeight);
    _osc2Comp.setBounds(osc1AreaX, osc2AreaY, osc1AreaWidth, osc1AreaHeight);
    
    // fx
    const auto effectsY = _osc2Area.getBottom() + osc1AreaHeight * osc2YMult;
    const auto effectsWidthMult = 1.57;
    const auto effectsHeightMult = 1.6;
    _effectsArea.setBounds(osc1AreaX, effectsY, osc1AreaWidth * effectsWidthMult, osc1AreaHeight * effectsHeightMult);
    
    // arp
    const auto arpXMult = 0.05;
    const auto arpX = _effectsArea.getRight() + _effectsArea.getWidth() * arpXMult;
    _arpArea.setBounds(arpX, effectsY, _effectsArea.getWidth(), osc1AreaHeight * effectsHeightMult);
    
    // adsr
    const auto adsrWidthMult = 0.075;
    const auto adsrHeightMult = 2.12;
    const auto adsrX = _osc1Area.getRight() + _osc1Area.getWidth() * adsrWidthMult;
    _adsrArea.setBounds(adsrX, osc1AreaY, osc1AreaWidth, osc1AreaHeight * adsrHeightMult);
    
    // mod
    const auto modX = _adsrArea.getRight() + _osc1Area.getWidth() * adsrWidthMult;
    const auto filterWidthMult = 1.06;
    _modArea.setBounds(modX, osc1AreaY, osc1AreaWidth * filterWidthMult, osc1AreaHeight);
    _filterArea.setBounds(modX, osc2AreaY, osc1AreaWidth * filterWidthMult, osc1AreaHeight);
}
