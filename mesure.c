#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
    FILE* data = initFichier(filename);
    absorp signalValue;
    oxy processedOxy = {0};
    param_mesure signalMesure = {0};
    int state = 0;
    while(state != EOF){            //read all the file until we get an End Of File signal
        signalValue = lireFichier(data, &state);
        if(state == 6){             //makes sure 6 values were read from the files (counts the two line breaks)
            processedOxy = mesure(&signalValue, &signalMesure);
        }
    }
    finFichier(data);
    return processedOxy;
}

oxy mesure(absorp* signalValue, param_mesure* signalMesure){
    if(signalMesure->previousSignal.acr < 0 && signalValue->acr >= 0){  //detects a new rising edge crossing 0, which indicates a new period
        signalMesure->processedResult = process(signalMesure->nbEch, signalMesure->acrMax - signalMesure->acrMin, signalMesure->acirMax - signalMesure->acirMin,signalValue->dcr, signalValue->dcir);

        signalMesure->processedResult.pouls = pulseAverage(&signalMesure->previousPulse, signalMesure->processedResult.pouls);  //takes the average of the last pulse values

        signalMesure->acrMax = 0;
        signalMesure->acirMax = 0;
        signalMesure->acrMin = 0;
        signalMesure->acirMin = 0;
        signalMesure->nbEch = 0;        //reset of all the value in order to calculate the right oxy for the new period
    }
    signalMesure->nbEch++;  //increments the number of value per period
    if(signalValue->acr > signalMesure->acrMax){    //depending on the current value, change the saved maximum for acr
        signalMesure->acrMax = signalValue->acr;
    }
    if(signalValue->acir > signalMesure->acirMax){  //depending on the current value, change the saved maximum for acir
        signalMesure->acirMax = signalValue->acir;
    }
    if(signalValue->acr < signalMesure->acrMin){    //depending on the current value, change the saved minimum for acr
        signalMesure->acrMin = signalValue->acr;
    }
    if(signalValue->acir < signalMesure->acirMin){  //depending on the current value, change the saved minimum for acir
        signalMesure->acirMin = signalValue->acir;
    }

    signalMesure->previousSignal = *signalValue;
    return signalMesure->processedResult;
}

oxy process(unsigned int nbEch, float acrPeakToPeak, float acirPeakToPeak, float dcr, float dcir){
    oxy calculated = {0};
    float RsIR = (acrPeakToPeak / dcr) / (acirPeakToPeak / dcir);   //calculation of the ratio
    if(RsIR <= 1){  //the equation of spo2 is different depending on the value of RsIR
        calculated.spo2 = (unsigned short)(110 - 25*RsIR);
    }
    else{
        calculated.spo2 = (unsigned short)(120.42 - 35.42*RsIR);
    }
    calculated.pouls = (unsigned short)(60/(nbEch*SAMPLE_FREQUENCY)); //the pulse is one over the number of values times the sample frequency, then multiplied by 60 to have it per minute
    return calculated;
}

unsigned short pulseAverage(pulse_average* pulseValue, unsigned short newPulse){
    pulseValue->previousPulse[pulseValue->index] = newPulse; //add the new value to the array
    if(pulseValue->size < NB_PERIOD_AVERAGE){
        pulseValue->size++;  //increases the size, which represents the number of value in the array, by one until it reaches the maximum
    }

    unsigned short i, currentIndex = pulseValue->index;
    for(i = 0; i < pulseValue->size - 1; i++){  //goes through every value of the array
        newPulse += pulseValue->previousPulse[currentIndex];    //sums up the pulse value
        currentIndex = (pulseValue->index + 1) % NB_PERIOD_AVERAGE; //makes sure the index increases but never goes over the size of the array
    }
    newPulse /= pulseValue->size;   //divide the sum by the number of pulse to obtain the average

    pulseValue->index = (pulseValue->index + 1) % NB_PERIOD_AVERAGE; //index increases every time a value is added and overrides the first value when it reaches then en of the array
    return newPulse;
}


/*
 * Other way of doing this function, but actualizing the oxy value every half period instead of every period
 *
oxy mesure(absorp* signalValue, absorp* previousValue, param_mesure* signalMesure, oxy* previousOxy){

    if(previousValue->acr < 0 && signalValue->acr >= 0){
        signalMesure->risingEdge = 1;

        oxy result = process(signalMesure->nbEchUp + signalMesure->nbEchDown, signalMesure->acrMax - signalMesure->acrMin, signalMesure->acirMax - signalMesure->acirMin,signalValue->dcr, signalValue->dcir);
        signalMesure->acrMax = 0;
        signalMesure->acirMax = 0;
        signalMesure->nbEchUp = 1;
        return result;
    }
    else if(previousValue->acr > 0 && signalValue->acr <= 0){
        signalMesure->risingEdge = 0;

        oxy result = process(signalMesure->nbEchUp + signalMesure->nbEchDown, signalMesure->acrMax - signalMesure->acrMin, signalMesure->acirMax - signalMesure->acirMin,signalValue->dcr, signalValue->dcir);
        signalMesure->acrMin = 0;
        signalMesure->acirMin = 0;
        signalMesure->nbEchDown = 1;
        return result;
    }

    if(signalMesure->risingEdge == 1){
        signalMesure->nbEchUp++;
        if(signalValue->acr > signalMesure->acrMax){
            signalMesure->acrMax = signalValue->acr;
        }
        if(signalValue->acir > signalMesure->acirMax){
            signalMesure->acirMax = signalValue->acir;
        }
    }
    else if (signalMesure->risingEdge == 0){
        signalMesure->nbEchDown++;
        if(signalValue->acr < signalMesure->acrMin){
            signalMesure->acrMin = signalValue->acr;
        }
        if(signalValue->acir < signalMesure->acirMin){
            signalMesure->acirMin = signalValue->acir;
        }
    }
    return *previousOxy;
}
 */