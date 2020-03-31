#include "affichage.h"

void affichage(oxy myOxy){

    FILE* data = 0;

    if( access( ".verrouData", F_OK ) != -1 ){ // Lock file exists
        printf("Data file already in use\n");//displays an error message when the Data.txt file is already accessed
    }
    else{// File doesn't exist
        if(open(".verrouData", O_CREAT, S_IRUSR) == -1){ //Creates lock file and checks if it was created
            printf("Lock file could not be created\n");//displays an error message when the lock files's creation failed
            exit(EXIT_FAILURE);
        }
        data = fopen ("Data.txt", "w+"); //tries to open Data.txt creates the file if it doesn't exist
        if (data == NULL){ //if File could not be opened or created
            printf("Data file does not exist\n");//displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        fprintf(data, "%d%s%d", myOxy.spo2, "\n", myOxy.pouls); //Prints spo2 and pulse in the data file

        remove(".verrouData");
    }
}

