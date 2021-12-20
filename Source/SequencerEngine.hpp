/*
  ==============================================================================

    MidiSequencer.hpp
    Created: 16 Dec 2021 10:44:47am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

// should store midi signal sequence, when what sound should play
// write midi events to keyboard state

class SequencerEngine: public HighResolutionTimer
{
public:
    //==============================================================================
    SequencerEngine(int bpm);
    ~SequencerEngine();
    
    void getNextEvents(MidiKeyboardState& state, int startSample, int numSamples);
    void addEvent(int note, int index) { };
    void prepareToPlay(double sampleRate);
    void reset();
    
    void hiResTimerCallback() override;
    
    bool toggle(int sampleIndex, int position);
    
    int getPosition() { return position; }
    
    bool isPlaying()  { return _isPlaying; }
    void togglePlay();
    
    int getNumberOfSounds() { return Size::soundsNumber; }
    int getLength()         { return Size::length; }
    
private:
    //==============================================================================
    void prepareUpdateInterval();
    
    //==============================================================================

    Array<Array<int>*> sequence;
    
    int bpm;
    
    bool _isPlaying = false;

    int position = 0;
    int totalSamples = 0;
    int samplesRemining = 0;
    int updateInterval = 0;
    double sampleRate = 0;
    
    int grid = 4;
    
    //==============================================================================

    enum Size {
        soundsNumber = 9,
        length = 16
    };
};
