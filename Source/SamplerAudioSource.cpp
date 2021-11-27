//
//  SamplerAudioSource.cpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/26/21.
//

#include "SamplerAudioSource.hpp"

//struct SamplerAudioSource : public AudioSource
//{
SamplerAudioSource::SamplerAudioSource (MidiKeyboardState& keyState)  : keyboardState (keyState)
{
    // create input stream
    auto assetsDir = File::getSpecialLocation (File::currentExecutableFile)
        .getParentDirectory();
    
    auto resourceFile = assetsDir.getChildFile ("bass_drum.wav");
    auto inputStream = resourceFile.createInputStream();
    
    // create reader
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatReader> audioReader (wavFormat.createReaderFor (inputStream.release(), true));

    // midi range
    BigInteger allNotes;
    allNotes.setRange (0, 128, true);
    
    // setup synth
    synth.addVoice (new SamplerVoice());
    synth.addSound (new SamplerSound ("sample", *audioReader, allNotes, 74, 0.1, 0.1, 10.0));
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
