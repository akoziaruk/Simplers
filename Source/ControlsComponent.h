/*
  ==============================================================================

    ControlsComponent.h
    Created: 8 Dec 2021 11:12:24am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlsComponentState.h"
#include "ControlsRowComponent.h"

using namespace juce;

class ControlsComponent  : public Component,
                           public ControlsRowComponent::Listener
{
public:
    //==============================================================================
    ControlsComponent(ControlsComponentState& state);
    ~ControlsComponent();
    
private:
    //==============================================================================
    void resized() override;
    void paint(Graphics &g) override;
    void handleValueChanged(ControlsRowComponent* source, int index, float value) override;
    
    //==============================================================================
    ControlsComponentState& state;
    
    ControlsRowComponent reverbControls { "Reverb", Array<String>("Dry", "Wet", "Room", "Damping", "Width", "Freeze") };
    //ControlsRowComponent distortionControls
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
