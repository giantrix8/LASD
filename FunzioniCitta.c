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
    AlberoCitta *result = NULL;
    
    controllo = strcmp(radice->citta->nome, nome);
    if (controllo == 0) {
        *errore=1;
        result = radice;
    }
    else if (controllo > 0) {
        result = CercaNodo(radice->sx, nome,errore);
    }
	else {
        result = CercaNodo(radice->dx, nome,errore);
    }
    return result;
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

//tipo==1 se si aggiunge nella lista aereo, tipo==0 se si aggiunge nella lista treno
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
static void CercaFogliaMinAlberoCitta(AlberoCitta **radice){
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
static void FreeListaCitta(AlberoCitta *radice){
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

AlberoCitta *EliminaNodo(AlberoCitta *padre,AlberoCitta *radice,char *nome){
    if(radice!=NULL) {
        if (strcmp(radice->citta->nome,nome)==0){
            FreeListaCitta(radice);
            if (radice->sx==NULL && radice->dx==NULL){
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
AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome){
    testa=EliminaNodo(NULL,testa,nome);
    EliminaListaCitta(testa,nome);
    return testa;
}

AlberoCitta *carica_grafo(AlberoCitta *radice)
 {
 	FILE *fp = NULL;
 	AlberoCitta *currentNodo;
 	Citta *currentCitta;
 	char currentName[LenC], destName[LenC];
 	short treno, aereo;
 	float prezzo;
 	int durata, errore = 0;
 	
 	//Caricamento albero delle città
 	fp = fopen("citta.txt", "r");
 	while(fscanf(fp, "%s", currentName) > 0)
 	{
 		fscanf(fp, "%d", &aereo);
 		fscanf(fp, "%d", &treno);	
 		radice = RiempiAlberoCitta(radice, currentName, aereo, treno);	
	}
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
			InserisciListaAdiacenza(radice, currentName, destName, prezzo, durata, 0);;
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

void salva_citta(AlberoCitta *radice, FILE *fp)
{
	if(radice != NULL)
	{
		fprintf(fp, "%s ", radice->citta->nome);
		fprintf(fp, "%d %d\n", radice->citta->treno, radice->citta->aereo);
		salva_citta(radice->sx, fp);
		salva_citta(radice->dx, fp);
	}
}

void salva_adiacenze(AlberoCitta *radice, FILE *fp)
{
	ListaNext *curr;
	if(radice != NULL)
	{
		fprintf(fp, "%s ", radice->citta->nome);
		//Salva lista treni
		curr = radice->citta->ListaTreno;
		while (curr != NULL)
		{
			fprintf(fp, "%s ", curr->citta->nome);
			fprintf(fp, "%f ", curr->prezzo);
			fprintf(fp, "%d ", curr->durata);
			curr = curr->next;
		}
		fprintf(fp, "0 ");
		//Salva lista aerei
		curr = radice->citta->ListaAereo;
		while (curr != NULL)
		{
			fprintf(fp, "%s ", curr->citta->nome);
			fprintf(fp, "%f ", curr->prezzo);
			fprintf(fp, "%d ", curr->durata);
			curr = curr->next;
		}
		fprintf(fp, "0\n");
		salva_adiacenze(radice->sx, fp);
		salva_adiacenze(radice->dx, fp);
	}
}

void salva_grafo(AlberoCitta *radice)
 {
 	FILE *fp;
 	fp = fopen("citta.txt", "w");
 	salva_citta(radice, fp);
 	fclose(fp);
 	
 	fp = fopen("adiacenze.txt", "w");
 	salva_adiacenze(radice, fp);
 	fclose(fp);
 }
