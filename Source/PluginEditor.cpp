#include "PluginEditor.h"

ScopiaAudioProcessorEditor::ScopiaAudioProcessorEditor (ScopiaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (700, 320);
    startTimerHz (30);
}

ScopiaAudioProcessorEditor::~ScopiaAudioProcessorEditor()
{
    stopTimer();
}

void ScopiaAudioProcessorEditor::timerCallback()
{
    repaint();
}

void ScopiaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff0b0f14));

    auto area = getLocalBounds().reduced (12);
    auto titleArea = area.removeFromTop (28);
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (18.0f, juce::Font::bold));
    g.drawText ("SCOPIA", titleArea, juce::Justification::left, true);

    g.setColour (juce::Colour (0xff6b7280));
    g.setFont (juce::Font (12.0f));
    g.drawText ("Audio oscilloscope - by Aron H (https://www.instagram.com/aronh.official/)",
                titleArea, juce::Justification::right, true);

    auto plot = area.reduced (4);
    g.setColour (juce::Colour (0xff111827));
    g.fillRect (plot);
    g.setColour (juce::Colour (0xff1f2937));
    g.drawRect (plot, 1);

    // Build waveform path from the capture buffer.
    const int n = ScopiaAudioProcessor::waveformSize;
    const int pos = audioProcessor.writePosition.load();
    waveformPath.clear();
    bool first = true;
    for (int i = 0; i < n; ++i)
    {
        int idx = (pos + i) % n;
        float v = audioProcessor.waveform.getSample (0, idx);
        float x = plot.getX() + (float) i / (float) (n - 1) * (float) plot.getWidth();
        float y = plot.getCentreY() - v * (float) plot.getHeight() * 0.45f;
        if (first) { waveformPath.startNewSubPath (x, y); first = false; }
        else waveformPath.lineTo (x, y);
    }

    g.setColour (juce::Colour (0xff22d3ee));
    g.strokePath (waveformPath, juce::PathStrokeType (1.5f));
}

void ScopiaAudioProcessorEditor::resized() {}