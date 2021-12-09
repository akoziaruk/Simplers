//
//  PadButton.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 12/1/21.
//

#include <JuceHeader.h>

using namespace juce;

class PadButton  : public Button
{
public:
    //==============================================================================
    PadButton();
    ~PadButton() override;

    //==============================================================================
    void paintButton (Graphics&, bool, bool) override;
    void colourChanged() override;
    void buttonStateChanged() override;
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PadButton)

};
