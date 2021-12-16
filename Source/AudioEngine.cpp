//
//  SamplerAudioSource.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#include "AudioEngine.hpp"

AudioEngine::AudioEngine()
{
    addSound("kick1.wav", 0);
    addSound("kick2.wav", 1);
    addSound("sn1.wav", 2);
    addSound("clap.wav", 3);
    addSound("clave.wav", 4);
    addSound("crash.wav", 5);
    addSound("hat1.wav", 6);
    addSound("hat2.wav", 7);
    addSound("hat3.wav", 8);
        
    audioEffectsState.setListener(this);

    auto defaultParameters = Parameters();
    audioEffectsState.setParameters(defaultParameters);
}

AudioEngine::~AudioEngine()
{
    audioEffectsState.removeListener(this);
}

void AudioEngine::addSound(String name, int note)
{
    auto assetsDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory();

    auto resourceFile = assetsDir.getChildFile (name);;
    auto inputStream = resourceFile.createInputStream();
    
    // create reader
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatReader> audioReader (wavFormat.createReaderFor (inputStream.release(), true));

    // midi range
    BigInteger allNotes;
    allNotes.setRange (note, note+1, true);
    
    // setup synth
    sampler.addVoice (new SamplerVoice());
    sampler.addSound (new SamplerSound (name, *audioReader, allNotes, note, 0, 0.5, 10.0));
}
    
void AudioEngine::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    sampler.setCurrentPlaybackSampleRate (sampleRate);
    midiSequencer.prepareToPlay(sampleRate);
    fxChain.prepare ({ sampleRate, (juce::uint32) samplesPerBlockExpected, 2 });
}
    
void AudioEngine::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    midiSequencer.getNextEvents(midiState, 0, bufferToFill.numSamples);
    
    MidiBuffer incomingMidi;
    midiState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);
    
    sampler.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
    
    auto block = AudioBlock<float> (*bufferToFill.buffer).getSubBlock ((size_t) bufferToFill.startSample, (size_t) bufferToFill.numSamples);
    auto context = ProcessContextReplacing<float> (block);
    fxChain.process (context);
}
    
void AudioEngine::handleValueChanged(AudioEffectsState *source, Parameters parameters)
{
    updateEffectsWithParameters(parameters);
}

void AudioEngine::setParameters(Parameters parameters)
{
    updateEffectsWithParameters(parameters);
}

void AudioEngine::updateEffectsWithParameters(Parameters parameters)
{
    updateReverb(parameters.reverb);
    updateDistortion(parameters.distortion);
}

void AudioEngine::updateReverb(Parameters::Reverb params)
{
    auto& reverb = fxChain.template get<reverbIndex>();
    auto effectParams = reverb.getParameters();
    
    effectParams.dryLevel = params.dry;
    effectParams.wetLevel = params.wet;
    effectParams.roomSize = params.room;
    effectParams.damping = params.damping;
    effectParams.width = params.width;
    effectParams.freezeMode = params.freeze;

    reverb.setParameters(effectParams);
}

void AudioEngine::updateDistortion(Parameters::Distortion parameters)
{
    auto& distoriton = fxChain.template get<distortionIndex>();
    distoriton.setPreGain(parameters.preGain);
    distoriton.setPostGain(parameters.postGain);
}

void AudioEngine::releaseResources() {}
