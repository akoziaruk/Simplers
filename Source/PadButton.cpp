//
//  PadButton.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 12/1/21.
//

#include "PadButton.hpp"

PadButton::PadButton() : Button("") {}

PadButton::~PadButton() {}

void PadButton::paintButton (Graphics& g, bool, bool) {
    auto cornerSize = 6.0f;

    Colour buttonColour = getToggleState() ? Colour (73, 109, 219) : Colour (113, 126, 195);
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    g.setColour (buttonColour);
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
}

void PadButton::buttonStateChanged()
{
    ButtonState state = getState();
    if (state == ButtonState::buttonDown)
        setToggleState (true, NotificationType::dontSendNotification);
    else if (state == ButtonState::buttonNormal)
        setToggleState (false, NotificationType::dontSendNotification);
}

void PadButton::colourChanged() {
    repaint();
}
