/*
  ==============================================================================

    MidiSequencer.cpp
    Created: 16 Dec 2021 10:44:47am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerEngine.hpp"

SequencerEngine::SequencerEngine(int sequencerSize)
{
    HighResolutionTimer::startTimer(60);
    
    // setup sequencer with provided size
    for (int i = 0; i < sequencerSize; i++)
    {
        sequence.add(new Array<int>());
    }
    
//    add(0, 0);
//    add(5, 0);
//    add(0, 1);
//    add(4, 2);
//    add(0, 4);
//    add(4, 6);
//    add(0, 8);
//    add(4, 10);
//    add(0, 12);
//    add(6, 14);
    
//    remove(0, 0);
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
    totalSamples += numSamples;
    samplesRemining = totalSamples % updateInterval;
    
    if ((samplesRemining + numSamples) >= updateInterval)
    {
//        DBG(position);

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
    updateInterval = 60.0 / bpm * sampleRate / kicksPerBit;
}

void SequencerEngine::reset()
{
    HighResolutionTimer::stopTimer();
    totalSamples = 0;
}

void SequencerEngine::hiResTimerCallback()
{
    updateInterval = 60.0 / bpm * sampleRate / kicksPerBit;
}
