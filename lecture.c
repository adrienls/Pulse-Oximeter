#include <string.h>
#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state){

    absorp signal = {0};
    char c = 0, tmpStr[5] = "", line[21] = "";
    int state = 0;

    if(file_pf == NULL) {
        *file_state = EOF;
        return signal;
    }
    else{
        do {
            c = (char)fgetc(file_pf);
            if (c == ',' || c == '\n'){
                switch (state){
                    case 0:
                        signal.acr = (float)strtol(tmpStr, NULL, 10);
                        break;
                    case 1:
                        signal.dcr = (float)strtol(tmpStr, NULL, 10);

                        break;
                    case 2:
                        signal.acir = (float)strtol(tmpStr, NULL, 10);

                        break;
                    case 3:
                        signal.dcir = (float)strtol(tmpStr, NULL, 10);

                        break;
                    default:
                        break;
                }
                state++;
                state %= 4;
                strcpy(tmpStr,"");
            }
            else{
                strncat(tmpStr, &c, 1);
            }
        } while(c != '\r');

        printf("%f %f %f %f\n\n", signal.dcr, signal.acr, signal.acir, signal.dcir);
        fpos_t position;
        fgetpos(file_pf, &position);
        if(fread(line, 21, 1, file_pf) == 1){
            fsetpos(file_pf, &position);
        }
        else{
            *file_state = EOF;
        }
        return signal; // return EOF flat
    }
}