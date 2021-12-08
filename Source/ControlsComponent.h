/*
  ==============================================================================

    ControlsComponent.h
    Created: 8 Dec 2021 11:12:24am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include <JuceHeader.h>

using namespace juce;

class ControlsComponent  : public Component,
                           public Slider::Listener
{
public:
    //==============================================================================
    ControlsComponent();
    ~ControlsComponent();
        
private:
    //==============================================================================
    void resized() override;
    void paint(Graphics &g) override;
    void sliderValueChanged (Slider* slider) override;
    
    //==============================================================================
    Slider reverbSlider;
    Label  reverbLabel;
    Slider distortionSlider;
    Label  distortionLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
