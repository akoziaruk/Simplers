#pragma once

#include <JuceHeader.h>
#include "AudioEngine.hpp"
#include "PadBoardComponent.hpp"
#include "ControlsComponent.hpp"
#include "SequencerComponent.hpp"

using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public Component,
                       public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(Button*) override;

private:
    //==============================================================================

    AudioDeviceManager audioDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    AudioEngine audioEngine;
    
    PadBoardComponent   padComponent        { audioEngine.midiState };
    ControlsComponent   controlsComponent   { audioEngine.audioEffectsState };
    
    SequencerComponent  sequencerComponent  { audioEngine.midiSequencer,
                                              audioEngine.getNumberOfSounds(),
                                              audioEngine.midiSequencer.getLength() };
    
    TextButton padButton { "" };
    TextButton sequencerButton { "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
