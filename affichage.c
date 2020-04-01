#include "affichage.h"

void affichage(oxy myOxy){
    FILE* data = NULL;

    if(access(LOCK_FILE, F_OK) != -1){  // Lock file exists
        printf("Data file already in use\n");   //displays an error message when the Data.txt file is already accessed
    }
    else{   // File doesn't exist
        FILE* verrou = fopen(LOCK_FILE, "w");
        if (verrou == NULL){  //if File could not be opened or created
            printf("%s could not be created\n", LOCK_FILE);    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
    data = fopen (DATA_FILE, "w");  //tries to open Data.txt creates the file if it doesn't exist
        if (data == NULL){  //if File could not be opened or created
            printf("%s does not exist and could not be created\n", DATA_FILE);    //displays an error message when Data.txt does not exist or could not be created
            exit(EXIT_FAILURE);
        }
        fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls); //Prints spo2 and pulse in the data file
        fclose(verrou);
        fclose(data);
        remove(LOCK_FILE);
    }
}

