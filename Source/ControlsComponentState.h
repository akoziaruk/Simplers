/*
  ==============================================================================

    ControlsComponentState.h
    Created: 9 Dec 2021 11:54:51am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ControlsComponentState
{
public:
    //==============================================================================
    ControlsComponentState();

    enum Control {
        distortion,
        reverb
    };
    
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void handleValueChanged(ControlsComponentState* source, Control control, float value) = 0;
    };
    
    void setListener(Listener* listener);
    void removeListener (Listener* listener);
    void setReverb(float value);
    void setDistortion(float value);

    
private:
    //==============================================================================

    
    //==============================================================================
    Listener* listener;
    
    float reverbValue = 0;
    float distortionValue = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponentState)
};

using ControlsComponentStateListener = ControlsComponentState::Listener;
using ComponentStateControl = ControlsComponentState::Control;

