/*
  ==============================================================================

    ControlsRowComponent.cpp
    Created: 13 Dec 2021 3:25:31pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#include "ControlsRowComponent.hpp"

ControlsRowComponent::ControlsRowComponent(String title)
{
    m_TitleLabel.setText(title, juce::dontSendNotification);
    m_TitleLabel.setColour(Label::textColourId, Colours::black);
    m_TitleLabel.setFont(Font(17, Font::bold));
    addAndMakeVisible(m_TitleLabel);
    
    enableButton.setColour(ToggleButton::ColourIds::tickColourId, Colours::black);
    enableButton.setColour(ToggleButton::ColourIds::tickDisabledColourId, Colours::black);
    enableButton.onClick = [this] { m_Listener->setEnabled(this, enableButton.getToggleState()); };
    
    addAndMakeVisible(enableButton);
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
    for (int i = 0; i < m_Sliders.size(); i++) {
        m_Sliders[i]->removeListener (this);
    }
}

void ControlsRowComponent::setListener(Listener *l)
{
    m_Listener = l;
}

void ControlsRowComponent::removeListener(Listener *l)
{
    m_Listener = NULL;
}

void ControlsRowComponent::addSlider(float value)
{
    auto slider = new Slider(Slider::Rotary, Slider::TextEntryBoxPosition::NoTextBox);
    
    slider->setValue(value);
    slider->setRange(0, 1);
    slider->setColour(Slider::textBoxTextColourId, Colours::black);
    slider->addListener(this);
    
    m_Sliders.add(slider);
    
    addAndMakeVisible(slider);
}

void ControlsRowComponent::addLabel(String title)
{
    auto label = new Label();
    label->setText(title, juce::dontSendNotification);
    label->setColour(Label::textColourId, Colours::black);
    label->setJustificationType(Justification(Justification::Flags::centred));
    addAndMakeVisible(label);
    
    m_Labels.add(label);
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
    m_TitleLabel.setBounds(8, 0, 100, 40);
    enableButton.setBounds(120, 0, 40, 40);
    
    int labelWidth = 80;
    int sliderSide = getWidth()/m_Sliders.size();
    int sliderWidth = jmin(labelWidth, sliderSide);
    
    for (int i = 0; i < m_Sliders.size(); i++) {
        m_Sliders[i]->setBounds(i * sliderWidth, 26, sliderWidth, jmin(60, sliderSide));
        m_Labels[i]->setBounds((i * sliderWidth) + (sliderWidth - labelWidth)/2, 80, labelWidth, 18);
    }
}

void ControlsRowComponent::sliderValueChanged (juce::Slider* slider)
{
    int index = m_Sliders.indexOf(slider);
    m_Listener->handleValueChanged(this, index, slider->getValue());
}
