#ifndef PULSE_OXIMETER_LECTURE_H
#define PULSE_OXIMETER_LECTURE_H

#include "define.h"

#define FRAME_SIZE (21)
#define FRAME_LAST_VALUE ('\r')

absorp lecture(FILE* file_pf, int* file_state);

#endif //PULSE_OXIMETER_LECTURE_H