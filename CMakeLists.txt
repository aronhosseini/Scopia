cmake_minimum_required(VERSION 3.22)
project(Scopia VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED JUCE_MODULES_PATH)
    set(JUCE_MODULES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules" CACHE PATH "Path to JUCE modules")
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/JUCE" EXCLUDE_FROM_ALL)

juce_add_plugin(Scopia
    COMPANY_NAME "Aron H"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Aron
    PLUGIN_CODE Scop
    FORMATS VST3 Standalone
    PRODUCT_NAME "Scopia"
)

juce_generate_juce_header(Scopia)

target_sources(Scopia PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_compile_definitions(Scopia PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(Scopia PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)