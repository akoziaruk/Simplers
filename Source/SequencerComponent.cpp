/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 16 Dec 2021 2:53:11pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerComponent.hpp"

#define MARGIN 8
#define PADDING 2

#define SELECTED_COLOUR Colour(73, 109, 219)
#define DESELECTED_COLOUR_1 Colour(113, 126, 195)
#define DESELECTED_COLOUR_2 Colour(108, 118, 188)

SequencerComponent::SequencerComponent(SequencerEngine& e, int rows, int items): m_Engine(e),
                                                                                 m_NumberOfRows(rows),
                                                                                 m_NumberOfItems(items)
{
    setFramesPerSecond(60);
    
    // setup BMP label
    m_BPMLabel.setEditable(true);
    m_BPMLabel.setText(String(m_Engine.getBMP()), juce::dontSendNotification);
    m_BPMLabel.onTextChange = [this] { m_Engine.setBMP(m_BPMLabel.getText().getIntValue()); };
    m_BPMLabel.setJustificationType(Justification::centred);
    m_BPMLabel.setColour (juce::Label::backgroundColourId, juce::Colours::darkgrey);
    m_BPMLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    m_BPMLabel.setKeyboardType(TextInputTarget::VirtualKeyboardType::numericKeyboard);
    addAndMakeVisible(m_BPMLabel);
    
    //setup Play/Stop button
    addAndMakeVisible(m_PlayStopButton);
    m_PlayStopButton.addListener(this);
    updatePlayStopButton();
    
    // add Sequencer buttons
    for (int i = 0; i < m_NumberOfRows*m_NumberOfItems; i++) {
        SequencerButton* button = new SequencerButton(SELECTED_COLOUR,
                                                      colorForDeselectedItem(i));
        button->setComponentID(String(i));
        button->addListener(this);
        addAndMakeVisible(button);
        
        m_Buttons.add(button);
    }
}

Colour SequencerComponent::colorForDeselectedItem(int index)
{
    int m = index%8;
    bool first = m==0||m==1||m==2||m==3;
    return first ? DESELECTED_COLOUR_1 : DESELECTED_COLOUR_2;;
}

SequencerComponent::~SequencerComponent()
{
    m_PlayStopButton.removeListener(this);
    
    for (int i = 0; i < m_Buttons.size(); i++)
        m_Buttons[i]->removeListener(this);
}

void SequencerComponent::buttonClicked(Button* button)
{
    if (button == &m_PlayStopButton) {
        m_Engine.togglePlay();
        updatePlayStopButton();
    } else {
        int index = button->getComponentID().getIntValue();
        int position = index % m_NumberOfItems;
        int sampleIndex = floor(index / m_NumberOfItems);
        
        bool state = m_Engine.toggle(sampleIndex, position);
        button->setToggleState(state, NotificationType::dontSendNotification);
    }
}

void SequencerComponent::resized()
{
    m_PlayStopButton.setBounds(10, 10, 50, 30);
    m_BPMLabel.setBounds(10, 50, 50, 30);

    // resize buttons
    m_ButtonSide = (getHeight()-MARGIN*2)/m_NumberOfRows-PADDING;
    m_ButtonStartX = (getWidth()-m_NumberOfItems*(m_ButtonSide+PADDING))/2;
    
    int index = 0;
    
    for (int i = 0; i < m_NumberOfRows; i++) {
        for (int j = 0; j < m_NumberOfItems; j++) {
            float x = m_ButtonStartX+j*(m_ButtonSide+PADDING);
            float y = MARGIN+i*(m_ButtonSide+PADDING);
            m_Buttons[index++]->setBounds(x, y, m_ButtonSide, m_ButtonSide);
        }
    }
}

void SequencerComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(Colour (201, 93, 99));
    g.fillRect(bounds);
    
    g.setColour(Colour(52, 73, 102));
         
    int x = m_ButtonStartX + (m_ButtonSide + PADDING) * m_Engine.getPosition();
    g.fillRect(x, getHeight()-8, m_ButtonSide, 6);
}

void SequencerComponent::updatePlayStopButton()
{
    m_PlayStopButton.setButtonText(m_Engine.isPlaying() ? "Stop" : "Play");
}

void SequencerComponent::update()
{
    
}
