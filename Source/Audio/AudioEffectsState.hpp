/*
  ==============================================================================

    AudioEffectsState.h
    Created: 9 Dec 2021 11:54:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#import "Parameters.hpp"

class AudioEffectsState
{
public:
    //==============================================================================
    AudioEffectsState() {};
    
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void handleValueChanged(AudioEffectsState* source, Parameters parameters) = 0;
    };
    
    void setListener(Listener* l)        { m_Listener = l; };
    void removeListener (Listener* l)    { m_Listener = NULL; };
    
    Parameters getParameters()           { return m_Parameters; };
    void setParameters(Parameters p)     { m_Parameters = p; m_Listener->handleValueChanged(this, m_Parameters); };
    
private:

    //==============================================================================
    Listener* m_Listener;
    Parameters m_Parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioEffectsState)
};

using AudioEffectsStateListener = AudioEffectsState::Listener;

