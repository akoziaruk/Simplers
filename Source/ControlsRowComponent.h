/*
  ==============================================================================

    ControlsRowComponent.h
    Created: 13 Dec 2021 3:25:31pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class ControlsRowComponent  : public Component,
                              public Slider::Listener
{
public:
    //==============================================================================
    ControlsRowComponent(String, Array<String>);
    ~ControlsRowComponent();
    
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void handleValueChanged(ControlsRowComponent* source, int index, float value) = 0;
    };
    
    void setListener(Listener* listener);
    void removeListener(Listener* listener);
    
private:
    //==============================================================================
    void resized() override;
    void paint(Graphics &g) override;
    void sliderValueChanged (Slider* slider) override;
    
    void addSlider();
    void addLabel(String title);
    void resizeSlider(Slider* slider);
    void resizeLabel(Label* slider);
    
    //==============================================================================
    Listener* listener;

    Label titleLabel;

    Array<Slider*> sliders;
    Array<Label*> labels;
    Array<String> titles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsRowComponent)
};
