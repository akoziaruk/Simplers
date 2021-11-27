//
//  SamplerAudioSource.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#pragma once

#include <JuceHeader.h>
using namespace juce;

struct SamplerAudioSource : public AudioSource
{
public:
    //==============================================================================
    SamplerAudioSource (MidiKeyboardState&);
    
    //==============================================================================
    MidiMessageCollector midiCollector;
    Synthesiser synth;

private:
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //==============================================================================
    MidiKeyboardState& keyboardState;

};
