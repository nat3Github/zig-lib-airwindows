// shim/audioeffectx.h (Final revisions for utility functions)
#ifndef __AUDIOEFFECTX_H__
#define __AUDIOEFFECTX_H__

#include <stdint.h> // For VstInt32, VstInt64, etc.
#include <string.h> // For memset, strcpy, etc.

// --- VST Type Definitions (Minimal but sufficient for compilation) ---
typedef int32_t VstInt32;
typedef int64_t VstInt64;
typedef float VstFloat;
typedef double VstDouble;

// Dummy VST constants
enum {
    kVstMaxProgNameLen = 24,
    kVstMaxParamStrLen = 8,
    kVstMaxLabelLen = 64,
    kVstMaxVendorStrLen = 64,
    kVstMaxProductStrLen = 64,
    kVstMaxEffectNameLen = 64,
    kVstMaxCategoryStrLen = 24,
    kVstMaxChunkSize = 8192, // A reasonable dummy value
};

// Dummy VstPlugCategory enum
enum VstPlugCategory {
    kNoCategory = 0,
    kEffect,
    kSynth,
    kSendFx,
    kFx,
    kGenerator,
    kAnalyser,
    kMastering,
    kNumPlugCategories // This is often used by VST hosts
};

// Define kPlugCategEffect as it's used in Acceleration.cpp
const VstPlugCategory kPlugCategEffect = kEffect;

// Dummy VstSpeakerArrangement (if your plugin uses it)
struct VstSpeakerArrangement {};


// --- Utility Functions (Declarations) ---
// These are functions typically provided by the VST SDK or a helper library.
// We declare them here so Acceleration.cpp can find them.
void vst_strncpy(char* dest, const char* src, VstInt32 maxLen);
void float2string(float value, char* text, VstInt32 maxLen);


// --- Dummy AEffect struct ---
struct AEffect {
    VstInt32 magic;
    void* object;
    VstInt32 (*dispatcher)(AEffect* effect, VstInt32 opcode, VstInt32 index, VstInt32 value, float opt, void* ptr);
    void (*process)(AEffect* effect, float** inputs, float** outputs, VstInt32 sampleFrames);
    void (*processReplacing)(AEffect* effect, float** inputs, float** outputs, VstInt32 sampleFrames);
    void (*setParameter)(AEffect* effect, VstInt32 index, float value);
    float (*getParameter)(AEffect* effect, VstInt32 index);

    VstInt32 numPrograms;
    VstInt32 numParams;
    VstInt32 numInputs;
    VstInt32 numOutputs;
    VstInt32 flags;
    VstInt32 res1;
    VstInt32 res2;
    VstInt32 uniqueID;
    VstInt32 version;
};

// --- Dummy audioMasterCallback signature ---
typedef VstInt32 (*audioMasterCallback)(AEffect* effect, VstInt32 opcode, VstInt32 index, VstInt32 value, float opt, void* ptr);


// --- Dummy AudioEffect Base Class ---
class AudioEffect {
public:
    AudioEffect(audioMasterCallback audioMaster);
    virtual ~AudioEffect();

    // --- Core VST Plugin Lifecycle/Processing ---
    virtual void setSampleRate(float sampleRate);
    virtual float getSampleRate();
    virtual void setBlockSize(VstInt32 blockSize);
    virtual void resume();
    virtual void suspend();

    // Main audio processing methods
    virtual void process(float** inputs, float** outputs, VstInt32 sampleFrames);
    virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
    virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

    // Parameter handling
    virtual void setParameter(VstInt32 index, float value);
    virtual float getParameter(VstInt32 index);

    // --- VST Host Communication (via audioMasterCallback) ---
    virtual VstInt32 canDo(char* text);
    virtual VstInt32 getNumMidiInputChannels();
    virtual VstInt32 getNumMidiOutputChannels();
    virtual VstInt32 getVendorVersion();
    virtual bool getVendorString(char* text);
    virtual bool getProductString(char* text);
    virtual bool getEffectName(char* name);
    virtual VstPlugCategory getPlugCategory();
    virtual VstInt32 getProgram();
    virtual void setProgram(VstInt32 program);
    virtual void getProgramName(char* name);
    virtual void setProgramName(char* name);
    virtual void getParameterLabel(VstInt32 index, char* label);
    virtual void getParameterDisplay(VstInt32 index, char* text);
    virtual void getParameterName(VstInt32 index, char* name);
    virtual VstInt32 getChunk(void** data, bool isPreset);
    virtual VstInt32 setChunk(void* data, VstInt32 byteSize, bool isPreset);
    virtual VstInt32 getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text);
    virtual bool setBypass(bool onOff);

    // Methods called during Acceleration constructor/init
    virtual void setNumInputs(VstInt32 numInputs);
    virtual void setNumOutputs(VstInt32 numOutputs);
    virtual void setUniqueID(VstInt32 uniqueID);
    virtual void canProcessReplacing();
    virtual void canDoubleReplacing();
    virtual void programsAreChunks(bool val);

    // Other less common but existing virtual methods
    virtual VstInt32 getMidiProgramName(VstInt32 channel, VstInt32 program, char* text);
    virtual bool hasMidiPrograms();
    virtual VstInt32 getMidiProgramCategory(VstInt32 channel, VstInt32 program);
    virtual bool hasMidiProgramCategory();
    virtual bool getMidiProgramWith  (VstInt32 channel, VstInt32 program, char* text);
    virtual bool getMidiProgramAtr  (VstInt32 channel, VstInt32 program, char* text);
    virtual bool getMidiProgramNameIndexed (VstInt32 channel, VstInt32 program, char* text, VstInt32 index, bool is  );
    virtual bool copyProgram(VstInt32 index);
    virtual bool connectInput(VstInt32 index, bool state);
    virtual bool connectOutput(VstInt32 index, bool state);
    virtual VstInt32 getNumProgramCategories();
    virtual VstInt32 getSpeakerArrangement(VstSpeakerArrangement** inputs, VstSpeakerArrangement** outputs);
    virtual VstInt32 setSpeakerArrangement(VstSpeakerArrangement* inputs, VstSpeakerArrangement* outputs);
    virtual VstInt32 getTailSize();
    virtual bool getEffectInfo(char* name, char* vendor, char* product, VstInt32* version, VstInt32* uniqueID, VstInt32* numInputs, VstInt32* numOutputs, VstInt32* flags);
    virtual VstInt32 getVstVersion();
    virtual VstInt32 getEditorRect(void** rect);
    virtual VstInt32 open();
    virtual VstInt32 close();

protected:
    audioMasterCallback fAudioMaster;
    AEffect* fEffect;
    float fSampleRate;
    VstInt32 fBlockSize;
    VstInt32 fNumInputs;
    VstInt32 fNumOutputs;
    VstInt32 fUniqueID;
    bool fCanProcessReplacing;
    bool fCanDoubleReplacing;
    bool fProgramsAreChunks;
};


// --- Dummy AudioEffectX Class ---
class AudioEffectX : public AudioEffect {
public:
    AudioEffectX(audioMasterCallback audioMaster, VstInt32 numPrograms, VstInt32 numParameters)
        : AudioEffect(audioMaster)
    {
        fEffect->numPrograms = numPrograms;
        fEffect->numParams = numParameters;
    }
    virtual ~AudioEffectX() {}
};

#endif // __AUDIOEFFECTX_H__