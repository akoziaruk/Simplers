#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    addAndMakeVisible (padComponent);
    
    audioDeviceManager.initialise (2, 2, nullptr, true, {}, nullptr);

    audioSourcePlayer.setSource (&samplerAudioSource);
    audioDeviceManager.addAudioCallback (&audioSourcePlayer);
}

MainComponent::~MainComponent()
{
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
    padComponent        .setBounds (8, 50, getWidth() - 16, getHeight() - 88);
}
