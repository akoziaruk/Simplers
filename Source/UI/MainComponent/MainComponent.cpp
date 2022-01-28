#include "MainComponent.hpp"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    m_PadButton.setColour(TextButton::ColourIds::buttonColourId, Colour(234, 215, 209));
    m_SequencerButton.setColour(TextButton::ColourIds::buttonColourId, Colour(225, 169, 193));
    
    addAndMakeVisible (m_PadButton);
    addAndMakeVisible (m_SequencerButton);
    addAndMakeVisible (m_PadComponent);
    addAndMakeVisible (m_ControlsComponent);
    addChildComponent (m_SequencerComponent);
    
    m_PadButton.addListener(this);
    m_SequencerButton.addListener(this);
    
    m_AudioDeviceManager.initialise (0, 2, nullptr, true, {}, nullptr);

    m_AudioSourcePlayer.setSource (&m_AudioEngine);
    m_AudioDeviceManager.addAudioCallback (&m_AudioSourcePlayer);
}

MainComponent::~MainComponent()
{
    m_PadButton.removeListener(this);
    m_SequencerButton.removeListener(this);

    m_AudioSourcePlayer.setSource (nullptr);
    m_AudioDeviceManager.removeAudioCallback (&m_AudioSourcePlayer);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour (31, 26, 56));
}

void MainComponent::resized()
{
    int margin = 16;
    int width = getWidth() * 0.45;
    int height = getHeight() - margin*2;
    
    m_PadComponent.setBounds(margin*2, margin, height, height);
    m_ControlsComponent.setBounds(width + margin*2, margin, width, height);
    m_SequencerComponent.setBounds(margin*2, margin, getWidth()*0.9, height);
    
    int buttonSide = 30;
    int x = getWidth()-buttonSide-16;
    
    m_PadButton.setBounds(x, 20, buttonSide, buttonSide);
    m_SequencerButton.setBounds(x, 20+buttonSide+4, buttonSide, buttonSide);
}

void MainComponent::buttonClicked(Button *button)
{
    bool showPad = (button == &m_PadButton);
    
    m_PadComponent.setVisible(showPad);
    m_ControlsComponent.setVisible(showPad);
    m_SequencerComponent.setVisible(!showPad);
}
