#ifndef PULSE_OXIMETER_INTEGRATION_H
#define PULSE_OXIMETER_INTEGRATION_H

#include "define.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"

void integrationTest(char* filename);
void integration(absorp* signalValue, param_fir* signalFIR, param_irr* signalIRR, param_mesure* signalMesure);

#endif //PULSE_OXIMETER_INTEGRATION_H