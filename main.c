#include <stdio.h>
#include "fichiers.h"
#include "integration.h"

#define SOURCE_FILE ("Tests/record1.dat")

int main() {
    FILE* data = initFichier(SOURCE_FILE);
    absorp signalValue;
    param_fir signalFIR = {0};
    param_irr signalIRR = {0};
    param_mesure signalMesure = {0};
    int state = 0;
    while(state != EOF){                //read all the file until we get an End Of File signal
        signalValue = lireFichier(data, &state);
        if(state == 6){                 //makes sure 6 values were read from the files (counts the two line breaks)
            integration(&signalValue, &signalFIR, &signalIRR, &signalMesure);   //calls all the processing functions and then display the result
        }
    }
    finFichier(data);
    return EXIT_SUCCESS;
}
