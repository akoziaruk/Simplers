/*
  ==============================================================================

    SequencerComponent.h
    Created: 16 Dec 2021 2:53:11pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MidiSequencer.hpp"

using namespace juce;

class SequencerComponent  : public Component
{
public:
    
    SequencerComponent(MidiSequencer&);
 
private:
    
};