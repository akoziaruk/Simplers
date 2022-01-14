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

SequencerComponent::SequencerComponent(SequencerEngine& e, int rows, int items): m_Engine(e),
                                                                                 m_NumberOfRows(rows),
                                                                                 m_NumberOfItems(items)
{
    setFramesPerSecond(60);
    setOpaque(false);
    
    // setup BMP label
    m_BPMLabel.setEditable(true);
    m_BPMLabel.setText(String(m_Engine.getBMP()), juce::dontSendNotification);
    m_BPMLabel.onTextChange = [this] { m_Engine.setBMP(m_BPMLabel.getText().getIntValue()); };
    m_BPMLabel.setJustificationType(Justification::centred);
    m_BPMLabel.setColour (juce::Label::backgroundColourId, Colour(123, 80, 111));
    m_BPMLabel.setColour (juce::Label::textColourId, Colour(219, 205, 198));
    m_BPMLabel.setKeyboardType(TextInputTarget::VirtualKeyboardType::numericKeyboard);
    m_BPMLabel.setLookAndFeel(&m_LookAndFeel);
    addAndMakeVisible(m_BPMLabel);
    
    // setup Play/Stop button
    addAndMakeVisible(m_PlayStopButton);
    m_PlayStopButton.addListener(this);
    updatePlayStopButton();
    
    // add Sequencer buttons
    for (int i = 0; i < m_NumberOfRows*m_NumberOfItems; i++) {
        SequencerButton* button = new SequencerButton(Colour(172, 117, 149),
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
    return first ? Colour(225, 169, 193): Colour(228, 184, 198);
}

SequencerComponent::~SequencerComponent()
{
    m_PlayStopButton.removeListener(this);
    
    for (int i = 0; i < m_Buttons.size(); i++)
        m_Buttons[i]->removeListener(this);
}

void SequencerComponent::buttonClicked(Button* button)
{
    if (button == &m_PlayStopButton)
        playButtonClicked();
    else
        sequencerButtonClicked(button);
}

void SequencerComponent::playButtonClicked()
{
    m_Engine.togglePlay();
    updatePlayStopButton();
}

void SequencerComponent::sequencerButtonClicked(Button *button)
{
    int index = button->getComponentID().getIntValue();
    int position = index % m_NumberOfItems;
    int sampleIndex = floor(index / m_NumberOfItems);
    
    bool state = m_Engine.toggle(sampleIndex, position);
    button->setToggleState(state, NotificationType::dontSendNotification);
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
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (77, 53, 84));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
    
    // draw cursor
    float x = m_ButtonStartX + (m_ButtonSide + PADDING) * m_Engine.getPosition();
    
    g.setColour(Colour(172, 117, 149));
    g.fillRoundedRectangle(Rectangle<float>(x, getHeight()-8.0, m_ButtonSide, 6.0), 2);
}

void SequencerComponent::updatePlayStopButton()
{
    m_PlayStopButton.setButtonText(m_Engine.isPlaying() ? "Stop" : "Play");
}

void SequencerComponent::update() {}
