/*
  ==============================================================================

    Parameters.h
    Created: 14 Dec 2021 1:03:47pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

/*
    Parameter values should be in range 0..1
 */

struct Parameters {
    
    struct Reverb {
        bool enabled = false;
        float dry = 0.5;
        float wet = 0.5;
        float room = 0.33;
        float damping = 0.4;
        float width = 1;
        float freeze = 0;
    };
    
    struct Distortion {
        bool enabled = false;
        float preGain = 0.5;
        float postGain = 0.6;
    };
    
    Reverb reverb;
    Distortion distortion;
};
