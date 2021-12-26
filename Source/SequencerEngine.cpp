/*
  ==============================================================================

    MidiSequencer.cpp
    Created: 16 Dec 2021 10:44:47am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "SequencerEngine.hpp"

SequencerEngine::SequencerEngine(int _bpm): m_BPM(_bpm)
{
    for (int i = 0; i < m_TotalLength; i++) {
        sequence.add(new Array<int>());
    }
}

SequencerEngine::~SequencerEngine() {
    for (int i = sequence.size(); i > 0; i--) {
        Array<int>* array = sequence[i];
        sequence.remove(i);
        delete array;
    }
}

bool SequencerEngine::toggle(int sampleIndex, int position)
{
    Array<int>* arr = sequence[position];
    int index = arr->indexOf(sampleIndex);
    if (index == -1) {
        arr->add(sampleIndex);
        return true;
    } else {
        arr->remove(index);
        return false;
    }
}

void SequencerEngine::getNextEvents(MidiKeyboardState &state, int startSample, int numSamples)
{
    if (!m_IsPlaying) { return; }
    
    m_TotalSamples += numSamples;
    m_SamplesRemining = m_TotalSamples % m_UpdateInterval;
    
    if ((m_SamplesRemining + numSamples) >= m_UpdateInterval) {
        Array<int>& array = *sequence[m_Position];
   
        for (int i = 0; i < array.size(); i++) {
            int sound = array[i];
            state.noteOn (1, sound, 1);
        }

        m_Position = (m_Position == sequence.size() -1 ) ? 0 : m_Position + 1;
    }
}
    
void SequencerEngine::prepareToPlay(double s)
{
    m_SampleRate = s;
    prepareUpdateInterval();
}

void SequencerEngine::reset()
{
    HighResolutionTimer::stopTimer();
    m_TotalSamples = 0;
    m_Position = 0;
}

void SequencerEngine::hiResTimerCallback()
{
    prepareUpdateInterval();
}

void SequencerEngine::togglePlay()
{
    m_IsPlaying = !m_IsPlaying;
    
    if (!m_IsPlaying)
        reset();
    else
        HighResolutionTimer::startTimer(60);
}

void SequencerEngine::prepareUpdateInterval()
{
    m_UpdateInterval = 60.0 / m_BPM * m_SampleRate / m_GridSize;
}


