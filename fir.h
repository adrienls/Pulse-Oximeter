#ifndef PULSE_OXIMETER_FIR_H
#define PULSE_OXIMETER_FIR_H

#include "define.h"

#define FIR_SIZE (51)

typedef struct{
    unsigned short index;
    unsigned short size;
    absorp previousValues[FIR_SIZE];
} param_fir;

absorp firTest(char* filename);
absorp fir(absorp* signalValue, param_fir* signalFIR);

#endif //PULSE_OXIMETER_FIR_H