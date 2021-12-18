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
    
    SequencerComponent(SequencerEngine&);
    ~SequencerComponent();
    void resized() override;
    void paint (juce::Graphics& g) override;
    void buttonClicked (Button* button) override;
    void update() override;
    
private:
    
    void updatePlayStopButton();
    
    SequencerEngine& engine;
    Array<SequencerButton*> buttons;

    Component positionSlider;
    TextButton playStopButton;
    
    int margin = 8;
    int padding = 2;
    int buttonSide = 0;
    int buttonStartX = 0;
};
