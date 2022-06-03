#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

static GrafoHotel *CaricaVetHotel(FILE **file,int dim){
    GrafoHotel *albergo=NULL;
    albergo = (GrafoHotel *) malloc(sizeof(GrafoHotel));
    albergo->indice = 0;
    albergo->dim = dim;
    albergo->hotel=NULL;
    if (dim!=0) {
        albergo->hotel = (Hotel **) malloc (dim * sizeof(Hotel*));
        for (int j=0;j<dim;j++){
            albergo->hotel[j]=(Hotel*) malloc(sizeof (Hotel));
        }
        char citta[LenC];
        float prezzo;
        for (int i = 0; i < dim; i++) {
            fscanf(*file, "%s%f", citta, &prezzo);
            albergo->hotel[i]->prezzo = prezzo;
            printf("\n%d", i);
            strcpy(albergo->hotel[i]->nome, citta);
            printf("->%s %.2f",albergo->hotel[i]->nome,albergo->hotel[i]->prezzo);
        }
    }
    return albergo;
}

static void CaricaCittaHotel(AlberoCitta *radice, FILE **file){
    AlberoCitta *citta;
    int errore=0;
    char cittadafile[LenC];
    int dim;
    while (fscanf(*file, "%s%d", cittadafile, &dim)==2) {
        citta = CercaNodo(radice, cittadafile, &errore);
        //printf("%s",citta->citta->nome); FUNZIONA
        citta->citta->Grafohotel = CaricaVetHotel(file, dim);
        //printf("\n%s->%s",citta->citta->nome,citta->citta->hotel->hotel[0]->nome);
    }
}

GrafoHotel *CaricaHotel(AlberoCitta *radice){
    FILE *F1;
    F1=fopen("Alberghi.txt","r");
    CaricaCittaHotel(radice,&F1);
    fclose(F1);
}
