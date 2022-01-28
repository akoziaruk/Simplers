#pragma once

#include <JuceHeader.h>
#include "MainComponent.hpp"
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

    AudioDeviceManager  m_AudioDeviceManager;
    AudioSourcePlayer   m_AudioSourcePlayer;
    AudioEngine         m_AudioEngine;
    
    PadBoardComponent   m_PadComponent        { m_AudioEngine.midiState };
    ControlsComponent   m_ControlsComponent   { m_AudioEngine.audioEffectsState };
    
    SequencerComponent  m_SequencerComponent  { m_AudioEngine.midiSequencer,
                                                m_AudioEngine.getNumberOfSounds(),
                                                m_AudioEngine.midiSequencer.getLength() };
    
    TextButton m_PadButton          { "" };
    TextButton m_SequencerButton    { "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
