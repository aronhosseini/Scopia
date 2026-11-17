#include "PluginProcessor.h"
#include "PluginEditor.h"

ScopiaAudioProcessor::ScopiaAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    waveform.setSize (1, waveformSize);
    waveform.clear();
}

ScopiaAudioProcessor::~ScopiaAudioProcessor() = default;

void ScopiaAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    waveform.clear();
    writePosition.store (0);
}

void ScopiaAudioProcessor::releaseResources() {}

void ScopiaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;

    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    // Pass audio through unchanged.
    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* data = buffer.getWritePointer (ch);
        for (int i = 0; i < numSamples; ++i)
            data[i] = data[i];
    }

    // Capture a mono mix into the waveform buffer.
    int pos = writePosition.load();
    for (int i = 0; i < numSamples; ++i)
    {
        float s = 0.0f;
        if (numChannels > 0)
        {
            for (int ch = 0; ch < numChannels; ++ch)
                s += buffer.getSample (ch, i);
            s /= (float) numChannels;
        }
        waveform.setSample (0, pos, s);
        pos = (pos + 1) % waveformSize;
    }
    writePosition.store (pos);
}

juce::AudioProcessorEditor* ScopiaAudioProcessor::createEditor()
{
    return new ScopiaAudioProcessorEditor (*this);
}

void ScopiaAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/) {}
void ScopiaAudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ScopiaAudioProcessor();
}