/*
  ==============================================================================

    SequencerButton.cpp
    Created: 17 Dec 2021 11:48:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerButton.hpp"

SequencerButton::SequencerButton(Colour s, Colour d): Button(""), m_SelectedColor(s), m_DeselectedColor(d) {}
SequencerButton::~SequencerButton() {}

void SequencerButton::paintButton (Graphics& g, bool, bool) {
    auto cornerSize = 6.0f;

    Colour buttonColour = getToggleState() ? m_SelectedColor: m_DeselectedColor;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    g.setColour (buttonColour);
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
}

void SequencerButton::buttonStateChanged(){}

void SequencerButton::colourChanged() {
    repaint();
}
