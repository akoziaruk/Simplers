#pragma once

#include <JuceHeader.h>
#include "SamplerAudioSource.hpp"
#include "MidiPadBoardComponent.hpp"
#include "ControlsComponent.h"
//#include "ControlsComponentState.h"

using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    AudioDeviceManager audioDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    SamplerAudioSource samplerAudioSource        { keyboardState };
    
    MidiKeyboardState keyboardState;
    MidiPadBoardComponent padComponent { keyboardState };
    
    ControlsComponentState controlsState;
    ControlsComponent controlsComponent { controlsState };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
