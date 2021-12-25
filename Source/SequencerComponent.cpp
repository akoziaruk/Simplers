/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 16 Dec 2021 2:53:11pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerComponent.hpp"

SequencerComponent::SequencerComponent(SequencerEngine& e, int rows, int items): engine(e),
                                                                                 numberOfRows(rows),
                                                                                 numberOfItems(items)
{
    setFramesPerSecond(60);
    
    // setup BMP label
    bpmLabel.setEditable(true);
    bpmLabel.setText(String(engine.getBMP()), juce::dontSendNotification);
    bpmLabel.onTextChange = [this] { engine.setBMP(bpmLabel.getText().getIntValue()); };
    bpmLabel.setJustificationType(Justification::centred);
    bpmLabel.setColour (juce::Label::backgroundColourId, juce::Colours::darkgrey);
    bpmLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    bpmLabel.setKeyboardType(TextInputTarget::VirtualKeyboardType::numericKeyboard);
    addAndMakeVisible(bpmLabel);
    
    //setup Play/Stop button
    addAndMakeVisible(playStopButton);
    playStopButton.addListener(this);
    updatePlayStopButton();
    
    // add Sequencer buttons
    for (int i = 0; i < numberOfRows*numberOfItems; i++)
    {
        SequencerButton* button = new SequencerButton(selectedColour,
                                                      colorForDeselectedItem(i));
        button->setComponentID(String(i));
        button->addListener(this);
        addAndMakeVisible(button);
        
        buttons.add(button);
    }
}

Colour SequencerComponent::colorForDeselectedItem(int index)
{
    int k = index%8;
    bool first = k==0||k==1||k==2||k==3;
    return first ? deselectedColour1 : deselectedColour2;;
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
        int position = index % numberOfItems;
        int sampleIndex = floor(index / numberOfItems);
        
        bool state = engine.toggle(sampleIndex, position);
        button->setToggleState(state, NotificationType::dontSendNotification);
    }
}

void SequencerComponent::resized()
{
    playStopButton.setBounds(10, 10, 50, 30);
    bpmLabel.setBounds(10, 50, 50, 30);

    // resize buttons
    buttonSide = (getHeight()-margin*2)/numberOfRows-padding;
    buttonStartX = (getWidth()-numberOfItems*(buttonSide+padding))/2;
    
    int index = 0;
    
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfItems; j++)
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
