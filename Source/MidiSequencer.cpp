/*
  ==============================================================================

    MidiSequencer.cpp
    Created: 16 Dec 2021 10:44:47am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "MidiSequencer.hpp"

MidiSequencer::MidiSequencer()
{
//    int timer = 100 / 60 * 1000 / 4; // BMP / sec in min * missis in sec / number of bits
//    startTimer(timer);
    
    HighResolutionTimer::startTimer(60);
    
    // save midi message at time stamp
//    sequence.addEvent(MidiMessage::noteOn (1, 5, 0.1f), 1);
//    sequence.addEvent(MidiMessage::noteOff (1, 5, 0.1f), 2);
//
    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 1);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 2);

    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 2);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 3);

    sequence.addEvent(MidiMessage::noteOn (1, 2, 1.0f), 3);
    sequence.addEvent(MidiMessage::noteOff (1, 2, 1.0f), 4);
    
    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 5);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 6);

    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 6);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 7);
    
    sequence.addEvent(MidiMessage::noteOn (1, 2, 1.0f), 7);
    sequence.addEvent(MidiMessage::noteOff (1, 2, 1.0f), 8);
    
    
    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 9);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 10);

    sequence.addEvent(MidiMessage::noteOn (1, 2, 1.0f), 11);
    sequence.addEvent(MidiMessage::noteOff (1, 2, 1.0f), 12);
    
    sequence.addEvent(MidiMessage::noteOn (1, 1, 1.0f), 13);
    sequence.addEvent(MidiMessage::noteOff (1, 1, 1.0f), 14);

    sequence.addEvent(MidiMessage::noteOn (1, 2, 1.0f), 15);
    sequence.addEvent(MidiMessage::noteOff (1, 2, 1.0f), 16);
}

void MidiSequencer::getNextEvents(MidiKeyboardState &state, int startSample, int numSamples)
{
    totalSamples += numSamples;
    samplesRemining = totalSamples % updateInterval;
    
    if ((samplesRemining + numSamples) >= updateInterval)
    {
        DBG("CLICK");
        position = (position == 15) ? 0 : position + 1;

        for (auto i = 0; i < sequence.getNumEvents(); i++)
       {
           MidiMessageSequence::MidiEventHolder *event = sequence.getEventPointer(i);
   
           if (event->message.getTimeStamp() == position)
           {
               auto message = event->message;
      
               if (message.isNoteOn()) {
                   state.noteOn (message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
               } else {
                   state.noteOff (message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
               }
           }
   
       }
    }
}

void MidiSequencer::prepareToPlay(double s)
{
    sampleRate = s;
    updateInterval = 60.0 / bpm * sampleRate;
}

void MidiSequencer::reset()
{
    HighResolutionTimer::stopTimer();
    totalSamples = 0;
}

void MidiSequencer::hiResTimerCallback()
{
    updateInterval = 60.0 / bpm * sampleRate;
}


//void MidiSequencer::timerCallback()
//{
//
//    // copy messages in keyboard state
//
//    time = (time == 16) ? 1: time+1;
//}

