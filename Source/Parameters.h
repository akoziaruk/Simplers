/*
  ==============================================================================

    Parameters.h
    Created: 14 Dec 2021 1:03:47pm
    Author:  Olexander Koziaruk

  ==============================================================================
*/

#pragma once

struct Parameters {

    struct Reverb {
        float dry = 0.5;
        float wet = 0.5;
        float room = 0.33;
        float damping = 0.4;
        float width = 1;
        float freeze = 0;
    };
    
    struct Distortion {
        
    };
    
    Reverb reverb;
    Distortion distortion;

};
