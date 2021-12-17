/*
  ==============================================================================

    SequencerButton.cpp
    Created: 17 Dec 2021 11:48:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerButton.h"

SequencerButton::SequencerButton() : Button(""){ }
SequencerButton::~SequencerButton() {}

void SequencerButton::paintButton (Graphics& g, bool, bool) {
    auto cornerSize = 6.0f;

    Colour buttonColour = getToggleState() ? Colour (73, 109, 219) : Colour (113, 126, 195);
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    g.setColour (buttonColour);
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
}

void SequencerButton::buttonStateChanged()
{
//    ButtonState state = getState();
//    if (state == ButtonState::buttonDown)
//        setToggleState (true, NotificationType::dontSendNotification);
//    else if (state == ButtonState::buttonNormal)
//        setToggleState (false, NotificationType::dontSendNotification);
}

void SequencerButton::colourChanged() {
    repaint();
}
