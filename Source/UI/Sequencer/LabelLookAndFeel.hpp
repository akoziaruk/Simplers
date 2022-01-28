/*
  ==============================================================================

    LabelLookAndFeel.h
    Created: 13 Jan 2022 3:48:40pm
    Author:  Alexander Koziaruk

  ==============================================================================
*/

#include <JuceHeader.h>

class LabelLookAndFeel: public LookAndFeel_V2
{
public:
    void drawLabel (Graphics& g, Label& label) override
    {
        g.setColour(Colour(172, 117, 149));
        g.fillRoundedRectangle(label.getLocalBounds().toFloat(), 6);
        
        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (getLabelFont (label));

            g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }
    }
};
