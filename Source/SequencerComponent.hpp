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
    
    SequencerEngine& m_Engine;
    Array<SequencerButton*> m_Buttons;

    TextButton m_PlayStopButton;
    Label m_BPMLabel;
    
    int m_NumberOfRows;
    int m_NumberOfItems;
    int m_ButtonSide;
    int m_ButtonStartX;
};
