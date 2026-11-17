#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ScopiaAudioProcessorEditor : public juce::AudioProcessorEditor,
                                  private juce::Timer
{
public:
    explicit ScopiaAudioProcessorEditor (ScopiaAudioProcessor&);
    ~ScopiaAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    ScopiaAudioProcessor& audioProcessor;
    juce::Path waveformPath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopiaAudioProcessorEditor)
};