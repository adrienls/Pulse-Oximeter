#ifndef PULSE_OXIMETER_IRR_H
#define PULSE_OXIMETER_IRR_H

#include "define.h"
#include "queue.h"

#define alpha (0.992)

absorp iirTest(char* filename);
absorp iir(absorp* signalValue, Queue* queue, absorp* previousFilteredValue);

#endif //PULSE_OXIMETER_IRR_H