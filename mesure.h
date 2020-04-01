#ifndef PULSE_OXIMETER_MESURE_H
#define PULSE_OXIMETER_MESURE_H

#include "define.h"
#include "queue.h"

typedef struct{
    float acrMax;
    float acrMin;
    float acirMax;
    float acirMin;

    unsigned int nbEch;
    absorp previousSignal;
    oxy processedResult;
} param_mesure;

oxy mesureTest(char* filename);
oxy mesure(absorp* signalValue, param_mesure* signalMesure);
oxy process(unsigned int nbEch, float acrPeakToPeak, float acirPeakToPeak, float dcr, float dcir);

#endif //PULSE_OXIMETER_MESURE_H