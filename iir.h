#ifndef PULSE_OXIMETER_IRR_H
#define PULSE_OXIMETER_IRR_H

#include "define.h"

#define ALPHA (0.992)

typedef struct{
    absorp previousSignalValue;
    absorp previousFilteredValue;
} param_irr;

absorp iirTest(char* filename);
absorp iir(absorp* signalValue, param_irr* signalIRR);

#endif //PULSE_OXIMETER_IRR_H