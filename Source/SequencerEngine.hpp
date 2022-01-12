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
    void togglePlay();
    
    bool isPlaying()        { return m_IsPlaying; }
    int getPosition()       { return m_Position; }
    int getLength()         { return m_TotalLength; }
    
    int getBMP()            { return m_BPM; }
    void setBMP(int bpm)    { this->m_BPM = bpm; }

private:
    //==============================================================================
    void prepareUpdateInterval();
    
    //==============================================================================
    Array<Array<int>*> sequence;
    
    int m_BPM;
    
    bool m_IsPlaying = false;

    int m_Position = 0;
    int m_TotalSamples = 0;
    int m_SamplesRemining = 0;
    int m_UpdateInterval = 0;
    double m_SampleRate = 0;
    
    const int m_TotalLength = 16;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerEngine)

    //==============================================================================
};
