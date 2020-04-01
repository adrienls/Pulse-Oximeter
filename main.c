#include <stdio.h>
#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"

#define SOURCE_FILE ("Tests/record1.dat")

int main() {
    FILE* data = initFichier(SOURCE_FILE);
    absorp signalValue, filteredSignal;
    oxy result;
    param_fir signalFIR = {0};
    param_irr signalIRR = {0};
    param_mesure signalMesure = {0};
    int state = 0;
    while(state != EOF){                //read all the file until we get an End Of File signal
        signalValue = lireFichier(data, &state);
        if(state == 6){                 //makes sure 6 values were read from the files (counts the two line breaks)
            filteredSignal = fir(&signalValue, &signalFIR);          //process the signal through an FIR filter
            filteredSignal = iir(&filteredSignal, &signalIRR);       //process the signal through an IRR filter
            result = mesure(&filteredSignal, &signalMesure);         //calculate the SPO2 measurement and the pulse from the signal
            affichage(result);                                      //display the result
        }
    }
    finFichier(data);
    return EXIT_SUCCESS;
}
