#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

static AlberoCitta *InserisciCitta(char *nome,short aereo,short treno) {
    AlberoCitta *tmp;
    tmp=(AlberoCitta*)malloc(sizeof(AlberoCitta));
    if (tmp==NULL)
    {
        printf ("\nnon %c stato possibile allocare la memoria\n", e_accentata);
        return NULL;
    }
    tmp->citta->ListaAereo=tmp->dx=tmp->sx=tmp->citta->ListaTreno=NULL;
    tmp->citta->ListaHotel=NULL;
    tmp->citta=(Citta*)malloc(sizeof(Citta));
    strcpy(tmp->citta->nome,nome);
    tmp->citta->aereo=aereo;
    tmp->citta->treno=treno;
    tmp->citta->ListaAereo;
    return tmp;
}
static AlberoCitta *RiempiAlberoCitta(AlberoCitta *radice, char *nome, short aereo, short treno){
    if(radice == NULL) {
        radice = InserisciCitta(nome,aereo,treno);
    }
    else {
        int controllo;
        controllo=strcmp(radice->citta->nome,nome);
        if(controllo>0){
            radice->sx= RiempiAlberoCitta(radice->sx,nome,aereo,treno);
        }
        else if (controllo<0) {
            radice->dx =  RiempiAlberoCitta(radice->dx,nome,aereo,treno);
        }
    }
    return radice;
}
static AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome,int *errore) {
    int controllo;
    controllo = strcmp(radice->citta->nome, nome);
    if (controllo == 0) {
        *errore=1;
        return radice;
    }
    if (controllo > 0) {
        radice->sx = CercaNodo(radice->sx, nome,errore);
    } else if (controllo < 0) {
        radice->dx = CercaNodo(radice->dx, nome,errore);
    }
}

static ListaNext *InserisciDestinazione(ListaNext *testa,AlberoCitta *destinazione, float prezzo, int tempo){
    ListaNext *tmp;
    tmp=(ListaNext*)malloc(sizeof (ListaNext));
    if(tmp==NULL){
        printf("\nLa memoria non %c stata allocata",e_accentata);
        return testa;
    }
    tmp->prezzo=prezzo;
    tmp->durata=tempo;
    tmp->citta=destinazione;
    tmp->next=testa;
    return tmp;
}

//tipo==1 se si aggiunge nella lista aereo
static void InserisciListaAdiacenza(AlberoCitta *radice,char *partenza, char *destinazione, float prezzo, int tempo,short tipo){
    AlberoCitta *CittaPartenza,*CittaDestinazione;
    int errore=0;
    CittaPartenza=CercaNodo(radice,partenza,&errore);
    if (errore==1){
        CittaDestinazione=CercaNodo(radice,destinazione,&errore);
        if (errore==1){
            if (tipo==1) {
                CittaPartenza->citta->ListaAereo = InserisciDestinazione(CittaPartenza->citta->ListaAereo,CittaDestinazione, prezzo, tempo);
            }
            else{
                CittaPartenza->citta->ListaTreno = InserisciDestinazione(CittaPartenza->citta->ListaTreno,CittaDestinazione, prezzo, tempo);
            }
        }
        else {
            printf("\nLa destinazione non %c stata trovata", e_accentata);
        }
    }
    else
    {
        printf("\nLa citt%c di partenza non %c stata trovata",a_accentata, e_accentata);
    }
}
void CercaFogliaMinAlberoCitta(AlberoCitta **radice){
    AlberoCitta *tmp;
    tmp=*radice;
    if (tmp->sx!=NULL){
        CercaFogliaMinAlberoCitta(&tmp->sx);
    }
    else if (tmp->sx==NULL && tmp->dx!=NULL){
        CercaFogliaMinAlberoCitta(&tmp->dx);
    }
    else if (tmp->sx==NULL && tmp->dx==NULL){
        *radice=tmp;
    }
}
void FreeListaCitta(AlberoCitta *radice){
    while (radice->citta->ListaAereo!=NULL) {
        free(radice->citta->ListaAereo);
    }
    while (radice->citta->ListaTreno!=NULL) {
        free(radice->citta->ListaTreno);
    }
    while (radice->citta->ListaHotel!=NULL) {
        free(radice->citta->ListaHotel);
    }
    free(radice->citta);
}
static AlberoCitta *EliminaNodo(AlberoCitta *padre,AlberoCitta *radice,char *nome){
    if(radice!=NULL) {
        if (strcmp(radice->citta->nome,nome)==0){
            FreeListaCitta(radice);
            if (radice->sx==NULL && radice==NULL){
                free(radice);
            }
            else if(radice->sx!=NULL && radice->dx!=NULL){
                AlberoCitta *tmp=radice;
                CercaFogliaMinAlberoCitta(&tmp->dx);
                radice->citta=tmp->citta;
                free(tmp);
            }
            else if (radice->sx!=NULL && radice->dx==NULL){
                padre->sx=radice->sx;
                free(radice);
                radice=padre->sx;
            }
            else if (radice->sx==NULL && radice->dx!=NULL){
                padre->dx=radice->dx;
                free(radice);
                radice=padre->dx;
            }
        }
        else {
            radice = EliminaNodo(radice, radice->sx, nome);
            radice = EliminaNodo(radice, radice->dx, nome);
        }
    }
    return radice;
}

