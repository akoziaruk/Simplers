/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 16 Dec 2021 2:53:11pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerComponent.hpp"

SequencerComponent::SequencerComponent(SequencerEngine& s): engine(s)
{
    setFramesPerSecond (60);
    
    addAndMakeVisible(positionSlider);
    
    //setup Play/Stop button
    addAndMakeVisible(playStopButton);
    playStopButton.addListener(this);
    updatePlayStopButton();
    
    // add Sequencer buttons
    for (int i = 0; i < 9*16; i++)
    {
        SequencerButton* button = new SequencerButton();
        button->setComponentID(String(i));
        button->addListener(this);
        addAndMakeVisible(button);
        
        buttons.add(button);
    }
}

SequencerComponent::~SequencerComponent()
{
    playStopButton.removeListener(this);
    
    for (int i = 0; i < buttons.size(); i++)
        buttons[i]->removeListener(this);
}

void SequencerComponent::buttonClicked(Button* button)
{
    if (button == &playStopButton)
    {
        engine.togglePlay();
        updatePlayStopButton();
    }
    else
    {
        int index = button->getComponentID().getIntValue();
        int position = index % 16;
        int sampleIndex = floor(index / 16);
        
        bool state = engine.toggle(sampleIndex, position);
        button->setToggleState(state, NotificationType::dontSendNotification);
    }
}

void SequencerComponent::resized()
{
    playStopButton.setBounds(10, 10, 50, 30);
    
    // resize buttons
    buttonSide = (getHeight()-margin*2)/9-padding;
    buttonStartX = (getWidth()-16*(buttonSide+padding))/2;
    
    int index = 0;
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            float x = buttonStartX+j*(buttonSide+padding);
            float y = margin+i*(buttonSide+padding);
            buttons[index++]->setBounds(x, y, buttonSide, buttonSide);
        }
    }
}

void SequencerComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(Colour (201, 93, 99));
    g.fillRect(bounds);
    
    g.setColour(Colour(52, 73, 102));
         
    int x = buttonStartX + (buttonSide + padding) * engine.getPosition();
    g.fillRect(x, getHeight()-8, buttonSide, 6);
}

void SequencerComponent::updatePlayStopButton()
{
    playStopButton.setButtonText(engine.isPlaying() ? "Stop" : "Play");
}

void SequencerComponent::update()
{
    
}
