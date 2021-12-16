//
//  MidiPadBoardComponent.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/27/21.
//

#include "PadBoardComponent.hpp"

PadBoardComponent::PadBoardComponent(MidiKeyboardState& s): state(s)
{
    // add pads
    for (int i = 0; i < 3*3; i++)
    {
        PadButton* pad = new PadButton();
        pad->setComponentID(String(i));
        pad->addListener(this);
        pads.add(pad);
        addAndMakeVisible (pad);
    }
}

PadBoardComponent::~PadBoardComponent()
{
    for (int i = 0; i < pads.size(); i++) {
        pads[i]->removeListener (this);
    }
}

void PadBoardComponent::buttonStateChanged(Button* button)
{
    // handle buttons action
    String id = button->getComponentID();
    int index = id.getIntValue();
    PadButton::ButtonState buttonState = button->getState();

    if (buttonState == PadButton::ButtonState::buttonDown)
        state.noteOn (midiChannel, index, velocity);
    else if (buttonState == PadButton::ButtonState::buttonNormal)
        state.noteOff (midiChannel, index, velocity);
}

void PadBoardComponent::resized()
{
    // resize pads
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float m = 8;
            float side = (getWidth()-m)/3-m;
            float x = j*(side+m)+m; float y = i*(side+m)+m;
            pads[index++]->setBounds (x,y,side,side);
        }
    }
}

void PadBoardComponent::paint (juce::Graphics& g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (201, 93, 99));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}
