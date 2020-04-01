#ifndef PULSE_OXIMETER_AFFICHAGE_H
#define PULSE_OXIMETER_AFFICHAGE_H

#include "define.h"

#define LOCK_FILE (".verrouData")
#define DATA_FILE ("Data.txt")

void affichage(oxy myOxy); //Prints oxy data in a file , the format of the file is: spo2 pouls

#endif //PULSE_OXIMETER_AFFICHAGE_H