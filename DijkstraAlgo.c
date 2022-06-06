#include <stdio.h>
#include <stdlib.h>

#include "strutture.h"
#include <unistd.h>

DjkElem *newDjkElem(Citta *citta)
{
    DjkElem *nuovo = (DjkElem*)malloc(sizeof(DjkElem));
    nuovo->citta = citta;
    nuovo->prev = NULL;
    nuovo->peso[0] = -1;
    nuovo->peso[1] = -1;
    nuovo->tipo = 2;
    return nuovo;
}

Prenotazione *newPrenotazione(Path *path, Hotel *hotel, float durata, float prezzo)
{
    Prenotazione *nuovo = (Prenotazione*)malloc(sizeof(Prenotazione));
    nuovo->viaggio = path;
    nuovo->hotel = hotel;
    nuovo->durata = durata;
    nuovo->prezzo = prezzo;
    return nuovo;
}

static DjkElem **newDjk(DjkElem **DjkVector, int dim){
    int i;
    DjkVector = (DjkElem**)malloc(dim*sizeof(DjkElem*));
    for(i = 0; i < dim; i++){
        DjkVector[i] = (DjkElem*)malloc(sizeof(DjkElem));
    }
    return DjkVector;
}

DjkElem **freeDjk(DjkElem **DjkVector, int dim)
{
    int i;
    for(i = 0; i < dim; i++)
        free(DjkVector[i]);
    free(DjkVector);
    return NULL;
}

static void riempiDjk(AlberoCitta *radice, DjkElem **DjkVector, DjkElem **minHeap){
    if(radice != NULL){
        DjkElem *nuovo = newDjkElem(radice->citta);
        riempiDjk(radice->sx, DjkVector, minHeap);
        DjkVector[radice->citta->key] = nuovo;
        minHeap[radice->citta->key] = nuovo;
        riempiDjk(radice->dx, DjkVector, minHeap);
    }
}

void DjkSwap(DjkElem **minHeap, int i, int j)
{
    DjkElem *tmp = minHeap[i];
    minHeap[i] = minHeap[j];
    minHeap[j] = tmp;
}

void Heapfy(DjkElem **minHeap, int i, int dim, int modo)
{
    int min = i;
    int L = 2*i+1;
    int R = 2*i+2;
    if(L < dim && (minHeap[min]->peso[modo] == -1 || (minHeap[L]->peso[modo] >= 0 && minHeap[L]->peso[modo] < minHeap[min]->peso[modo])))
        min = L;
    if(R < dim && (minHeap[min]->peso[modo] == -1 || (minHeap[R]->peso[modo] >= 0 && minHeap[R]->peso[modo] < minHeap[min]->peso[modo])))
        min = R;
    if(min != i)
    {
        DjkSwap(minHeap, i, min);
        Heapfy(minHeap, min, dim, modo);
    }
}

void BuildHeap(DjkElem **minHeap, int dim, int modo)
{
    int i = dim/2-1;
    for(; i >= 0; i--)
        Heapfy(minHeap, i, dim, modo);
}

Citta *EstraiMinimo(DjkElem **minHeap, int dim)
{
    Citta *minCitta = minHeap[0]->citta;
    //Funzione di controllo
    //printf("nodo piu vicino: %s\n", minCitta->nome);
    DjkSwap(minHeap, 0, dim-1);
    return minCitta;
}

DjkElem **djkRelax(DjkElem **Vector, Citta *partenza, ListaNext *arco, int tipo, int modo)
{
    float newPeso, newPeso2;
    Citta *dest = arco->citta;

    if(modo == 0)
    {
        newPeso = Vector[partenza->key]->peso[modo] + arco->durata;
        newPeso2 = Vector[partenza->key]->peso[(modo+1)%2] + arco->prezzo;
    }
    else
    {
        newPeso2 = Vector[partenza->key]->peso[(modo+1)%2] + arco->durata;
        newPeso = Vector[partenza->key]->peso[modo] + arco->prezzo;
    }
    //Funzione di controllo
    //printf("%s %.0f + per %s %.0f = %.0f\n", partenza->nome, Vector[partenza->key]->peso[modo], dest->nome, arco->durata, newPeso);

    if(Vector[dest->key]->peso[modo] == -1 || newPeso < Vector[dest->key]->peso[modo]){
        Vector[dest->key]->peso[modo] = newPeso;
        Vector[dest->key]->peso[(modo+1)%2] = newPeso2;
        Vector[dest->key]->prev = partenza;
        Vector[dest->key]->tipo = tipo;
        //printf("%s %d ", Vector[dest->key]->citta->nome, tipo);
    }
    return Vector;
}

void stampaPesi(DjkElem **vett, int dim)
{
    int i;
    for(i = 0; i < dim; i++)
        printf("per %s %.0f minuti, prezzo: %.2f\n", vett[i]->citta->nome, vett[i]->peso[0], vett[i]->peso[1]);
}

DjkElem **MinPath(Citta *partenza, DjkElem **Vector, DjkElem **minHeap, int dim, int tipo, int modo)
{
    if(dim != 0)
    {
        Citta *minimo = NULL;
        ListaNext  *curr = NULL;
        if(tipo == 0 || tipo == 2)
        {
            curr = partenza->ListaAereo;
            while(curr != NULL)
            {
                Vector = djkRelax(Vector, partenza, curr, 0, modo);
                curr = curr->next;
            }
        }
        if(tipo == 1 || tipo == 2)
        {
            curr = partenza->ListaTreno;
            while(curr != NULL)
            {
                Vector = djkRelax(Vector, partenza, curr, 1, modo);
                curr = curr->next;
            }
        }
        Heapfy(minHeap, 0, dim, modo);
        minimo = EstraiMinimo(minHeap, dim--);
        minHeap = MinPath(minimo, Vector, minHeap, dim, tipo, modo);
        return minHeap;
    }
}

Path *inserisciPath(Path *top, Citta *citta, char* tipo)
{
    Path *nuovo = (Path*)malloc(sizeof(Path));
    nuovo->citta = citta;
    nuovo->tipo = tipo;
    nuovo->next = top;
    return nuovo;
}


void stampa_path(Path *cammino)
{
    if(cammino->next != NULL)
    {
        if(cammino->next->tipo == 0)
            printf("Aereo ");
        else if(cammino->next->tipo == 1)
            printf("Treno ");
        printf("%s --> %s\n", cammino->citta->nome, cammino->next->citta->nome);
        stampa_path(cammino->next);
    }
}

void stampa_viaggio(Prenotazione *prenotazione)
{
    stampa_path(prenotazione->viaggio);
    printf("Durata totale: %.0f minuti\nPrezzo: %.2f%c\n", prenotazione->durata, prenotazione->prezzo,dollaro);
    sleep(2);
}

// tipo: 0 per l'aereo, 1 per il treno, 2 per misto
// modo: 0 per il più veloce, 1 per il più economico
// trova il percorso minimo, permette la scelta dell'hotel e restituisce un puntatore ad una prenotazione
Prenotazione *prenotaViaggio(AlberoCitta *radice, char *partenzaa, char *arrivoo, int tipo, int modo)
{
    Citta *partenza,*arrivo;
    int errore=0;
    partenza= (CercaNodo(radice,partenzaa,&errore))->citta;
    if(errore!=1){
        return NULL;
    }
    errore=0;
    arrivo= (CercaNodo(radice,arrivoo,&errore))->citta;
    if(errore!=1){
        return NULL;
    }
    int dim = 0;
    contaCitta(radice, &dim);
    Path *minPath = NULL;
    DjkElem **Vector = NULL;
    DjkElem **minHeap = NULL;
    DjkElem *currElem = NULL;
    Citta *currCitta = NULL;
    Hotel *albergo = NULL;
    Prenotazione *pren;

    Vector = newDjk(Vector, dim);
    minHeap = newDjk(minHeap, dim);
    riempiDjk(radice, Vector, minHeap);
    //Inizializzazione Dijkstra
    Vector[partenza->key]->peso[0] = 0;
    Vector[partenza->key]->peso[1] = 0;
    BuildHeap(minHeap, dim, modo);
    partenza = EstraiMinimo(minHeap, dim);
    //Chiamata Dijkstra
    minHeap = MinPath(partenza, Vector, minHeap, dim-1, tipo, modo);
    //stampaPesi(Vector, dim); //Funzione di controllo
    //Controllo se la destinazione è raggiungibile
    if(Vector[arrivo->key]->tipo == 2)
    {
        crea_notifica(arrivo);
        return NULL;
    }
    //Ricostruzione del percorso minimo
    currCitta = arrivo;
    currElem = Vector[arrivo->key];
    while(1)
    {
        minPath = inserisciPath(minPath, currCitta, currElem->tipo);
        currCitta = currElem->prev;
        if(currCitta == NULL)
            break;
        currElem = Vector[currCitta->key];
    }
    //Creazione della prenotazione
    pren = newPrenotazione(minPath, NULL, Vector[arrivo->key]->peso[0], Vector[arrivo->key]->peso[1]);
    stampa_viaggio(pren);
    //Scelta dell'Hotel
    albergo = SceltaHotel(radice, arrivo->nome);
    if(albergo == NULL)
    {
        free(pren);
        return NULL;
    }
    djkHotel(arrivo->Grafohotel, albergo);
    pren->hotel = albergo;
    pren->prezzo += albergo->prezzo;
    printf("\n");
    //Liberazione della memoria e ritorno
    Vector = freeDjk(Vector, dim);
    return pren;
}
