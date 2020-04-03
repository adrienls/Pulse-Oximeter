#include <string.h>
#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state){

    absorp signal = {0};

    if (file_pf == NULL) {  //makes sure the file to read is valid
        *file_state = EOF;
    }
    else {
        char c, invalidFrame = 1, tmpStr[FRAME_SIZE];
        unsigned short i;

        while(invalidFrame == 1) {                          //makes sure a valid frame has been read
            invalidFrame = 0, c = 0;                        //considers the frame as valid by default, the value will be modified if the size of the frame is not right
            strcpy(tmpStr, "");                         //reset to an empty string the buffer

            for (i = 0; c != FRAME_LAST_VALUE; i++) {       //go through every character of the frame
                c = (char)fgetc(file_pf);                   //saves each character
                if(c == EOF){                               //stops the reading of the file if we arrive to the end
                    *file_state = EOF;
                    return signal;
                }
                tmpStr[i] = c;                              //save the character in the buffer
            }
            *file_state = FRAME_NB_VALUE;

            if(i != FRAME_SIZE){                            //if i is different from the frame size then the frame is not valid and we need to take the next one
                invalidFrame = 1;
            }
        }

        //Convert each character to the corresponding float value
        //the -48 is the difference between a number and its ascii value
        signal.acr = (float)((tmpStr[0] - 48) * 1000 + (tmpStr[1] - 48) * 100 + (tmpStr[2] - 48) * 10 + (tmpStr[3] - 48));
        signal.dcr = (float)((tmpStr[5] - 48) * 1000 + (tmpStr[6] - 48) * 100 + (tmpStr[7] - 48) * 10 + (tmpStr[8] - 48));
        signal.acir = (float)((tmpStr[10] - 48) * 1000 + (tmpStr[11] - 48) * 100 + (tmpStr[12] - 48) * 10 + (tmpStr[13] - 48));
        signal.dcir = (float)((tmpStr[15] - 48) * 1000 + (tmpStr[16] - 48) * 100 + (tmpStr[17] - 48) * 10 + (tmpStr[18] - 48));

        signal.acir -= 2048;    //ac values go from 0 to 4095, so there are 4096 values
        signal.acr -= 2048;     //to subtract 2048 (half of the number of values) from the current value enables us to center ac values around 0
    }
    return signal; // return EOF flat
}