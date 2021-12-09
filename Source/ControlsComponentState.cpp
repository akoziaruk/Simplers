/*
  ==============================================================================

    ControlsComponentState.cpp
    Created: 9 Dec 2021 11:54:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsComponentState.h"

ControlsComponentState::ControlsComponentState(){}

void ControlsComponentState::setListener(Listener *l)
{
    listener = l;
}

void ControlsComponentState::removeListener(Listener *listener)
{
    listener = NULL;
}

void ControlsComponentState::setReverb(float value)
{
    reverbValue = value;
    
    listener->handleValueChanged(this, reverb, value);
}

void ControlsComponentState::setDistortion(float value)
{
    distortionValue = value;
    
    listener->handleValueChanged(this, distortion, value);
}
