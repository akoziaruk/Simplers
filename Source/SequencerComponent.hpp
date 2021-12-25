/*
  ==============================================================================

    SequencerComponent.h
    Created: 16 Dec 2021 2:53:11pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SequencerEngine.hpp"
#include "SequencerButton.h"

using namespace juce;

class SequencerComponent  : public AnimatedAppComponent,
                            public Button::Listener
{
public:
    
    SequencerComponent(SequencerEngine&, int rows, int items);
    ~SequencerComponent();
    void resized() override;
    void paint (juce::Graphics& g) override;
    void buttonClicked (Button* button) override;
    void update() override;
    
private:
    
    void updatePlayStopButton();
    Colour colorForDeselectedItem(int index);
    
    SequencerEngine& engine;
    Array<SequencerButton*> buttons;

    TextButton playStopButton;
    Label bpmLabel;
    
    int numberOfRows;
    int numberOfItems;
    
    int margin = 8;
    int padding = 2;
    int buttonSide = 0;
    int buttonStartX = 0;
    
    Colour selectedColour = Colour(73, 109, 219);
    Colour deselectedColour1 = Colour(113, 126, 195);
    Colour deselectedColour2 = Colour(108, 118, 188);
};
