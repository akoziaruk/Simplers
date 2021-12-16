/*
  ==============================================================================

    ControlsComponent.h
    Created: 8 Dec 2021 11:12:24am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioEffectsState.hpp"
#include "ControlsRowComponent.hpp"

using namespace juce;

class ControlsComponent  : public Component,
                           public ControlsRowComponent::Listener
{
public:
    //==============================================================================
    ControlsComponent(AudioEffectsState& state);
    ~ControlsComponent();
    
private:
    //==============================================================================
    void resized() override;
    void paint(Graphics &g) override;
    void handleValueChanged(ControlsRowComponent* source, int index, float value) override;
    
    void updateParameters(Parameters::Reverb* reverb, int index, float value);
    void updateParameters(Parameters::Distortion* distortion, int index, float value);

    //==============================================================================
    AudioEffectsState& state;
    
    ControlsRowComponent reverbControls { "Reverb" };
    enum Reverb: uint { dry, wet, room, damping, width, freeze };
    
    ControlsRowComponent distortionControls { "Distortion" };
    enum Distortion: uint { preGain, postGain };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
