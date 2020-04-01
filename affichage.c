#include "affichage.h"

void affichage(oxy myOxy){
    FILE* dataFile = NULL;

    if(access(LOCK_FILE, F_OK) != -1){  // Lock file exists
        printf("Data file already in use\n");   //displays an error message when the Data.txt file is already accessed
    }
    else{   // File doesn't exist
        FILE* lockFile = fopen(LOCK_FILE, "w");
        if (lockFile == NULL){  //if File could not be opened or created
            printf("%s could not be created\n", LOCK_FILE);    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        dataFile = fopen (DATA_FILE, "w");  //tries to open Data.txt creates the file if it doesn't exist
        if (dataFile == NULL){  //if File could not be opened or created
            printf("%s does not exist and could not be created\n", DATA_FILE);    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        fprintf(dataFile, "%d\n%d", myOxy.spo2, myOxy.pouls); //Prints spo2 and pulse in the dataFile file
        fclose(lockFile);
        fclose(dataFile);
        remove(LOCK_FILE);
    }
}

