/*
  ==============================================================================

    ControlsComponent.cpp
    Created: 8 Dec 2021 11:12:24am
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsComponent.hpp"

ControlsComponent::ControlsComponent(AudioEffectsState& s): m_State(s)
{
    auto parameters = m_State.getParameters();
    
    m_ReverbControls.setSlidersData(Array<SliderData>(SliderData("Dry",       parameters.reverb.dry),
                                                      SliderData("Wet",       parameters.reverb.wet),
                                                      SliderData("Room",      parameters.reverb.room),
                                                      SliderData("Damping",   parameters.reverb.damping),
                                                      SliderData("Width",     parameters.reverb.width),
                                                      SliderData("Freeze",    parameters.reverb.freeze)));
    
    m_ReverbControls.setListener(this);
    addAndMakeVisible(m_ReverbControls);
    
    m_DistortionControls.setSlidersData(Array<SliderData>(SliderData("Pre Gain",    parameters.distortion.preGain),
                                                          SliderData("Post Gain",   parameters.distortion.postGain)));
    
    m_DistortionControls.setListener(this);
    addAndMakeVisible(m_DistortionControls);
}

ControlsComponent::~ControlsComponent()
{
    m_ReverbControls.removeListener(this);
    m_DistortionControls.removeListener(this);
}

void ControlsComponent::resized()
{
    m_ReverbControls.setBounds(8, 8, getWidth() - 16, 100);
    m_DistortionControls.setBounds(8, 116, getWidth() - 16, 100);
}

void ControlsComponent::paint(Graphics &g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (166, 99, 204));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}

void ControlsComponent::setEnabled(ControlsRowComponent* source, bool enabled)
{
    auto parameters = m_State.getParameters();

    if (source == &m_ReverbControls)
        parameters.reverb.enabled = enabled;
    else if (source == &m_DistortionControls)
        parameters.distortion.enabled = enabled;
    
    m_State.setParameters(parameters);
}

void ControlsComponent::handleValueChanged(ControlsRowComponent *source, int index, float value)
{
    auto parameters = m_State.getParameters();

    if (source == &m_ReverbControls) {
        updateParameters(&parameters.reverb, index, value);
    }
    else if (source == &m_DistortionControls) {
        updateParameters(&parameters.distortion, index, value);
    }
    
    m_State.setParameters(parameters);
}

void ControlsComponent::updateParameters(Parameters::Reverb *reverb, int index, float value)
{
    switch (Reverb(index)) {
        case Reverb::dry:
            reverb->dry = value;                break;
        case Reverb::wet:
            reverb->wet = value;                break;
        case Reverb::room:
            reverb->room = value;               break;
        case Reverb::damping:
            reverb->damping = value;            break;
        case Reverb::width:
            reverb->width = value;              break;
        case Reverb::freeze:
            reverb->freeze = value;             break;
    }
}

void ControlsComponent::updateParameters(Parameters::Distortion *distortion, int index, float value)
{
    switch (Distortion(index)) {
        case Distortion::preGain:
            distortion->preGain = value;            break;
        case Distortion::postGain:
            distortion->postGain = value;           break;
    }
}
