#pragma once

#include <JuceHeader.h>

class ScopiaAudioProcessor : public juce::AudioProcessor
{
public:
    ScopiaAudioProcessor();
    ~ScopiaAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Scopia"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Waveform capture buffer (single channel, fixed size)
    static constexpr int waveformSize = 2048;
    juce::AudioBuffer<float> waveform;
    std::atomic<int> writePosition { 0 };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopiaAudioProcessor)
};