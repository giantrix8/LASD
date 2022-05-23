#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"
/*
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
}*/
static AlberoCitta *InserisciCitta(char *nome,short aereo,short treno) {
    AlberoCitta *tmp;
    tmp=(AlberoCitta*)malloc(sizeof(AlberoCitta));
    if (tmp==NULL)
    {
        printf ("non %c stato possibile allocare la memoria\n", e_accentata);
        return NULL;
    }
    tmp->citta->ListaAereo=tmp->dx=tmp->sx=tmp->citta->ListaTreno=NULL;
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
static AlberoCitta CercaNodo(){}
AlberoCitta  *EliminaNodo(AlberoCitta *radice,char *nome){
    AlberoCitta *tmp;
    tmp=CercaNodo(radice,nome);

}