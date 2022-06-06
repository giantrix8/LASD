#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

static GrafoHotel *CaricaVetHotel(FILE **file,int dim){
    GrafoHotel *albergo=NULL;
    albergo = (GrafoHotel *) malloc(sizeof(GrafoHotel));
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
            //printf("\n%d", i);
            strcpy(albergo->hotel[i]->nome, citta);
            albergo->hotel[i]->adiacenti=NULL;
            //printf("->%s %.2f",albergo->hotel[i]->nome,albergo->hotel[i]->prezzo);
        }
    }
    return albergo;
}

static void CaricaCittaHotel(AlberoCitta *radice, FILE **file) {
    AlberoCitta *citta;
    int errore = 0;
    char cittadafile[LenC];
    int dim;
    while (fscanf(*file, "%s%d", cittadafile, &dim) == 2) {
        errore=0;
        citta = CercaNodo(radice, cittadafile, &errore);
        if (errore==1){
            citta->citta->Grafohotel = CaricaVetHotel(file, dim);
        }
        //printf("%s",citta->citta->nome); FUNZIONA
        //printf("\n%s->%s",citta->citta->nome,citta->citta->hotel->hotel[0]->nome);
    }
}
void StampaHotel (Hotel **hotel, int dim){
    int i;
    printf("\n Gli hotel disponibili sono:");
    for(i=0;i<dim;i++){
        printf("\n%d %s %.2f%c",i,hotel[i]->nome,hotel[i]->prezzo,dollaro);
    }
}

Hotel *SceltaHotel(AlberoCitta *radice, char *NomeCitta){
    int scelta=0;
    AlberoCitta *nodo;
    nodo=CercaNodo(radice,NomeCitta,&scelta);
    if (scelta!=1){
        printf ("\nLa citt%s richiesta non %s presente",a_accentata,e_accentata);
    }
    StampaHotel(nodo->citta->Grafohotel->hotel,nodo->citta->Grafohotel->dim);
    do {
        printf("\nSeleziona l'albergo in cui vuoi pernottare o -1 annullare: ->");
        scanf("%d",&scelta);
        if (scelta==-1){
            return NULL;
        }
        if (scelta<0 || scelta>nodo->citta->Grafohotel->dim){
            printf("\nLa scelta non %s valida",e_accentata);
        }
    } while (scelta<0 || scelta>nodo->citta->Grafohotel->dim);
    return nodo->citta->Grafohotel->hotel[scelta];
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
         //printf(" %d %s",testa->distanza,testa->destinanzione->nome);
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
                //printf("\n %s",hotel->nome);
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

static void SalvaHotel (AlberoCitta *radice, FILE **file){
    fprintf(*file,"\n%s ",radice->citta->nome);
    if (radice->citta->Grafohotel!=NULL) {
        fprintf(*file,"%d ",radice->citta->Grafohotel->dim);
        for (int i = 0; i < radice->citta->Grafohotel->dim; i++) {
            fprintf(*file, "%s %.2f ", radice->citta->Grafohotel->hotel[i]->nome,
                    radice->citta->Grafohotel->hotel[i]->prezzo);
            }
    }
    else{
        fprintf(*file,"0");
    }
}

static void SalvaHotelAdiacenza(AlberoCitta *testa, FILE **file) {
    AlberoCitta *radice = testa;
    int i;
    fprintf(*file, "%s ", radice->citta->nome);
    if (radice->citta->Grafohotel!=NULL) {
        for (i = 0; i < radice->citta->Grafohotel->dim; i++) {
            fprintf(*file, "%s ", radice->citta->Grafohotel->hotel[i]->nome);
            while (radice->citta->Grafohotel->hotel[i]->adiacenti != NULL) {
                fprintf(*file, "%d %s ", radice->citta->Grafohotel->hotel[i]->adiacenti->distanza,radice->citta->Grafohotel->hotel[i]->adiacenti->destinanzione->nome);
                //printf("\n%d %s ", radice->citta->Grafohotel->hotel[i]->adiacenti->distanza,radice->citta->Grafohotel->hotel[i]->adiacenti->destinanzione->nome);
                radice->citta->Grafohotel->hotel[i]->adiacenti = radice->citta->Grafohotel->hotel[i]->adiacenti->next;
            }
            fprintf(*file,"-1 0\n");
        }
    }
    fprintf(*file,"Fine\n\n");
}
static void CaricaGrafoIte(AlberoCitta *radice,FILE *F1, FILE *F2){
    if (radice!=NULL){
        SalvaHotel(radice, &F1);
        SalvaHotelAdiacenza(radice, &F2);
        CaricaGrafoIte(radice->sx,F1,F2);
        CaricaGrafoIte(radice->dx,F1,F2);
    }
}

void SalvaGrafoHotel(AlberoCitta *radice){
    FILE *F1,*F2;
    F1 = fopen("Alberghi.txt", "w");
    F2 = fopen("AdiacenzeAlberghi.txt", "w");
    CaricaGrafoIte(radice,F1,F2);
    fclose(F1);
    fclose(F2);
}
int minHotel(int *vett, int *visited, int dim)
{
    int i;
    int minIndex = -1;
    for(i = 0; i < dim; i++)
    {
        if (visited[i] == 0)
        {
            if (minIndex == -1)
                minIndex = i;
            else if(vett[i] > -1 && vett[i] < vett[minIndex])
                minIndex = i;
        }
    }
    return minIndex;
}

void stampa_pathHotel(Hotel **graph, int arrivo, int *precedenti)
{
    if(arrivo != -1)
    {
        stampa_pathHotel(graph, precedenti[arrivo], precedenti);
        printf("--> %s ", graph[arrivo]->nome);
    }
}

void relaxHotel(Arco *arco, int *distanze, int partenza, int *precedenti, int dim)
{
    Hotel *dest = arco->destinanzione;
    int newDist = arco->distanza + distanze[dest->key];

    if(distanze[dest->key] == -1 || newDist < distanze[dest->key])
    {
        distanze[dest->key] = newDist;
        precedenti[dest->key] = partenza;
    }
}

int *minPathHotel(Hotel **graph, int *distanze, int *visited, int *precedenti, int dim)
{
    int i, min;
    Arco *curr = NULL;
    for(i = 0; i < dim; i++)
    {
        min = minHotel(distanze, visited, dim);
        //printf("%d / %d\n", min, dim);
        visited[min] = 1;
        curr = graph[min]->adiacenti;
        while(curr != NULL)
        {
            relaxHotel(curr, distanze, graph[min]->key, precedenti, dim);
            curr = curr->next;
        }
    }
    return distanze;
}

void djkHotel(GrafoHotel *graph, Hotel *arrivo)
{
    int dim = graph->dim, i;
    int *visited = (int*)calloc(dim, sizeof(int));
    int *distanze = (int*)malloc(dim*sizeof(int));
    int *precedenti = (Hotel**)calloc(dim, sizeof(Hotel*));


    graph->hotel[0]->key = 0;
    distanze[0] = 0;
    precedenti[0] = -1;
    visited[0] = 0;
    for(i = 1; i < dim; i++)
    {
        graph->hotel[i]->key = i;
        distanze[i] = -1;
        precedenti[i] = -1;
        visited[i] = 0;
    }
    distanze = minPathHotel(graph->hotel, distanze, visited, precedenti, dim);
    free(visited);

    printf("Percorso piu breve per l'Hotel: %d km\n", distanze[arrivo->key]);
    stampa_pathHotel(graph->hotel, arrivo->key, precedenti);
    free(distanze);
    free(precedenti);
}