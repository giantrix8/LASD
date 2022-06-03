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
            albergo->hotel[i]->adiacenti=NULL;
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
Hotel *CercaHotel(AlberoCitta *radice, char *NomeCitta, char *NomeAlbergo){
    AlberoCitta *citta;
    int errore=0;
    citta = CercaNodo(radice, NomeCitta, &errore);
    if (errore!=1){return NULL;}
    Hotel **tmp;
    tmp=citta->citta->Grafohotel->hotel;
    int i=0;
    while(i<citta->citta->Grafohotel->dim){
        if (strcmp(tmp[i]->nome,NomeAlbergo)==0){
            return tmp[i];
        }
        else {
            i++;
        }
    }
    return NULL;
}
static Arco *CreaArco(int distanza, char *nomeAlbergo,AlberoCitta *radice, char *citta){
    Arco *NuovoArco;
    NuovoArco=(Arco*) malloc(sizeof(Arco));
    NuovoArco->distanza=distanza;
    NuovoArco->destinanzione= CercaHotel(radice,citta,nomeAlbergo);
    NuovoArco->next=NULL;
    return NuovoArco;
}

static Arco *InserisciArco(Arco *testa, int distanza, char *albergo,AlberoCitta *radice,char *citta){
     if (testa!=NULL){
         testa->next=InserisciArco(testa->next, distanza,albergo,radice,citta);
     }
     else{
         testa= CreaArco(distanza,albergo,radice,citta);
         printf(" %d %s",testa->distanza,testa->destinanzione->nome);
     }
    return testa;
}

static void CaricaAdiacenzaHotel(AlberoCitta *radice, FILE **file){
    AlberoCitta *citta;
    Hotel *hotel;
    char cittadafile[LenC],albergo[LenC];
    int distanza,esci,fine;
    while (fscanf(*file, "%s", cittadafile)==1){
        fine=0;
        do {
            fscanf(*file, "%s", albergo);
            if (strcmp(albergo, "Fine") != 0) {
                hotel = CercaHotel(radice, cittadafile, albergo);
                printf("\n %s",hotel->nome);
                esci = 0;
                do {
                    fscanf(*file, "%d%s", &distanza, albergo);
                    if (distanza < 0) {
                        esci = 1;
                    } else {
                        hotel->adiacenti = InserisciArco(hotel->adiacenti, distanza, albergo, radice, cittadafile);
                    }
                } while (esci == 0);
            }
            else {
                fine=1;
            }
        }while(fine==0);
    }
}

void CaricaHotel(AlberoCitta *radice){
    FILE *F1;
    F1=fopen("Alberghi.txt","r");
    CaricaCittaHotel(radice,&F1);
    fclose(F1);
    //printf("%s",radice->citta->Grafohotel->hotel[0]->nome); FUNZIONA
    F1=fopen("AdiacenzeAlberghi.txt","r");
    CaricaAdiacenzaHotel(radice,&F1);
    fclose(F1);
}
