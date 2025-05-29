// acceleration_c_api.cpp
#include "acceleration_h.h"
#include "Acceleration.h" // Your original Acceleration.h

extern "C" {

Acceleration* acceleration_new_shimmed(audioMasterCallback_c master_callback) {
    // The cast below relies on the master_callback_c being compatible with
    // the audioMasterCallback type in your shim/audioeffectx.h.
    return new Acceleration(reinterpret_cast<audioMasterCallback>(master_callback));
}

void acceleration_delete_shimmed(Acceleration* instance) {
    delete instance;
}

void acceleration_process_replacing_shimmed(Acceleration* instance, float** inputs, float** outputs, int32_t sampleFrames) {
    instance->processReplacing(inputs, outputs, sampleFrames);
}

void acceleration_process_double_replacing_shimmed(Acceleration* instance, double** inputs, double** outputs, int32_t sampleFrames) {
    instance->processDoubleReplacing(inputs, outputs, sampleFrames);
}

float acceleration_get_parameter_shimmed(Acceleration* instance, int32_t index) {
    return instance->getParameter(index);
}

void acceleration_set_parameter_shimmed(Acceleration* instance, int32_t index, float value) {
    instance->setParameter(index, value);
}

void acceleration_get_parameter_label_shimmed(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterLabel(index, text);
}

void acceleration_get_parameter_name_shimmed(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterName(index, text);
}

void acceleration_get_parameter_display_shimmed(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterDisplay(index, text);
}

bool acceleration_get_effect_name_shimmed(Acceleration* instance, char* name) {
    return instance->getEffectName(name);
}

// ... continue for other methods you want to expose ...

} // extern "C"