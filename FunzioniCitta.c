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
    //tmp->citta->ListaHotel=hotel;
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
static AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome) {
    int controllo;
    AlberoCitta *nodo;
    nodo=radice;
    while(nodo!=NULL){
        controllo=strcmp(nodo->citta->nome, nome);
        if (controllo==0){
            return nodo;
        }
        else if (controllo==1){
            nodo=nodo->sx;
        }
        else {
            nodo=nodo->dx;
        }
    }
    return NULL;
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
    CittaPartenza=CercaNodo(radice,partenza);
    if (CittaPartenza==NULL){
        CittaDestinazione=CercaNodo(radice,destinazione);
        if (CittaDestinazione==NULL){
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
static *CercaPadre(AlberoCitta *radice, char *nome){
    AlberoCitta *padre=NULL,*tmp=radice;
    int trovato=0,controllo;
    while(tmp!=NULL && trovato==0){
        controllo= strcmp(radice->citta->nome,nome);
        if (controllo==0){
            trovato=1;
        }
        else if (controllo>0){
            padre=tmp;
            tmp=tmp->sx;
        }
        else{
            padre=tmp;
            tmp=tmp->dx;
        }
    }
return padre;
}

static AlberoCitta *CercaFogliaMinAlberoCitta(AlberoCitta *radice){
    AlberoCitta *tmp=radice;
    while(tmp->sx!=NULL){
        tmp=tmp->sx;
    }
    return tmp;
}
static void DeallocaListaCitta(ListaNext *lista, char *nome){
    if (lista!=NULL){
        if(strcmp(lista->citta->nome,nome)==0){
            ListaNext *tmp;
            tmp=lista;
            lista=lista->next;
            free(tmp);
            DeallocaListaCitta(lista,nome);
        }
        else{
            DeallocaListaCitta(lista->next,nome);
        }
    }
}
static void EliminaListaCitta(AlberoCitta *radice, char*nome){
    if (radice!=NULL){
        DeallocaListaCitta(radice->citta->ListaAereo,nome);
        DeallocaListaCitta(radice->citta->ListaTreno,nome);
        EliminaListaCitta(radice->sx,nome);
        EliminaListaCitta(radice->dx,nome);
    }
}
static void FreeListeAdiacenzaCitta(AlberoCitta *radice){
    ListaNext *tmp;
    while (radice->citta->ListaAereo!=NULL) {
        tmp=radice->citta->ListaAereo->next;
        free(radice->citta->ListaAereo);
        radice=tmp;
    }
    while (radice->citta->ListaTreno!=NULL) {
        tmp=radice->citta->ListaTreno->next;
        free(radice->citta->ListaTreno);
        radice=tmp;
    }/*
    while (radice->citta->ListaHotel!=NULL) {
        tmp=radice->citta->ListaTreno->next;
        free(radice->citta->ListaHotel);
        radice=tmp;
    }*/
}

static AlberoCitta *EliminaNodoCitta(AlberoCitta *TestaAlbero,char *nome){
    if(TestaAlbero!=NULL) {
        AlberoCitta *radice=TestaAlbero;
        AlberoCitta *padre;
        radice= CercaNodo(radice,nome);
        if (radice==NULL){
            printf("/nIl nodo da eliminare non %c presente.",e_accentata);
            return TestaAlbero;
        }
        FreeListeAdiacenzaCitta(radice);
        free(radice->citta);
        if (radice->sx==NULL && radice->dx==NULL){
            free(radice);
            radice=NULL;
        }
        else if(radice->sx!=NULL && radice->dx!=NULL){
            AlberoCitta *Min;
            Min=CercaFogliaMinAlberoCitta(radice->dx); //in Min c'è il nodo minimo del sottoalbero destro del nodo da eliminare
            padre=CercaPadre(TestaAlbero,Min->citta->nome);//in padre c'è il padre di min
            if (padre==NULL && radice->dx->sx==NULL) {//Da eliminare è la radice e l'elemento più piccolo del sottoalbero dx è il figlio stesso
                Min->sx=TestaAlbero->sx;
                TestaAlbero=Min;
                free(radice);
            }
            else
            {
                padre->sx = Min->dx;
                radice->citta = Min->citta;
                free(Min);
            }
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
    return TestaAlbero;
}
AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome){
    testa=EliminaNodoCitta(testa,nome);
    EliminaListaCitta(testa,nome);
    return testa;
}
AlberoCitta *carica_grafo(AlberoCitta *radice)
{
    FILE *fp = NULL;
    char currentName[LenC], destName[LenC];
    short treno, aereo;
    float prezzo;
    int durata;

    //Caricamento albero delle città
    fp = fopen("citta.txt", "r");
    while(fscanf(fp, "%s %d %d", currentName, &treno, &aereo) > 0)
        radice = RiempiAlberoCitta(radice, currentName, aereo, treno);
    fclose(fp);

    //Caricamento liste di adiacenza
    fp = fopen("adiacenze.txt", "r");
    while(fscanf(fp, "%s", currentName) > 0)
    {
        //Inserimenti in lista treni
        while(fscanf(fp, "%s %f %d", destName, &prezzo, &durata) > 0)
        {
            if(strcmp("0", destName) == 0)
                break;
            InserisciListaAdiacenza(radice, currentName, destName, prezzo, durata, 0);
        }
        //inserimenro in lista aerei
        while(fscanf(fp, "%s %f %d", destName, &prezzo, &durata) > 0)
        {
            if(strcmp("0", destName) == 0)
                break;
            InserisciListaAdiacenza(radice, currentName, destName, prezzo, durata, 1);
        }
    }
    fclose(fp);
    return radice;
}
