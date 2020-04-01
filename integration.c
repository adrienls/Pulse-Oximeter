#include "integration.h"
#include "fichiers.h"
#include "affichage.h"

void integrationTest(char* filename){
    FILE* data = initFichier(filename);
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
}

void integration(absorp* signalValue, param_fir* signalFIR, param_irr* signalIRR, param_mesure* signalMesure){
    absorp filteredSignal = fir(signalValue, signalFIR);    //process the signal through an FIR filter
    filteredSignal = iir(&filteredSignal, signalIRR);       //process the signal through an IRR filter
    oxy result = mesure(&filteredSignal, signalMesure);     //calculate the SPO2 measurement and the pulse from the signal
    affichage(result);                                      //display the result
}