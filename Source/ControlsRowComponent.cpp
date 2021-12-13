/*
  ==============================================================================

    ControlsRowComponent.cpp
    Created: 13 Dec 2021 3:25:31pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsRowComponent.h"

ControlsRowComponent::ControlsRowComponent(String title, Array<String> s): titles(s)
{
    addAndMakeVisible(titleLabel);
    titleLabel.setText(title, juce::dontSendNotification);
    titleLabel.setColour(Label::textColourId, Colours::black);
    titleLabel.setFont(Font(17, Font::bold));

    for (int i = 0; i < titles.size(); i++) {
        addSlider();
        addLabel(titles[i]);
    }
}

ControlsRowComponent::~ControlsRowComponent()
{
    for (int i = 0; i < sliders.size(); i++) {
        sliders[i]->removeListener (this);
    }
}

void ControlsRowComponent::setListener(Listener *l)
{
    listener = l;
}

void ControlsRowComponent::removeListener(Listener *l)
{
    listener = NULL;
}

void ControlsRowComponent::addSlider()
{
    auto slider = new Slider(Slider::Rotary, Slider::TextEntryBoxPosition::NoTextBox);
    addAndMakeVisible(slider);
    slider->setRange(0, 1);
    slider->setColour(Slider::textBoxTextColourId, Colours::black);
    slider->addListener(this);
    
    sliders.add(slider);
}

void ControlsRowComponent::addLabel(String title)
{
    auto label = new Label();
    label->setText(title, juce::dontSendNotification);
    label->setColour(Label::textColourId, Colours::black);
    label->setJustificationType(Justification(Justification::Flags::centred));
    addAndMakeVisible(label);
    
    labels.add(label);
}

void ControlsRowComponent::paint(Graphics &g)
{
    auto cornerSize = 6.0f;
    auto bounds = getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    g.setColour (Colour (178, 152, 220));
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 0.5f);
}

void ControlsRowComponent::resized()
{
    titleLabel.setBounds(8, 0, 100, 40);
    
    int sliderSide = 60;
    int labelWidth = 80;
    
    for (int i = 0; i < sliders.size(); i++)
    {
        sliders[i]->setBounds(i * sliderSide, 26, sliderSide, sliderSide);
        labels[i]->setBounds((i * sliderSide) + (sliderSide - labelWidth)/2, 80, labelWidth, 18);
    }
}

void ControlsRowComponent::sliderValueChanged (juce::Slider* slider)
{
    int index = sliders.indexOf(slider);
    listener->handleValueChanged(this, index, slider->getValue());
}
