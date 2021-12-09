/*
  ==============================================================================

    ControlsComponent.cpp
    Created: 8 Dec 2021 11:12:24am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsComponent.h"

ControlsComponent::ControlsComponent(ControlsComponentState& s): state(s)
{
    addAndMakeVisible (reverbSlider);
    reverbSlider.setRange (0, 1);
    reverbSlider.setColour(Slider::textBoxTextColourId, Colours::black);
    reverbSlider.addListener (this);
    
    addAndMakeVisible (reverbLabel);
    reverbLabel.setText ("Reverb", juce::dontSendNotification);
    reverbLabel.setColour(Label::textColourId, Colours::black);
    reverbLabel.attachToComponent (&reverbSlider, true);
    
    addAndMakeVisible (distortionSlider);
    distortionSlider.setRange (0, 1);
    distortionSlider.setColour(Slider::textBoxTextColourId, Colours::black);
    distortionSlider.addListener (this);
    
    addAndMakeVisible (distortionLabel);
    distortionLabel.setText ("Distortion", juce::dontSendNotification);
    distortionLabel.setColour(Label::textColourId, Colours::black);
    distortionLabel.attachToComponent (&distortionSlider, true);
}

ControlsComponent::~ControlsComponent(){
    reverbSlider.removeListener (this);
    distortionSlider.removeListener (this);
}

void ControlsComponent::resized()
{
    auto sliderLeft = 74;
    reverbSlider.setBounds (sliderLeft, 16, getWidth() - sliderLeft - 10, 20);
    distortionSlider.setBounds (sliderLeft, 16+20+8, getWidth() - sliderLeft - 10, 20);
}

void ControlsComponent::paint(Graphics &g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (201, 93, 99));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}

void ControlsComponent::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &reverbSlider) {
        state.setReverb (slider->getValue());
    } else if (slider == &distortionSlider) {
        state.setDistortion (slider->getValue());
    }
}
