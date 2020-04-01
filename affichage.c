#include "affichage.h"

void affichage(oxy myOxy){
    FILE* data = NULL;

    if(access(".verrouData", F_OK) != -1){  // Lock file exists
        printf("Data file already in use\n");   //displays an error message when the Data.txt file is already accessed
    }
    else{   // File doesn't exist
        FILE* verrou = fopen(".verrouData", "w");
        if (verrou == NULL){  //if File could not be opened or created
            printf(".verrouData could not be created\n");    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        data = fopen ("Data.txt", "w");  //tries to open Data.txt creates the file if it doesn't exist
        if (data == NULL){  //if File could not be opened or created
            printf("Data file does not exist and could not be created\n");    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls); //Prints spo2 and pulse in the data file
        fclose(verrou);
        fclose(data);
        remove(".verrouData");
    }
}

