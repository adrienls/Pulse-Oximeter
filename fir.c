#include "fir.h"
#include "fichiers.h"

absorp firTest(char* filename){
    FILE* data = initFichier(filename);
    absorp signalValue, filteredValue = {0};
    int state = 0;
    param_fir signalFIR = {0};
    while(state != EOF){            //read all the file until we get an End Of File signal
        signalValue = lireFichier(data, &state);
        if(state == 6){             //makes sure 6 values were read from the files (counts the two line breaks)
            filteredValue = fir(&signalValue, &signalFIR);
        }
    }
	finFichier(data);
	return filteredValue;
}

absorp fir(absorp* signalValue, param_fir* signalFIR){
    const double FIR_TAPS[FIR_SIZE]={1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003, 7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};
    absorp filteredValue = *signalValue;    //DC values are not affected by the FIR filter
    filteredValue.acr = 0;
    filteredValue.acir = 0; //AC values are reset to 0 in order for the filter to recalculate them

    signalFIR->previousValues[signalFIR->index] = *signalValue; //add the new value to the array
    if(signalFIR->size < FIR_SIZE){
        signalFIR->size++;  //increases the size, which represents the number of value in the array, by one until it reaches the maximum
    }

    unsigned short i, currentIndex = signalFIR->index; //current index is initialized at the position of the new value we just added
    for (i = 0; i < signalFIR->size; i++) {
        //the first new value is the first fir coefficient times the newest value added
        //the index changes as new value are added, thanks to the modulo we can simulate a circular buffer
        filteredValue.acr += (float)(FIR_TAPS[i] * signalFIR->previousValues[currentIndex].acr);
        filteredValue.acir += (float)(FIR_TAPS[i] * signalFIR->previousValues[currentIndex].acir);
        currentIndex = (currentIndex == 0)? signalFIR->size-1 : currentIndex-1; //decreases the current index by one, or start again at the last value of the array if it is already equal to 0
    }

    signalFIR->index = (signalFIR->index + 1) % FIR_SIZE; //index increases every time a value is added and overrides the first value when it reaches the end of the array
    return filteredValue;
}

/*
 * Other way of implementing this function using queues
 *
absorp fir(absorp* signalValue, Queue* queue){
    const double FIR_TAPS[51]={1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003, 7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};
    unsigned short size = queueSize(queue); //the queue saves the input values from the sampling, the filtered value are the output
    absorp filteredValue = *signalValue;
    filteredValue.acr = 0;
    filteredValue.acir = 0;
    if(size == 51){                     //makes sure there is never more than 51 value in the queue
        DeQueue(queue);
    }
    EnQueue(queue, *signalValue);
    unsigned short i;
    for (i = 0; i < size; ++i) {
        //the first new value is the first fir coefficient times the last value of the queue, which is the newest added (index 50 = size - 1)
        //as the index of the coefficient (i) increases we each time times it by the older value (smaller index value in the queue)
        filteredValue.acr += (float)(FIR_TAPS[i] * getValue(queue, size-1-i).acr);
        filteredValue.acir += (float)(FIR_TAPS[i] * getValue(queue, size-1-i).acir);
    }
    return filteredValue;
}
 */