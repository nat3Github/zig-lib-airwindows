// acceleration.i
%module acceleration_c_api

// Include the base class's SWIG interface file to get type definitions
%include "audioeffectx.i"

// C++ headers for the generated wrapper's compilation
%{
#include "Acceleration.h" // Your actual plugin header
%}

// --- Typemaps for float** and double** ---
// This is the most complex part. We'll tell SWIG how to map C++ `float**` to a C pointer (e.g., `void*` or `float**`).
// For simplicity in the C API, you might treat these as `void*` and handle the casting in Zig.
// Or, if Zig can directly consume `float**`, you can keep it as is.
// For now, let's assume direct passing is fine and SWIG will attempt to pass through.
// If warnings persist for float**/double**, we'd need more complex typemaps.

// --- Define C-style functions using %inline or %extend ---
// %inline creates free C functions.
// %extend adds C functions that take a class pointer as the first argument.

%inline %{
    // Constructor
    Acceleration* acceleration_init(audioMasterCallback_c master_callback) {
        return new Acceleration(reinterpret_cast<audioMasterCallback>(master_callback));
    }

    // Destructor
    void acceleration_uninit(Acceleration* instance) {
        delete instance;
    }

    // processReplacing
    void acceleration_process_replacing_shimmed(Acceleration* instance, float** inputs, float** outputs, int32_t sampleFrames) {
        instance->processReplacing(inputs, outputs, sampleFrames);
    }

    // processDoubleReplacing
    void acceleration_process_double_replacing_shimmed(Acceleration* instance, double** inputs, double** outputs, int32_t sampleFrames) {
        instance->processDoubleReplacing(inputs, outputs, sampleFrames);
    }

    // getParameter
    float acceleration_get_parameter_shimmed(Acceleration* instance, int32_t index) {
        return instance->getParameter(index);
    }

    // setParameter
    void acceleration_set_parameter_shimmed(Acceleration* instance, int32_t index, float value) {
        instance->setParameter(index, value);
    }

    // getParameterLabel
    void acceleration_get_parameter_label_shimmed(Acceleration* instance, int32_t index, char* text) {
        instance->getParameterLabel(index, text);
    }

    // getParameterName
    void acceleration_get_parameter_name_shimmed(Acceleration* instance, int32_t index, char* text) {
        instance->getParameterName(index, text);
    }

    // getParameterDisplay
    void acceleration_get_parameter_display_shimmed(Acceleration* instance, int32_t index, char* text) {
        instance->getParameterDisplay(index, text);
    }
%}