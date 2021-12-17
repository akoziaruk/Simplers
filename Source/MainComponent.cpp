#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    padButton.setColour(TextButton::ColourIds::buttonColourId, Colour(191, 204, 148));
    sequencerButton.setColour(TextButton::ColourIds::buttonColourId, Colour(230, 170, 206));
    
    addAndMakeVisible (padButton);
    addAndMakeVisible (sequencerButton);
    addAndMakeVisible (padComponent);
    addAndMakeVisible (controlsComponent);
    addChildComponent (sequencerComponent);
    
    padButton.addListener(this);
    sequencerButton.addListener(this);
    
    audioDeviceManager.initialise (2, 2, nullptr, true, {}, nullptr);

    audioSourcePlayer.setSource (&audioEngine);
    audioDeviceManager.addAudioCallback (&audioSourcePlayer);
}

MainComponent::~MainComponent()
{
    padButton.removeListener(this);
    sequencerButton.removeListener(this);

    audioSourcePlayer.setSource (nullptr);
    audioDeviceManager.removeAudioCallback (&audioSourcePlayer);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour (238, 132, 52));
}

void MainComponent::resized()
{
    int margin = 16;
    int width = getWidth() * 0.45;
    int height = getHeight() - margin*2;
    padComponent        .setBounds(margin*2, margin, height, height);
    controlsComponent   .setBounds(width + margin*2, margin, width, height);
    sequencerComponent  .setBounds(margin*2, margin, getWidth()*0.9, height);
    
    int buttonSide = 40;
    int x = getWidth()-buttonSide-8;
    
    padButton           .setBounds(x, 20, buttonSide, buttonSide);
    sequencerButton     .setBounds(x, 20+buttonSide+4, buttonSide, buttonSide);
}

void MainComponent::buttonClicked(Button *button)
{
    bool showPad = (button == &padButton);
    
    padComponent.setVisible(showPad);
    controlsComponent.setVisible(showPad);
    sequencerComponent.setVisible(!showPad);
}
