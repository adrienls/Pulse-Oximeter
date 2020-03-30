#include "iir.h"
#include "fichiers.h"


absorp iirTest(char* filename){
    FILE* data = initFichier(filename);
    absorp filteredValue = {0, 0, 0, 0}, signalValue;
    int state = 0;
    Queue* queue = CreateQueue();
    while(state != EOF){
        signalValue = lireFichier(data, &state);
        if(state == 6){
            filteredValue = iir(&signalValue, queue, &filteredValue);
        }
    }
    DeleteQueue(queue);
    finFichier(data);
    return filteredValue;
}

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
        filteredValue.acr = (float)(getValue(queue, 1).acr - getValue(queue, 0).acr + alpha * previousFilteredValue->acr);
        filteredValue.acir = (float)(getValue(queue, 1).acir - getValue(queue, 0).acir + alpha * previousFilteredValue->acir);
        return filteredValue;
    }
    else{                                   //spcecial case if it is the first value to be calculated
        EnQueue(queue, *signalValue);
        return *signalValue;
    }
}