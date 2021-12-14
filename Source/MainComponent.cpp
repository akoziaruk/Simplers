#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    addAndMakeVisible (padComponent);
    addAndMakeVisible (controlsComponent);
    
    audioDeviceManager.initialise (2, 2, nullptr, true, {}, nullptr);

    audioSourcePlayer.setSource (&samplerAudioSource);
    audioDeviceManager.addAudioCallback (&audioSourcePlayer);
    
    controlsState.setListener(&samplerAudioSource);
    
    auto parameters = Parameters();
    samplerAudioSource.setParameters(parameters);
    controlsState.setParameters(parameters);
}

MainComponent::~MainComponent()
{
    audioSourcePlayer.setSource (nullptr);
    audioDeviceManager.removeAudioCallback (&audioSourcePlayer);
    controlsState.removeListener(&samplerAudioSource);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour (238, 132, 52));
}

void MainComponent::resized()
{
    int topMargin = 50;
    int padHeight = getWidth() - 16;
    padComponent        .setBounds (8, topMargin, getWidth() - 16, padHeight);
    controlsComponent   .setBounds(8, topMargin + padHeight + 8, getWidth() - 16, 200);
}
