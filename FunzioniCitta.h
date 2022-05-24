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
    tmp->dx = NULL;
    tmp->sx = NULL;
    tmp->citta = (Citta*)malloc(sizeof(Citta));
    strcpy(tmp->citta->nome, nome);
    tmp->citta->aereo = aereo;
    tmp->citta->treno = treno;
    tmp->citta->ListaAereo = NULL;
    tmp->citta->ListaTreno = NULL;
    tmp->citta->ListaHotel = NULL;
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

static ListaNext *InserisciDestinazione(ListaNext *testa, Citta *destinazione, float prezzo, int tempo){
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
//napoli---->milano     tmp=napoli

//tipo==1 se si aggiunge nella lista aereo, tipo == 0 se si aggiunge nella lista treno
static void InserisciListaAdiacenza(AlberoCitta *radice,char *partenza, char *destinazione, float prezzo, int tempo,short tipo){
    AlberoCitta *CittaPartenza,*CittaDestinazione;
    int errore=0;
    CittaPartenza=CercaNodo(radice,partenza,&errore);
    if (errore==1){
        CittaDestinazione=CercaNodo(radice,destinazione,&errore);
        if (errore==1){
            if (tipo==1) {
                CittaPartenza->citta->ListaAereo = InserisciDestinazione(CittaPartenza->citta->ListaAereo,CittaDestinazione->citta, prezzo, tempo);
            }
            else{
                CittaPartenza->citta->ListaTreno = InserisciDestinazione(CittaPartenza->citta->ListaTreno,CittaDestinazione->citta, prezzo, tempo);
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
/*
AlberoCitta  *EliminaNodo(AlberoCitta *radice,char *nome){
    AlberoCitta *tmp;
    tmp=CercaNodo(radice,nome);
}
 */
 
 AlberoCitta *carica_grafo(AlberoCitta *ABRcitta)
 {
 	
 	
 }
