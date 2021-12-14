/*
  ==============================================================================

    ControlsComponentState.h
    Created: 9 Dec 2021 11:54:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#import "Parameters.h"

class ControlsComponentState
{
public:
    //==============================================================================
    ControlsComponentState() {};
    
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void handleValueChanged(ControlsComponentState* source, Parameters parameters) = 0;
    };
    
    void setListener(Listener* l)        { listener = l; };
    void removeListener (Listener* l)    { listener = NULL; };
    
    Parameters getParameters() { return parameters; };
    void setParameters(Parameters p) { parameters = p; listener->handleValueChanged(this, parameters); };
    
private:

    //==============================================================================
    Listener* listener;
    Parameters parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponentState)
};

using ControlsComponentStateListener = ControlsComponentState::Listener;

