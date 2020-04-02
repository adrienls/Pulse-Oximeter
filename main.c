#include <stdio.h>
#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"
#include "lecture.h"
#include "integration.h"

#define LECTURE_TEST_FILE ("Tests/record1_bin.dat")
#define INTEGRATION_TEST_FILE ("Tests/record1.dat")

void lectureTest(char* filename){
    int state = 0;
    FILE* data = initFichier(filename);
    while(state != EOF){
        lecture(data, &state);
    }
    finFichier(data);
}

int main() {
    lectureTest(LECTURE_TEST_FILE);
    integrationTest(INTEGRATION_TEST_FILE);
    return EXIT_SUCCESS;
}
