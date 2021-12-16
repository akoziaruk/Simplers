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

class MidiSequencer: public HighResolutionTimer
{
public:
    //==============================================================================
    MidiSequencer();
    
    void getNextEvents(MidiKeyboardState& state, int startSample, int numSamples);
    void addEvent(int note, int index) { };
    void prepareToPlay(double sampleRate);
    void reset();
    
    void hiResTimerCallback() override;
    
private:
    //==============================================================================

    MidiMessageSequence sequence;

    int position = 0;
    int totalSamples = 0;
    int samplesRemining = 0;
    int updateInterval = 0;
    double sampleRate = 0;
    int bpm = 120;

};
