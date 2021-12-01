//
//  SamplerAudioSource.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#include "SamplerAudioSource.hpp"

SamplerAudioSource::SamplerAudioSource (MidiKeyboardState& keyState)  : keyboardState (keyState)
{
    addSound("bass_drum.wav", 0);
    addSound("bass_drum.wav", 1);
    addSound("bass_drum.wav", 2);

    addSound("snare.wav", 3);
    addSound("snare.wav", 4);
    addSound("snare.wav", 5);
    
    addSound("hi_hat.wav", 6);
    addSound("hi_hat.wav", 7);
    addSound("hi_hat.wav", 8);
}

void SamplerAudioSource::addSound(String name, int note)
{
    // create input stream
    auto assetsDir = File::getSpecialLocation (File::currentExecutableFile)
        .getParentDirectory();
    
    auto resourceFile = assetsDir.getChildFile (name);
    auto inputStream = resourceFile.createInputStream();
    
    // create reader
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatReader> audioReader (wavFormat.createReaderFor (inputStream.release(), true));

    // midi range
    BigInteger allNotes;
    allNotes.setRange (note, note+1, true);
    
    // setup synth
    synth.addVoice (new SamplerVoice());
    synth.addSound (new SamplerSound (name, *audioReader, allNotes, note, 0.1, 0.1, 10.0));
}
    
void SamplerAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    midiCollector.reset (sampleRate);
    synth.setCurrentPlaybackSampleRate (sampleRate);
}
    
void SamplerAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);
    keyboardState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);
    
    synth.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
}
    
void SamplerAudioSource::releaseResources() {}
