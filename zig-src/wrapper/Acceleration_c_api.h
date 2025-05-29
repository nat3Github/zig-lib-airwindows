#ifndef Acceleration_C_API_H
#define Acceleration_C_API_H

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

extern const int Acceleration_KNUM_PROGRAMS;
extern const int Acceleration_KNUM_INPUTS;
extern const int Acceleration_KNUM_OUTPUTS;
extern const int Acceleration_KNUM_PARAMETERS;

// Create and destroy functions for the Acceleration object
Acceleration* Acceleration_init(audioMasterCallback_c master_callback);
void Acceleration_uninit(Acceleration* instance);

// Expose the core processing functions
void Acceleration_process_replacing(Acceleration* instance, float** inputs, float** outputs, int32_t sampleFrames);
void Acceleration_process_double_replacing(Acceleration* instance, double** inputs, double** outputs, int32_t sampleFrames);

// Expose parameter functions
float Acceleration_get_parameter(Acceleration* instance, int32_t index);
void Acceleration_set_parameter(Acceleration* instance, int32_t index, float value);
void Acceleration_get_parameter_label(Acceleration* instance, int32_t index, char* text);
void Acceleration_get_parameter_name(Acceleration* instance, int32_t index, char* text);
void Acceleration_get_parameter_display(Acceleration* instance, int32_t index, char* text);

#ifdef __cplusplus
}
#endif

#endif // Acceleration_C_API_H