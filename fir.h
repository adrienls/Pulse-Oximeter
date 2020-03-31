#ifndef PULSE_OXIMETER_FIR_H
#define PULSE_OXIMETER_FIR_H

#include "define.h"
#include "queue.h"

absorp firTest(char* filename);
absorp fir(absorp* signalValue, Queue* queue);

#endif //PULSE_OXIMETER_FIR_H