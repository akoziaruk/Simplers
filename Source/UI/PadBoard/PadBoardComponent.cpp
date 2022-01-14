//
//  MidiPadBoardComponent.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/27/21.
//

#include "PadBoardComponent.hpp"

#define MIDI_CHANEL 1
#define VELOCITY 1

PadBoardComponent::PadBoardComponent(MidiKeyboardState& s): m_State(s)
{
    // add pads
    for (int i = 0; i < 3*3; i++) {
        PadButton* pad = new PadButton();
        pad->setComponentID(String(i));
        pad->addListener(this);
        m_Pads.add(pad);
        addAndMakeVisible (pad);
    }
}

PadBoardComponent::~PadBoardComponent()
{
    for (int i = m_Pads.size()-1; i > 0 ; i--) {
        PadButton* button = m_Pads[i];
        button->removeListener(this);
        m_Pads.remove(i);
        
        delete button;
    }
}

void PadBoardComponent::buttonStateChanged(Button* button)
{
    // handle buttons action
    String id = button->getComponentID();
    int index = id.getIntValue();
    PadButton::ButtonState buttonState = button->getState();

    if (buttonState == PadButton::ButtonState::buttonDown)
        m_State.noteOn (MIDI_CHANEL, index, VELOCITY);
    else if (buttonState == PadButton::ButtonState::buttonNormal)
        m_State.noteOff (MIDI_CHANEL, index, VELOCITY);
}

void PadBoardComponent::resized()
{
    // resize pads
    float m = 8;
    float side = (getHeight()-m)/3-m;
    int index = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float x = j*(side+m)+m; float y = i*(side+m)+m;
            m_Pads[index++]->setBounds (x,y,side,side);
        }
    }
}

void PadBoardComponent::paint (juce::Graphics& g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (77, 53, 84));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}
