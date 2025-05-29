#ifndef ACCELERATION_C_API_H
#define ACCELERATION_C_API_H

#include <stdint.h>
#include <stdbool.h>

// Forward declaration for the opaque pointer
#ifdef __cplusplus
struct Acceleration;
#else
typedef struct Acceleration Acceleration;
#endif

// This needs to match the dummy audioMasterCallback from your shim/audioeffectx.h
// It can be a simple void function if your C++ plugin doesn't strictly depend on its return value
// or arguments for core logic (only for VST host communication).
typedef int32_t (*audioMasterCallback_c)(void* effect, int32_t opcode, int32_t index, int32_t value, float opt, void* host_ptr);


#ifdef __cplusplus
extern "C" {
#endif

// Create and destroy functions for the Acceleration object
Acceleration* acceleration_new_shimmed(audioMasterCallback_c master_callback);
void acceleration_delete_shimmed(Acceleration* instance);

// Expose the core processing functions
void acceleration_process_replacing_shimmed(Acceleration* instance, float** inputs, float** outputs, int32_t sampleFrames);
void acceleration_process_double_replacing_shimmed(Acceleration* instance, double** inputs, double** outputs, int32_t sampleFrames);

// Expose parameter functions
float acceleration_get_parameter_shimmed(Acceleration* instance, int32_t index);
void acceleration_set_parameter_shimmed(Acceleration* instance, int32_t index, float value);
void acceleration_get_parameter_label_shimmed(Acceleration* instance, int32_t index, char* text);
void acceleration_get_parameter_name_shimmed(Acceleration* instance, int32_t index, char* text);
void acceleration_get_parameter_display_shimmed(Acceleration* instance, int32_t index, char* text);

// You can expose other VST-like functions if you want to call them,
// but remember they'll just hit the dummy implementations in your shim.
bool acceleration_get_effect_name_shimmed(Acceleration* instance, char* name);
// ... and so on for other methods you wish to interact with

#ifdef __cplusplus
}
#endif

#endif // ACCELERATION_C_API_H