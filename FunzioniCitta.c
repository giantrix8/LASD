#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"
static ListaNext *CaricaCitta(char **nome, int Leng){
    ListaNext *tmp;
    if (Leng>0){
        tmp=(ListaNext*)malloc(sizeof(ListaNext));
        strcpy(tmp->citta,nome[Leng-1]);
        tmp->next=CaricaCitta(nome,Leng-1);
    }
    else {tmp=NULL;}
    return tmp;
}
 static ListaNext *InserisciListaNext(ListaNext *testa,char **nome, int Leng){
    if (testa==NULL){
            testa=CaricaCitta(nome,Leng);
        }
    else{
        testa->next= InserisciListaNext(testa->next,nome,Leng);
    }
    return testa;
}
static AlberoCitta *InserisciCitta(char *nome,short aereo,short treno,char **ListaAereo,char **ListaTreno,int LengA, int LengT) {
    AlberoCitta *tmp;
    tmp=(AlberoCitta*)malloc(sizeof(AlberoCitta));
    if (tmp==NULL)
    {
        printf ("non %c stato possibile allocare la memoria\n", e_accentata);
        return NULL;
    }
    tmp->dx=tmp->sx=NULL;
    tmp->citta=(Citta*)malloc(sizeof(Citta));
    strcpy(tmp->citta->nome,nome);
    tmp->citta->aereo=aereo;
    tmp->citta->treno=treno;
    if (LengT!=0){
        tmp->citta->ListaTreno= InserisciListaNext(NULL,ListaTreno,LengT);
    }
    else{
        tmp->citta->ListaTreno=NULL;
    }
    if (LengA!=0){
        tmp->citta->ListaAereo= InserisciListaNext(NULL,ListaAereo,LengA);
    }
    else{
        tmp->citta->ListaAereo=NULL;
    }
    return tmp;
}
static AlberoCitta *RiempiAlberoCitta(AlberoCitta *radice, char *nome, short aereo, short treno, char **ListaAereo, char **ListaTreno, int LengA, int LengT){
    if(radice == NULL) {
        radice = InserisciCitta(nome,aereo,treno,ListaAereo,ListaTreno,LengA,LengT);
    }
    else {
        int controllo;
        controllo=strcmp(radice->citta->nome,nome);
        if(controllo>0){
            radice->sx= RiempiAlberoCitta(radice->sx,nome,aereo,treno,ListaAereo,ListaTreno,LengA,LengT);
        }
        else if (controllo<0) {
            radice->dx =  RiempiAlberoCitta(radice->dx,nome,aereo,treno,ListaAereo,ListaTreno,LengA,LengT);
        }
    }
    return radice;
}
