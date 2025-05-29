// audioeffectx.i
%module(directors=0) audioeffectx_base // directors=0 often reduces some boilerplate related to callbacks back into C++

// Forward declare AEffect struct so audioMasterCallback can use it
%{
struct AEffect; // Forward declaration
#include "audioeffectx.h" // The actual C++ header for AudioEffectX and AEffect
%}

// --- Define VST specific types for SWIG ---
%include <stdint.h>
%typedef int32_t VstInt32;
%typedef int32_t VstPlugCategory;

// Define the C-compatible callback signature explicitly for SWIG
typedef int32_t (*audioMasterCallback_c)(struct AEffect *, int32_t, int32_t, int32_t, float, void *);
%typedef audioMasterCallback_c audioMasterCallback; // Map C++ audioMasterCallback to your C-compatible type

// --- Ignore all methods of AudioEffectX directly ---
// We don't want any methods of the base class to be wrapped directly.
%ignore AudioEffectX::dispatcher;
%ignore AudioEffectX::process;
%ignore AudioEffectX::processReplacing;
%ignore AudioEffectX::processDoubleReplacing;
%ignore AudioEffectX::setParameter;
%ignore AudioEffectX::getParameter;
%ignore AudioEffectX::setProgram;
%ignore AudioEffectX::getProgram;
%ignore AudioEffectX::getProgramName;
%ignore AudioEffectX::setProgramName;
%ignore AudioEffectX::getChunk;
%ignore AudioEffectX::setChunk;
%ignore AudioEffectX::canDo;
%ignore AudioEffectX::getParameterLabel;
%ignore AudioEffectX::getParameterName;
%ignore AudioEffectX::getParameterDisplay;
%ignore AudioEffectX::getEffectName; // Ignore this here, we'll wrap it via Acceleration
%ignore AudioEffectX::getPlugCategory; // Ignore this here

// Now, include the header for SWIG to parse the class itself, but its methods are ignored.
%include "audioeffectx.h"

// If AEffect itself is causing boilerplate, and you don't need its internal structure exposed
// beyond the function pointer signature, you might need to ignore it too, but be careful.
// %ignore AEffect;