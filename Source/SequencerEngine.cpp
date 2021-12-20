/*
  ==============================================================================

    MidiSequencer.cpp
    Created: 16 Dec 2021 10:44:47am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerEngine.hpp"

SequencerEngine::SequencerEngine(int _bpm): bpm(_bpm)
{
    for (int i = 0; i < length; i++)
    {
        sequence.add(new Array<int>());
    }
}

SequencerEngine::~SequencerEngine() {
    for (int i = sequence.size(); i > 0; i--)
    {
        Array<int>* array = sequence[i];
        sequence.remove(i);
        delete array;
    }
}

bool SequencerEngine::toggle(int sampleIndex, int position)
{
    Array<int>* arr = sequence[position];
    int index = arr->indexOf(sampleIndex);
    if (index == -1)
    {
        arr->add(sampleIndex);
        return true;
    }
    else
    {
        arr->remove(index);
        return false;
    }
}

void SequencerEngine::getNextEvents(MidiKeyboardState &state, int startSample, int numSamples)
{
    if (!_isPlaying) { return; }
    
    totalSamples += numSamples;
    samplesRemining = totalSamples % updateInterval;
    
    if ((samplesRemining + numSamples) >= updateInterval)
    {
        Array<int>& array = *sequence[position];
   
        for (int i = 0; i < array.size(); i++)
        {
            int sound = array[i];
            state.noteOn (1, sound, 1);
        }

        position = (position == sequence.size() -1 ) ? 0 : position + 1;
    }
}
    
void SequencerEngine::prepareToPlay(double s)
{
    sampleRate = s;
    prepareUpdateInterval();
}

void SequencerEngine::reset()
{
    HighResolutionTimer::stopTimer();
    totalSamples = 0;
    position = 0;
}

void SequencerEngine::hiResTimerCallback()
{
    prepareUpdateInterval();
}

void SequencerEngine::togglePlay()
{
    _isPlaying = !_isPlaying;
    
    if (!_isPlaying)
        reset();
    else
        HighResolutionTimer::startTimer(60);
}

void SequencerEngine::prepareUpdateInterval()
{
    updateInterval = 60.0 / bpm * sampleRate / grid;
}


