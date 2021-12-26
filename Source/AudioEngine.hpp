//
//  SamplerAudioSource.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#pragma once

#include <JuceHeader.h>
#include "Distortion.hpp"
#include "AudioEffectsState.hpp"
#include "SequencerEngine.hpp"

using namespace juce;
using namespace dsp;

struct AudioEngine : public AudioSource,
                     public AudioEffectsStateListener
{
public:
    //==============================================================================
    AudioEngine();
    ~AudioEngine();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void handleValueChanged(AudioEffectsState* source, Parameters parameters) override;
    void setParameters(Parameters parameters);
    int getNumberOfSounds() { return m_Sampler.getNumSounds(); }

    //==============================================================================
    SequencerEngine midiSequencer { 120 };
    MidiKeyboardState midiState;
    AudioEffectsState audioEffectsState;


private:
    //==============================================================================
    void addSound(String name, int note);
    void updateEffectsWithParameters(Parameters parameters);
    void updateReverb(Parameters::Reverb parameters);
    void updateDistortion(Parameters::Distortion parameters);

    //==============================================================================
    Synthesiser m_Sampler;
    
    enum
    {
        reverbIndex,
        distortionIndex,
    };
    ProcessorChain<dsp::Reverb, Distortion<float>> fxChain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioEngine)
};
