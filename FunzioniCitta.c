#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

static AlberoCitta *InserisciCitta(char *nome,short aereo,short treno, int key) {
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
    tmp->citta->Grafohotel = NULL;
    tmp->citta->key = key;
    return tmp;
}
static AlberoCitta *RiempiAlberoCitta(AlberoCitta *radice, char *nome, short aereo, short treno, int key){
    if(radice == NULL) {
        radice = InserisciCitta(nome,aereo,treno, key);
    }
    else {
        int controllo;
        controllo=strcmp(radice->citta->nome,nome);
        if(controllo>0){
            radice->sx= RiempiAlberoCitta(radice->sx,nome,aereo,treno, key);
        }
        else if (controllo<0) {
            radice->dx =  RiempiAlberoCitta(radice->dx,nome,aereo,treno, key);
        }
    }
    return radice;
}

AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome,int *errore) {
    int controllo;
    AlberoCitta *result = NULL;
    if (radice==NULL){
        return NULL;
    }
    controllo = strcmp(radice->citta->nome, nome);
    if (controllo == 0) {
        *errore=1;
        result = radice;
    }
    else if (controllo > 0) {
        result = CercaNodo(radice->sx, nome,errore);
    }
    else{
        result = CercaNodo(radice->dx, nome,errore);
    }
    return result;
}

static ListaNext *InserisciDestinazione(ListaNext *testa,AlberoCitta *destinazione, float prezzo, float tempo){
    ListaNext *tmp;
    tmp=(ListaNext*)malloc(sizeof (ListaNext));
    if(tmp==NULL){
        printf("\nLa memoria non %c stata allocata",e_accentata);
        return testa;
    }
    tmp->prezzo=prezzo;
    tmp->durata=tempo;
    tmp->citta=destinazione->citta;
    tmp->next=testa;
    return tmp;
}

//tipo==1 se si aggiunge nella lista aereo, tipo==0 se si aggiunge nella lista treno
void InserisciListaAdiacenza(AlberoCitta *radice,char *partenza, char *destinazione, float prezzo, float tempo,short tipo){
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

static AlberoCitta *CercaPadre(AlberoCitta *radice, char *nome){
    AlberoCitta *padre=NULL,*tmp=radice;
    int trovato=0,controllo;
    while(tmp!=NULL && trovato==0){
        controllo= strcmp(tmp->citta->nome,nome);
        if (controllo==0){
            trovato=1;
            //printf("\n=0 %s----padre= %s",tmp->citta->nome,padre->citta->nome);
        }
        else if (controllo>0){
            padre=tmp;
            tmp=tmp->sx;
            //printf("\n>0 %s-----%s",tmp->citta->nome,padre->citta->nome);
        }
        else{
            padre=tmp;
            tmp=tmp->dx;
            //printf("\n<0 %s-----%s",tmp->citta->nome,padre->citta->nome);
        }
    }
    return padre;
} //FUNZIONA

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
        radice->citta->ListaAereo=tmp;
    }
    while (radice->citta->ListaTreno!=NULL) {
        tmp=radice->citta->ListaTreno->next;
        free(radice->citta->ListaTreno);
        radice->citta->ListaTreno=tmp;
    }
    if (radice->citta->Grafohotel!=NULL) {
        Arco *next;
        for (int i = 0; i < radice->citta->Grafohotel->dim; i++) {
            while (radice->citta->Grafohotel->hotel[i]->adiacenti != NULL) {
                next=radice->citta->Grafohotel->hotel[i]->adiacenti->next;
                free(radice->citta->Grafohotel->hotel[i]->adiacenti);
                radice->citta->Grafohotel->hotel[i]->adiacenti=next;
            }
            free(radice->citta->Grafohotel->hotel[i]);
        }
        free(radice->citta->Grafohotel);
    }
}

static void EliminaNodoCitta(AlberoCitta **TestaAlbero,char *nome){
    if(TestaAlbero!=NULL) {
        AlberoCitta *radice = *TestaAlbero;
        AlberoCitta *padre;
        int errore = 0;
        radice = CercaNodo(radice, nome, &errore);
        if (errore == 0) { //FUNZIONA
            printf("/nIl nodo da eliminare non %c presente.", e_accentata);
            return;
        }
        FreeListeAdiacenzaCitta(radice);
        if (radice->sx == NULL && radice->dx == NULL) { //FUNZIONA
            padre = CercaPadre(*TestaAlbero, radice->citta->nome);
            if (padre->sx == radice) {
                padre->sx = NULL;
            } else if (padre->dx == radice) {
                padre->dx = NULL;
            }
            free(radice->citta);
            free(radice);
            radice = NULL;
        }
        else if (radice->sx != NULL && radice->dx != NULL) { //funziona
            AlberoCitta *Min;
            Min = CercaFogliaMinAlberoCitta(radice->dx); //in Min c'è il nodo minimo del sottoalbero destro del nodo da eliminare
            padre = CercaPadre(*TestaAlbero, Min->citta->nome);//in padre c'è il padre di Min
            //printf("\npadre=%s radice=%s Min=%s", padre->citta->nome, radice->citta->nome, Min->citta->nome);
            free(radice->citta);
            if (padre==radice) {//Da eliminare è la radice e l'elemento più piccolo del sottoalbero dx è il figlio stesso
                radice->citta=Min->citta;
                radice->dx=Min->dx;
                free(Min);
            } else //FUNZIONA!
            {
                //printf("\ndentro EliminaNodoCitta");
                radice->citta = Min->citta;
                padre->sx = Min->dx;
                free(Min);
                //printf("\n%s--%s\nFuori EliminaNodoCitta",padre->citta->nome,padre->sx->citta->nome)

            }
        }
        else {
            padre= CercaPadre(*TestaAlbero,radice->citta->nome);
            if (radice->sx != NULL && radice->dx == NULL) {
                if (padre->sx == radice) {
                    padre->sx = radice->sx;
                    free(radice);
                } else if (padre->dx == radice) {
                    padre->dx = radice->sx;
                    free(radice);
                }
            } else if (radice->sx == NULL && radice->dx != NULL) {
                if (padre->sx == radice) {
                    padre->sx = radice->dx;
                    free(radice);
                } else if (padre->dx == radice) {
                    padre->dx = radice->dx;
                    free(radice);
                }
            }
        }
    }
    return;
}

AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome){
    EliminaNodoCitta(&testa,nome);
    printf("\n");
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
 	float prezzo, durata;
 	int i = 0, errore = 0;
 	
 	//Caricamento albero delle città
 	fp = fopen("citta.txt", "r");
 	while(fscanf(fp, "%s", currentName) > 0)
 	{
 		fscanf(fp, "%d", &aereo);
 		fscanf(fp, "%d", &treno);	
 		radice = RiempiAlberoCitta(radice, currentName, aereo, treno, i++);
	}
 	fclose(fp);

 	//Caricamento liste di adiacenza
 	fp = fopen("adiacenze.txt", "r");
 	while(fscanf(fp, "%s", currentName) > 0)
 	{
 		//Inserimenti in lista treni
 		while(fscanf(fp, "%s ", destName) > 0)
 		{
 			if(strcmp("0", destName) == 0)
			 	break;
            fscanf(fp, "%f ",&prezzo);
            fscanf(fp, "%f ",&durata);
			InserisciListaAdiacenza(radice, currentName, destName, prezzo, durata, 0);;
		}
		//inserimenro in lista aerei
 		while(fscanf(fp, "%s ", destName) > 0)
 		{
            fscanf(fp, "%f ",&prezzo);
            fscanf(fp, "%f ",&durata);
 			if(strcmp("0", destName) == 0)
			 	break;
			InserisciListaAdiacenza(radice, currentName, destName, prezzo, durata, 1);
		}
	}
	fclose(fp);
	return radice;
}

static void salva_citta(AlberoCitta *radice, FILE *fp)
{
	if(radice != NULL)
	{
		fprintf(fp, "%s ", radice->citta->nome);
		fprintf(fp, "%d %d\n", radice->citta->treno, radice->citta->aereo);
		salva_citta(radice->sx, fp);
		salva_citta(radice->dx, fp);
	}
}

static void salva_adiacenze(AlberoCitta *radice, FILE *fp)
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
			fprintf(fp, "%.2f ", curr->prezzo);
			fprintf(fp, "%.0f ", curr->durata);
			curr = curr->next;
		}
		fprintf(fp, "0 ");
		//Salva lista aerei
		curr = radice->citta->ListaAereo;
		while (curr != NULL)
		{
			fprintf(fp, "%s ", curr->citta->nome);
			fprintf(fp, "%.2f ", curr->prezzo);
			fprintf(fp, "%.0f ", curr->durata);
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

void contaCitta(AlberoCitta *radice, int *n)
{
    if(radice != NULL)
    {
        contaCitta(radice->sx, n);
        radice->citta->key = *n;
        (*n)++;
        contaCitta(radice->dx, n);
    }
}

 void StampaCitta (AlberoCitta *radice){
     if (radice!=NULL){
         StampaCitta(radice->sx);
         printf("->%s ",radice->citta->nome);
         StampaCitta(radice->dx);
     }
}

static void ControlloCitta(ListaNext *lista,char *NomeCitta, int *trovato){
    ListaNext *next=lista;
    while (next!=NULL && *trovato==0){
        if (strcmp(NomeCitta,next->citta->nome)==0){
            *trovato=1;
        }
        else{
            next=next->next;
        }
    }
}

static void CittaInraggiungibile(AlberoCitta *radice,char *nomeCitta, int *trovato){
    if (radice!=NULL){
        ControlloCitta(radice->citta->ListaTreno,nomeCitta,trovato);
        ControlloCitta(radice->citta->ListaAereo,nomeCitta,trovato);
        if (*trovato==0){
            CittaInraggiungibile(radice->sx,nomeCitta,trovato);
        }
        if (*trovato==0){
            CittaInraggiungibile(radice->dx,nomeCitta,trovato);
        }
    }

}

void ControllaCittaInraggiungibile(AlberoCitta *radice, AlberoCitta *CittaCorrente){
    if (CittaCorrente!=NULL) {
        int trovato = 0;
        CittaInraggiungibile(radice, CittaCorrente->citta->nome, &trovato);
        if (trovato == 0) {
            crea_notifica(CittaCorrente->citta);
        }
        ControllaCittaInraggiungibile(radice,CittaCorrente->sx);
        ControllaCittaInraggiungibile(radice, CittaCorrente->dx);
    }
}