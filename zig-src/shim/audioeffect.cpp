// shim/audioeffect.cpp (Should be good from previous step)
#include "audioeffectx.h"
#include <iostream>
#include <stdio.h>

// Dummy implementation of the audioMasterCallback
VstInt32 dummyAudioMasterCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstInt32 value, float opt, void* ptr) {
    // std::cout << "Dummy audioMasterCallback called: opcode=" << opcode << std::endl;
    return 0;
}

// --- Utility Functions (Dummy Implementations) ---
// Mimic vst_strncpy
void vst_strncpy(char* dest, const char* src, VstInt32 maxLen) {
    if (dest && src) {
        strncpy(dest, src, maxLen);
        dest[maxLen - 1] = '\0'; // Ensure null-termination
    }
}

// Mimic float2string
void float2string(float value, char* text, VstInt32 maxLen) {
    if (text) {
        snprintf(text, maxLen, "%.2f", value); // Format as float with 2 decimal places
        text[maxLen - 1] = '\0'; // Ensure null-termination
    }
}


// --- AudioEffect Implementations ---
AudioEffect::AudioEffect(audioMasterCallback audioMaster) :
    fAudioMaster(audioMaster ? audioMaster : dummyAudioMasterCallback),
    fEffect(nullptr),
    fSampleRate(44100.0f),
    fBlockSize(512),
    fNumInputs(0),
    fNumOutputs(0),
    fUniqueID(0),
    fCanProcessReplacing(false),
    fCanDoubleReplacing(false),
    fProgramsAreChunks(false)
{
    fEffect = new AEffect();
    memset(fEffect, 0, sizeof(AEffect));
    fEffect->magic = 0x56737450; // 'VstP'
    fEffect->object = this;
}

AudioEffect::~AudioEffect() {
    delete fEffect;
    fEffect = nullptr;
}

void AudioEffect::setSampleRate(float sampleRate) { fSampleRate = sampleRate; }
float AudioEffect::getSampleRate() { return fSampleRate; }
void AudioEffect::setBlockSize(VstInt32 blockSize) { fBlockSize = blockSize; }
void AudioEffect::resume() {}
void AudioEffect::suspend() {}

void AudioEffect::process(float** inputs, float** outputs, VstInt32 sampleFrames) {}
void AudioEffect::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) {}
void AudioEffect::processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) {}

void AudioEffect::setParameter(VstInt32 index, float value) {}
float AudioEffect::getParameter(VstInt32 index) { return 0.f; }

VstInt32 AudioEffect::canDo(char* text) { return 0; }
VstInt32 AudioEffect::getNumMidiInputChannels() { return 0; }
VstInt32 AudioEffect::getNumMidiOutputChannels() { return 0; }
VstInt32 AudioEffect::getVendorVersion() { return 1000; }
bool AudioEffect::getVendorString(char* text) { if (text) strcpy(text, "Dummy Vendor"); return true; }
bool AudioEffect::getProductString(char* text) { if (text) strcpy(text, "Dummy Product"); return true; }
bool AudioEffect::getEffectName(char* name) { if (name) strcpy(name, "Dummy Effect"); return true; }
VstPlugCategory AudioEffect::getPlugCategory() { return kNoCategory; }
VstInt32 AudioEffect::getProgram() { return 0; }
void AudioEffect::setProgram(VstInt32 program) {}
void AudioEffect::getProgramName(char* name) { if (name) strcpy(name, "Dummy Program"); }
void AudioEffect::setProgramName(char* name) {}
void AudioEffect::getParameterLabel(VstInt32 index, char* label) { if (label) strcpy(label, "Unit"); }
void AudioEffect::getParameterDisplay(VstInt32 index, char* text) { if (text) strcpy(text, "0.0"); }
void AudioEffect::getParameterName(VstInt32 index, char* name) { if (name) strcpy(name, "Param"); }
VstInt32 AudioEffect::getChunk(void** data, bool isPreset) { if (data) *data = nullptr; return 0; }
VstInt32 AudioEffect::setChunk(void* data, VstInt32 byteSize, bool isPreset) { return 0; }
VstInt32 AudioEffect::getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text) { return 0; }
bool AudioEffect::setBypass(bool onOff) { return false; }

void AudioEffect::setNumInputs(VstInt32 numInputs) { fNumInputs = numInputs; }
void AudioEffect::setNumOutputs(VstInt32 numOutputs) { fNumOutputs = numOutputs; }
void AudioEffect::setUniqueID(VstInt32 uniqueID) { fUniqueID = uniqueID; }
void AudioEffect::canProcessReplacing() { fCanProcessReplacing = true; }
void AudioEffect::canDoubleReplacing() { fCanDoubleReplacing = true; }
void AudioEffect::programsAreChunks(bool val) { fProgramsAreChunks = val; }

VstInt32 AudioEffect::getMidiProgramName(VstInt32 channel, VstInt32 program, char* text) { return 0; }
bool AudioEffect::hasMidiPrograms() { return false; }
VstInt32 AudioEffect::getMidiProgramCategory(VstInt32 channel, VstInt32 program) { return 0; }
bool AudioEffect::hasMidiProgramCategory() { return false; }
bool AudioEffect::getMidiProgramWith  (VstInt32 channel, VstInt32 program, char* text) { return false; }
bool AudioEffect::getMidiProgramAtr  (VstInt32 channel, VstInt32 program, char* text) { return false; }
bool AudioEffect::getMidiProgramNameIndexed (VstInt32 channel, VstInt32 program, char* text, VstInt32 index, bool is  ) { return false; }
bool AudioEffect::copyProgram(VstInt32 index) { return false; }
bool AudioEffect::connectInput(VstInt32 index, bool state) { return false; }
bool AudioEffect::connectOutput(VstInt32 index, bool state) { return false; }
VstInt32 AudioEffect::getNumProgramCategories() { return 0; }
VstInt32 AudioEffect::getSpeakerArrangement(VstSpeakerArrangement** inputs, VstSpeakerArrangement** outputs) { return 0; }
VstInt32 AudioEffect::setSpeakerArrangement(VstSpeakerArrangement* inputs, VstSpeakerArrangement* outputs) { return 0; }
VstInt32 AudioEffect::getTailSize() { return 0; }
bool AudioEffect::getEffectInfo(char* name, char* vendor, char* product, VstInt32* version, VstInt32* uniqueID, VstInt32* numInputs, VstInt32* numOutputs, VstInt32* flags) { return false; }
VstInt32 AudioEffect::getVstVersion() { return 2400; }
VstInt32 AudioEffect::getEditorRect(void** rect) { return 0; }
VstInt32 AudioEffect::open() { return 0; }
VstInt32 AudioEffect::close() { return 0; }