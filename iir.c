#include "iir.h"
#include "fichiers.h"


absorp iirTest(char* filename){
    FILE* data = initFichier(filename);
    absorp signalValue, filteredValue = {0};
    param_irr signalIRR = {0};
    int state = 0;
    while(state != EOF){                //read all the file until we get an End Of File signal
        signalValue = lireFichier(data, &state);
        if(state == 6){                 //makes sure 6 values were read from the files (counts the two line breaks)
            filteredValue = iir(&signalValue, &signalIRR);
        }
    }
    finFichier(data);
    return filteredValue;
}

absorp iir(absorp* signalValue, param_irr* signalIRR){
    absorp filteredValue = *signalValue;    //DC values are not affected by the FIR filter

    if(signalIRR->previousFilteredValue.acr != 0 && signalIRR->previousSignalValue.acr != 0){
        filteredValue.acr = (float)(signalValue->acr - signalIRR->previousSignalValue.acr + ALPHA * signalIRR->previousFilteredValue.acr);
        filteredValue.acir = (float)(signalValue->acir - signalIRR->previousSignalValue.acir + ALPHA * signalIRR->previousFilteredValue.acir);
    }

    signalIRR->previousSignalValue = *signalValue;
    signalIRR->previousFilteredValue = filteredValue;
    return filteredValue;
}

/*
 * Other way of implementing this function using queues
 *
absorp iir(absorp* signalValue, Queue* queue, absorp* previousFilteredValue){
    unsigned short size = queueSize(queue); //the queue saves the input values from the sampling, the filtered value are the output
    absorp filteredValue = *signalValue;
    filteredValue.acr = 0;
    filteredValue.acir = 0;
    if(size > 0){                           //makes sure there is at least one value in the queue
        if(size == 2) {
            DeQueue(queue);                 //makes sure there is never more than 2 value in the queue
        }
        EnQueue(queue, *signalValue);
        //the new value is equal to the newest one in the queue (index 1) minus the oldest one (index 0) plus alpha times the previous irr value
        filteredValue.acr = (float)(getValue(queue, 1).acr - getValue(queue, 0).acr + ALPHA * previousFilteredValue->acr);
        filteredValue.acir = (float)(getValue(queue, 1).acir - getValue(queue, 0).acir + ALPHA * previousFilteredValue->acir);
        return filteredValue;
    }
    else{                                   //spcecial case if it is the first value to be calculated
        EnQueue(queue, *signalValue);
        return *signalValue;
    }
}
 */