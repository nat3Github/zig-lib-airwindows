#ifndef Acceleration_C_API_H
#define Acceleration_C_API_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
struct Acceleration;
#else
typedef struct Acceleration Acceleration;
#endif

typedef int32_t (*audioMasterCallback_c)(void *effect, int32_t opcode,
                                         int32_t index, int32_t value,
                                         float opt, void *host_ptr);

#ifdef __cplusplus
extern "C" {
#endif

extern const int Acceleration_KNUM_PROGRAMS;
extern const int Acceleration_KNUM_INPUTS;
extern const int Acceleration_KNUM_OUTPUTS;
extern const int Acceleration_KNUM_PARAMETERS;

Acceleration *Acceleration_init(audioMasterCallback_c master_callback);
void Acceleration_uninit(Acceleration *instance);

void Acceleration_process_replacing(Acceleration *instance, float **inputs,
                                    float **outputs, int32_t sampleFrames);
void Acceleration_process_double_replacing(Acceleration *instance,
                                           double **inputs, double **outputs,
                                           int32_t sampleFrames);

float Acceleration_get_parameter(Acceleration *instance, int32_t index);
void Acceleration_set_parameter(Acceleration *instance, int32_t index,
                                float value);
void Acceleration_get_parameter_label(Acceleration *instance, int32_t index,
                                      char *text);
void Acceleration_get_parameter_name(Acceleration *instance, int32_t index,
                                     char *text);
void Acceleration_get_parameter_display(Acceleration *instance, int32_t index,
                                        char *text);

#ifdef __cplusplus
}
#endif

#endif