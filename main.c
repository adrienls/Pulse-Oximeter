#include <stdio.h>
#include "fichiers.h"
#include "affichage.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"

int main() {
    int state=0;
    absorp myAbsorp;
    oxy myOxy = {76, 84};
    /*
    param_fir* myFIR = init_fir(...); // init FIR
    param_iir* myIIR = init_iir(...); // init IIR
    param_mesure* myMes = param_mesure(...) // init mesure
    FILE* myFile = initFichier("record1.dat");
    do{
        myAbsorp = lireFichier(myFile,&state);
        myAbsorp = fir(myAbsorp,myFIR);
        myAbsorp = iir(myAbsorp,myIIR);
        myOxy = mesure(myAbsorp,myMes);
        affichage(myOxy);
    }while(state != EOF);
    finFichier(myFile);
    fin_mesure(myMes);
    fin_iir(myIIR);
    fin_fir(myFIR) ;
     */
    //affichage(myOxy);
    myAbsorp = firTest("Tests/record1.dat");
    printf("After FIR Filter, myAbsorp is:\nACr: %d - DCr: %d - ACir: %d - DCir: %d\n", (int)myAbsorp.acr, (int)myAbsorp.dcr, (int)myAbsorp.acir, (int)myAbsorp.dcir);

    /*myOxy = mesureTest("Tests/record1_iir.dat");
    char pourcentage = '%';
    printf("SPO2 is: %d%c - Pulse is: %d\n", myOxy.spo2, pourcentage, myOxy.pouls);*/
    return EXIT_SUCCESS;
}
