#include <stdlib.h>
#include <stdio.h>
#include "strutture.h"


DjkElem *newDjkElem(Citta *citta)
{
    DjkElem *nuovo = (DjkElem*)malloc(sizeof(DjkElem));
    nuovo->citta = citta;
    nuovo->prev = NULL;
    nuovo->peso[0] = -1;
    nuovo->peso[1] = -1;
    return nuovo;
}

static DjkElem **newVector(DjkElem **DjkVector, int dim){
    int i = 0;
    DjkVector = (DjkElem**)malloc(dim*sizeof(DjkElem*));
    for(i = 0; i < dim; i++){
        DjkVector[i] = (DjkElem*)malloc(sizeof(DjkElem));
    }
    return DjkVector;
}

static DjkElem **newMinHeap(DjkElem **minHeap, int dim){
    int i = 0;
    minHeap = (DjkElem**)malloc(dim*sizeof(DjkElem*));
    for(i = 0; i < dim; i++){
        minHeap[i] = (DjkElem*)malloc(sizeof(DjkElem));
    }
    return minHeap;
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
    if(L < dim && (minHeap[L]->peso[modo] < minHeap[min]->peso[modo] || minHeap[L]->peso[modo] == -1))
        min = L;
    if(R < dim && (minHeap[R]->peso[modo] < minHeap[min]->peso[modo] || minHeap[R]->peso[modo] == -1))
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

Citta *EstraiMinimo(DjkElem **minHeap, int *dim)
{
    Citta *minCitta = minHeap[0]->citta;
    DjkSwap(minHeap, 0, *dim-1);
    *dim--;
    return minCitta;
}

DjkElem **djkRelax(DjkElem **Vector, Citta *partenza, ListaNext *arco, int modo)
{
    float newPeso;
    Citta *dest = arco->citta;

    if(modo == 0)
        newPeso = Vector[partenza->key]->peso[modo] + arco->durata;
    else
        newPeso = Vector[partenza->key]->peso[modo] + arco->prezzo;

    if(Vector[dest->key]->peso[modo] == -1 || newPeso < Vector[dest->key]->peso[modo]){
        Vector[dest->key]->peso[modo] = newPeso;
        Vector[dest->key]->prev = partenza;
    }
    return Vector;
}

DjkElem **MinPath(Citta *partenza, DjkElem **Vector, DjkElem **minHeap, int dim, int tipo, int modo)
{
    if(dim != 0)
    {
        Citta *minimo = NULL;
        ListaNext  *curr;
        if(tipo == 0)
            curr = partenza->ListaAereo;
        else
            curr = partenza->ListaTreno;
        while(curr != NULL)
        {
            Vector = djkRelax(Vector, partenza, curr, modo);
            curr = curr->next;
        }
        BuildHeap(minHeap, dim, modo);
        minimo = EstraiMinimo(minHeap, &dim);
        minHeap = MinPath(minimo, Vector, minHeap, dim, tipo, modo);
        return minHeap;
    }
}

void stampaPesi(DjkElem **vett, int dim)
{
    int i;
    for(i = 0; i < dim; i++)
        printf("Città: %s %d minuti\n", vett[i]->citta->nome, vett[i]->peso[0]);
}

// tipo: 0 per l'aereo, 1 per il treno
// modo: 0 per il più veloce, 1 per il più economico
Path *FindMinPath(AlberoCitta *radice, Citta *partenza, Citta *arrivo, int tipo, int modo)
{
    int dim = contaCitta(radice);
    DjkElem **Vector = NULL;
    DjkElem **minHeap = NULL;

    Vector = newVector(Vector, dim);
    minHeap = newMinHeap(minHeap, dim);
    riempiDjk(radice, Vector, minHeap);

    printf("%s", Vector[partenza->key]->citta->nome);
    Vector[partenza->key]->peso[modo] = 0;
    BuildHeap(minHeap, dim--, modo);
    minHeap = MinPath(partenza, Vector, minHeap, dim, tipo, modo);
    stampaPesi(Vector, dim);
    return NULL;
}