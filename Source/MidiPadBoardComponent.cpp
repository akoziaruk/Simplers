//
//  MidiPadBoardComponent.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/27/21.
//

#include "MidiPadBoardComponent.hpp"

MidiPadBoardComponent::MidiPadBoardComponent(MidiKeyboardState& s): state(s)
{
    // add pads
    for (int i = 0; i < 3*3; i++)
    {
        TextButton* pad = new TextButton();
        pad->setComponentID(String(i));
        pad->addListener(this);
//        pad->setColour(TextButton::ColourIds::buttonOnColourId, Colour (73, 109, 219));
//        pad->setColour(TextButton::ColourIds::buttonColourId, Colour (113, 126, 195));
        pads.add(pad);
        addAndMakeVisible (pad);
    }
}

MidiPadBoardComponent::~MidiPadBoardComponent()
{
    for (int i = 0; i < pads.size(); i++) {
        pads[i]->removeListener (this);
    }
}

void MidiPadBoardComponent::buttonStateChanged(Button* button)
{
    // handle buttons action
    String id = button->getComponentID();
    int index = id.getIntValue();
    TextButton::ButtonState buttonState = button->getState();

    if (buttonState == TextButton::ButtonState::buttonDown) {
        state.noteOn (midiChannel, index, velocity);
    }
    else if (buttonState == TextButton::ButtonState::buttonNormal)
        state.noteOff (midiChannel, index, velocity);
}

void MidiPadBoardComponent::resized()
{
    // resize pads
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            float m = 8;
            float side = (getWidth()-m)/3-m;
            float x = k*(side+m)+m; float y = i*(side+m)+m;
            pads[index++]->setBounds (x,y,side,side);
        }
    }
}

void MidiPadBoardComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour (201, 93, 99));
}
