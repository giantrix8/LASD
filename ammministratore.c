#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strutture.h"
void Logo(){
    system("CLS");
    printf ("Benvenuto %c\n\t\t             %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",1,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
    printf ("\nViaggi da 30elloda solo su-> %c %c 3G Travel %c %c",179, 4, 4,179);
    printf ("\n\t %c                   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",32,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
}//FUNZIONA

static int CercaNotifica(Path *testa, char *nomecitta){
    if (testa==NULL){return 0;}
    if (strcmp(nomecitta,testa->citta->nome)==0){
        return 1;
    }
    else{
        return CercaNotifica(testa->next,nomecitta);
    }
}


void crea_notifica(Citta *citta)
{
    FILE *fp = NULL;
    fp = fopen("notifiche.txt", "a");

    fprintf(fp,"%s\n", citta->nome);
    fclose(fp);
}

Path *inserisci_notifica(Path* top, Citta *citta)
{
    Path* nuovo = (Path*)malloc(sizeof(Path));
    nuovo->citta = citta;
    nuovo->next = top;
    return nuovo;
    /*
    if(top == NULL)
    {
        Path* nuovo = (Path*)malloc(sizeof(Path));
        nuovo->citta = citta;
        nuovo->next = NULL;
        return nuovo;
    }
    else
        top->next = inserisci_notifica(top->next, citta);
    */
}

Path *carica_notifiche(AlberoCitta *radice)
{
    Path* codaNotifiche = NULL;
    FILE *fp = NULL;
    char nome[LenC];
    int  errore = 0;
    Citta *currCitta = NULL;

    fp = fopen("notifiche.txt", "r");
    while(fscanf(fp, "%s", nome) > 0)
    {
        int trovato=CercaNotifica(codaNotifiche,nome);
        if(trovato==0){
            currCitta = (CercaNodo(radice, nome, &errore))->citta;
            codaNotifiche = inserisci_notifica(codaNotifiche, currCitta);
        }
    }
    fclose(fp);
    return codaNotifiche;
}

void salva_notifiche(Path* codaNotifiche)
{
    if(codaNotifiche != NULL)
    {
        crea_notifica(codaNotifiche->citta);
        salva_notifiche(codaNotifiche->next);
    }
}

void stampa_notifiche(Path *top)
{
    if(top != NULL)
    {
        printf("%s -> ", top->citta->nome);
        stampa_notifiche(top->next);
    }
}

void mostra_notifiche(AlberoCitta *radice)
{
    Path* codaNotifiche = NULL, *tmp = NULL;
    Citta* partenza = NULL;
    char nuovoNome[LenC];
    float nuovoPrezzo, nuovaDurata;
    int op, errore,tipo;
    codaNotifiche = carica_notifiche(radice);
    FILE *fp = fopen("notifiche.txt", "w");
    fprintf(fp, "");
    fclose(fp);
    if(codaNotifiche == NULL)
    {
        printf("Non ci sono notifiche!\n");
        return;
    }
    do {
        //stampa_notifiche(codaNotifiche);
        printf("\nLa citt%c %s non %c raggiungibile\n",a_accentata, codaNotifiche->citta->nome,e_accentata);
        printf("Premi:\n1 per inserire una citt%c da cui sia raggiungibile\n2 per eliminare il nodo\n",a_accentata);
        scanf("%d", &op);
        if(op == 1)
        {
            do{
                scanf("%s", nuovoNome);
                partenza = CercaNodo(radice, nuovoNome, &errore);
                if(partenza != NULL)
                {
                    printf("Prezzo: ");
                    scanf("%f", &nuovoPrezzo);
                    printf("Durata del viaggio in minuti: ");
                    scanf("%f", &nuovaDurata);
                    printf("Inserire 0 per treno 1 per aereo");
                    scanf("%d",&tipo);
                }
            } while(partenza == NULL);
            InserisciListaAdiacenza(radice, nuovoNome, codaNotifiche->citta->nome, nuovoPrezzo, nuovaDurata, tipo);
            tmp = codaNotifiche;
            codaNotifiche = codaNotifiche->next;
            free(tmp);
        }
        else if(op == 2)
        {
            EliminaCitta(radice, codaNotifiche->citta->nome);
            tmp = codaNotifiche;
            codaNotifiche = codaNotifiche->next;
            free(tmp);
        }
    } while(codaNotifiche != NULL);
    fp = fopen("notifiche.txt", "w");
    fprintf(fp, "");
    fclose(fp);
    salva_notifiche(codaNotifiche);
}