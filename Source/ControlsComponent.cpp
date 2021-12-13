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
    reverbControls.setListener(this);
    addAndMakeVisible (reverbControls);
}

ControlsComponent::~ControlsComponent()
{
    reverbControls.removeListener(this);
}

void ControlsComponent::resized()
{
    reverbControls.setBounds(8, 8, getWidth() - 16, 100);
}

void ControlsComponent::paint(Graphics &g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (166, 99, 204));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}

void ControlsComponent::handleValueChanged(ControlsRowComponent *source, int index, float value)
{
    if (source == &reverbControls) {
        // effect for index
        // state reverb set parameters

    }
}
