#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    addAndMakeVisible (keyboardComponent);

    audioDeviceManager.initialise (2, 2, nullptr, true, {}, nullptr);

    audioSourcePlayer.setSource (&samplerAudioSource);
    audioDeviceManager.addAudioCallback (&audioSourcePlayer);
    audioDeviceManager.addMidiInputDeviceCallback ({}, &(samplerAudioSource.midiCollector));
    
}

MainComponent::~MainComponent()
{
    audioSourcePlayer.setSource (nullptr);
    audioDeviceManager.removeMidiInputDeviceCallback ({}, &(samplerAudioSource.midiCollector));
    audioDeviceManager.removeAudioCallback (&audioSourcePlayer);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    keyboardComponent   .setBounds (8, 96, getWidth() - 16, 64);
}
