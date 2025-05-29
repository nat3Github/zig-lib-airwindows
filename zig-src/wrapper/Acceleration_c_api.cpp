#include "Acceleration_c_api.h"
#include "Acceleration.h" 

extern "C" {
const int Acceleration_KNUM_PROGRAMS = kNumPrograms;
const int Acceleration_KNUM_INPUTS = kNumInputs;
const int Acceleration_KNUM_OUTPUTS = kNumOutputs;
const int Acceleration_KNUM_PARAMETERS = kNumParameters;

Acceleration* Acceleration_init(audioMasterCallback_c master_callback) {
    return new Acceleration(reinterpret_cast<audioMasterCallback>(master_callback));
}

void Acceleration_uninit(Acceleration* instance) {
    delete instance;
}

void Acceleration_process_replacing(Acceleration* instance, float** inputs, float** outputs, int32_t sampleFrames) {
    instance->processReplacing(inputs, outputs, sampleFrames);
}

void Acceleration_process_double_replacing(Acceleration* instance, double** inputs, double** outputs, int32_t sampleFrames) {
    instance->processDoubleReplacing(inputs, outputs, sampleFrames);
}

float Acceleration_get_parameter(Acceleration* instance, int32_t index) {
    return instance->getParameter(index);
}

void Acceleration_set_parameter(Acceleration* instance, int32_t index, float value) {
    instance->setParameter(index, value);
}

void Acceleration_get_parameter_label(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterLabel(index, text);
}

void Acceleration_get_parameter_name(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterName(index, text);
}

void Acceleration_get_parameter_display(Acceleration* instance, int32_t index, char* text) {
    instance->getParameterDisplay(index, text);
}

} // extern "C"