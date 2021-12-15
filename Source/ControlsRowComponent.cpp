/*
  ==============================================================================

    ControlsRowComponent.cpp
    Created: 13 Dec 2021 3:25:31pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsRowComponent.h"

ControlsRowComponent::ControlsRowComponent(String title)
{
    addAndMakeVisible(titleLabel);
    titleLabel.setText(title, juce::dontSendNotification);
    titleLabel.setColour(Label::textColourId, Colours::black);
    titleLabel.setFont(Font(17, Font::bold));
}

void ControlsRowComponent::setSlidersData(Array<SliderData> items)
{
    for (int i = 0; i < items.size(); i++) {
        auto item = items[i];
        addSlider(item.value);
        addLabel(item.name);
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

void ControlsRowComponent::addSlider(float value)
{
    auto slider = new Slider(Slider::Rotary, Slider::TextEntryBoxPosition::NoTextBox);
    
    slider->setValue(value);
    slider->setRange(0, 1);
    slider->setColour(Slider::textBoxTextColourId, Colours::black);
    slider->addListener(this);
    
    sliders.add(slider);
    
    addAndMakeVisible(slider);
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
    
    int labelWidth = 80;
    int sliderSide = getWidth()/sliders.size();
    int sliderWidth = jmin(labelWidth, sliderSide);
    
    for (int i = 0; i < sliders.size(); i++)
    {
        sliders[i]->setBounds(i * sliderWidth, 26, sliderWidth, jmin(60, sliderSide));
        labels[i]->setBounds((i * sliderWidth) + (sliderWidth - labelWidth)/2, 80, labelWidth, 18);
    }
}

void ControlsRowComponent::sliderValueChanged (juce::Slider* slider)
{
    int index = sliders.indexOf(slider);
    listener->handleValueChanged(this, index, slider->getValue());
}
