//
//  SamplerAudioSource.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#pragma once

#include <JuceHeader.h>
#include "Distortion.hpp"
#include "ControlsComponentState.h"

using namespace juce;
using namespace dsp;

struct SamplerAudioSource : public AudioSource,
                            public ControlsComponentStateListener
{
public:
    //==============================================================================
    SamplerAudioSource (MidiKeyboardState&);
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void handleValueChanged(ControlsComponentState* source, Parameters parameters) override;
    void setParameters(Parameters parameters);

    //==============================================================================
    Synthesiser synth;

private:
    //==============================================================================
    void addSound(String name, int note);
    void updateEffectsWithParameters(Parameters parameters);
    void updateReverb(Parameters::Reverb parameters);
    void updateDistortion(Parameters::Distortion parameters);

    //==============================================================================
    MidiKeyboardState& keyboardState;
    
    enum
    {
        reverbIndex,
        distortionIndex,
    };
    ProcessorChain<dsp::Reverb, Distortion<float>> fxChain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerAudioSource)
};
