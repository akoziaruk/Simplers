//
//  Distortion.hpp
//  Simplers - App
//
//  Created by Olexander Koziaruk on 12/7/21.
//

#pragma once

#include <JuceHeader.h>
using namespace juce;
using namespace dsp;

template <typename Type>
class Distortion
{
public:
    //==============================================================================
    Distortion()
    {
        auto& waveshaper = processorChain.template get<waveshaperIndex>();
        waveshaper.functionToUse = [] (Type x) {
            return std::tanh (x);
        };
    }
    
    void setPreGain (float value) //value in range 0..1
    {
        float decibels = jmap<float>(value, 20, 70);
        auto& preGain = processorChain.template get<preGainIndex>();
        preGain.setGainDecibels (decibels);
    }

    void setPostGain (float value) //value in range 0..1
    {
        float decibels = jmap<float>(value, -50, 0);
        auto& postGain = processorChain.template get<postGainIndex>();
        postGain.setGainDecibels (decibels);
    }
    
    void setEnabled(bool enabled)
    {
        processorChain.template setBypassed<filterIndex>    (!enabled);
        processorChain.template setBypassed<preGainIndex>   (!enabled);
        processorChain.template setBypassed<waveshaperIndex>(!enabled);
        processorChain.template setBypassed<postGainIndex>  (!enabled);
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        auto& filter = processorChain.template get<filterIndex>();
        filter.state = FilterCoefs::makeFirstOrderHighPass (spec.sampleRate, 1000.0f);

        processorChain.prepare (spec);
    }

    //==============================================================================
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        processorChain.process (context);
    }

    //==============================================================================
    enum
    {
        filterIndex,
        preGainIndex,
        waveshaperIndex,
        postGainIndex
    };

    using Filter = IIR::Filter<Type>;
    using FilterCoefs = IIR::Coefficients<Type>;

    juce::dsp::ProcessorChain<ProcessorDuplicator<Filter, FilterCoefs>,
                              Gain<Type>, WaveShaper<Type>, Gain<Type>> processorChain;

    void reset() noexcept {
        processorChain.reset();
    }

private:
    //==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion)
};