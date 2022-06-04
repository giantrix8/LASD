#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strutture.h"

void crea_notifica(Citta *citta, int tipo)
{
    FILE *fp = NULL;
    fp = fopen("notifiche.txt", "a");

    fprintf(fp,"%s %d\n", citta->nome, tipo);
    fclose(fp);
}

Path *inserisci_notifica(Path* top, Citta *citta, int tipo)
{
    if(top == NULL)
    {
        Path* nuovo = (Path*)malloc(sizeof(Path));
        nuovo->citta = citta;
        nuovo->tipo = tipo;
        nuovo->next = NULL;
        return nuovo;
    }
    else
        top->next = inserisci_notifica(top->next, citta, tipo);
}

Path *carica_notifiche(AlberoCitta *radice)
{
    Path* codaNotifiche = NULL;
    FILE *fp = NULL;
    char nome[LenC];
    int tipo, errore = 0;
    Citta *currCitta = NULL;

    fp = fopen("notifiche.txt", "r");
    while(fscanf(fp, "%s", nome) > 0)
    {
        fscanf(fp, "%d\n", &tipo);
        currCitta = (CercaNodo(radice, nome, &errore))->citta;
        codaNotifiche = inserisci_notifica(codaNotifiche, currCitta, tipo);
    }
    fclose(fp);
    return codaNotifiche;
}

void salva_notifiche(Path* codaNotifiche)
{
    if(codaNotifiche != NULL)
    {
        crea_notifica(codaNotifiche->citta, codaNotifiche->tipo);
        salva_notifiche(codaNotifiche->next);
    }
}

void mostra_notifiche(AlberoCitta *radice)
{
    Path* codaNotifiche = NULL, *tmp = NULL;
    Citta* partenza = NULL;
    char nuovoNome[LenC];
    float nuovoPrezzo, nuovaDurata;
    int tipo, op, errore;
    if (tipo == 2)
        tipo--;

    codaNotifiche = carica_notifiche(radice);
    if(codaNotifiche == NULL)
    {
        printf("Non ci sono notifiche!\n");
        return;
    }
    do {
        if(codaNotifiche->tipo == 0){
            printf("Non ci sono aerei per ");
        }
        else
            printf("Non ci sono treni per ");
        printf("%s\n", codaNotifiche->citta->nome);
        printf("Premi:\n1 per inserire una città da cui sia raggiungibile\n2 per eliminare il nodo\n3 per tornare indietro\n");
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
                }
            } while(partenza == NULL);
            InserisciListaAdiacenza(radice, nuovoNome, codaNotifiche->citta->nome, nuovoPrezzo, nuovaDurata, (tipo%2)+1);
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
    } while(codaNotifiche != NULL && op != 3);
    FILE *fp = fopen("notifiche.txt", "w");
    fclose(fp);
    salva_notifiche(codaNotifiche);
}