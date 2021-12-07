//
//  SamplerAudioSource.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#pragma once

#include <JuceHeader.h>
#include "Distortion.hpp"

using namespace juce;
using namespace dsp;

struct SamplerAudioSource : public AudioSource
{
public:
    //==============================================================================
    SamplerAudioSource (MidiKeyboardState&);
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    MidiMessageCollector midiCollector;
    Synthesiser synth;

private:
    //==============================================================================
    void addSound(String name, int note);
    
    //==============================================================================
    MidiKeyboardState& keyboardState;
    ProcessorChain<Distortion<float>> fxChain;
};
