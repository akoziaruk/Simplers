//
//  MidiPadBoardComponent.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 11/27/21.
//

#include <JuceHeader.h>
#include "PadButton.hpp"

using namespace juce;

class PadBoardComponent  :  public Component,
                            public Button::Listener
{
public:
    //==============================================================================
    PadBoardComponent(MidiKeyboardState& state);
    ~PadBoardComponent();
        
private:
    void resized() override;
    void paint (juce::Graphics& g) override;
    void buttonClicked (Button* button) override {};
    void buttonStateChanged (Button* button) override;
    
    void updatePad(int index, bool isDown);
    
    //==============================================================================
    MidiKeyboardState& state;
    Array<PadButton*> pads;
    
    int midiChannel = 1;
    int velocity = 1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PadBoardComponent)
};

