#ifndef PULSE_OXIMETER_MESURE_H
#define PULSE_OXIMETER_MESURE_H

#include "define.h"

#define SAMPLE_FREQUENCY (0.002)
#define NB_PERIOD_AVERAGE (10)

typedef struct{
    unsigned short index;
    unsigned short size;
    unsigned short previousPulse[NB_PERIOD_AVERAGE];
} pulse_average;

typedef struct{
    float acrMax;
    float acrMin;
    float acirMax;
    float acirMin;

    unsigned int nbEch;
    pulse_average previousPulse;
    absorp previousSignal;
    oxy processedResult;
} param_mesure;

oxy mesureTest(char* filename);
oxy mesure(absorp* signalValue, param_mesure* signalMesure);
oxy process(unsigned int nbEch, float acrPeakToPeak, float acirPeakToPeak, float dcr, float dcir);
unsigned short pulseAverage(pulse_average* pulseValue, unsigned short newPulse);

#endif //PULSE_OXIMETER_MESURE_H