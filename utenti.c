#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

Utenti *inserisciInListaUtenti(Utenti *lista, Utenti *utente){
    if(lista==NULL){
        utente->next = lista;
        return utente;
    }
    lista->next = inserisciInListaUtenti(lista->next, utente);

    return lista;
}

Utenti *leggiFileUtenti(FILE *fp){
    Utenti *tmp, *lista = NULL;

    fp = fopen("FileUtenti.txt", "r");

    while(!feof(fp)){
        tmp = (Utenti *) malloc(sizeof(Utenti));

        fscanf(fp,"%s\t%s\t%d",tmp->nome, tmp->password, &tmp->saldo);

        lista = inserisciInListaUtenti(lista,tmp);
    }

    fclose(fp);

    return lista;
}


void scriviSuFileListaUtenti(Utenti *lista, FILE *fp){
    fp = fopen("FileUtenti.txt", "a+");

    while(lista != NULL){
        if(lista->next != NULL){
            fprintf(fp, "%s\t%s\t%d\n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }

    fclose(fp);
}


Utenti *signIn(FILE *fp){
    int controllo;
    Utenti *tmp;
    tmp = malloc(sizeof(utenti));
    char ps[20];

    Utenti *utente = malloc(sizeof (Utenti));

    fp = fopen("FileUtenti.txt", "a+");

    printf("Inserisci il tuo nome : ");
    scanf("%s", utente->nome);

    do {
        controllo = 0;
        printf("\nInserisci la password-->");
        scanf("%s", tmp->password);
        printf("\nInseriscila di nuovo--->");
        scanf("%s", ps);
        if (strcmp(tmp->password, ps) != 0) {
            printf("\nLe due password non coincidono riprova.");
            controllo = 1;
        }
    } while (controllo == 1);

    printf("Inserisci il tuo saldo iniziale : ");
    scanf("%d", &utente->saldo);

    fprintf(fp, "%s\t%s\t%d\n", utente->nome, tmp->password, utente->saldo);

    printf("\nREGISTRAZIONE EFFETTUATA CON SUCCESSO\n");

    fclose(fp);

    return utente;
}


void stampaListaUtenti(Utenti *lista){
    while(lista != NULL){
        if (lista->next != NULL){
            printf("%s %s %d \n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }
}

Utenti *signUp(Utenti *lista){
    int controllo = 0, riprova = 0;
    Utenti *utente, *nuovaLista;

    utente = malloc(sizeof(utenti));
    nuovaLista = malloc(sizeof(utenti));

    do {
        printf("Inserisci il tuo nickname : ");
        scanf("%s", utente->nome);

        printf("Inserisci la password : ");
        scanf("%s", utente->password);

        controllo = 0;
        riprova = 0;

        nuovaLista = lista;
        while(nuovaLista != NULL){
            if(nuovaLista->next != NULL){
                if(strcmp(nuovaLista->nome, utente->nome) == 0 && strcmp(nuovaLista->password, utente->password) == 0){
                    strcpy(utente->nome, nuovaLista->nome);
                    strcpy(utente->password, nuovaLista->password);
                    utente->saldo = nuovaLista->saldo;
                    controllo = 1;
                }
            }
            nuovaLista = nuovaLista->next;
        }

        if(controllo == 1){
            printf("LOGIN EFFETTUATO CON SUCCESSO\n");
        } else{
            printf("Nome utente o password sbagliata. Inserisci 1 per riprovare 0 per terminare : ");
            scanf("%d", &riprova);
        }

        if(riprova == 0){
            exit(0);
        }

    } while (controllo != 1 || riprova != 0);
    
    return utente;
}

void scriviUtenti(Utenti *lista, FILE *fp){

    fp = fopen("FileUtenti.txt", "a+");

    while (lista != NULL) {
        if (lista->next != NULL) {
            fprintf(fp, "%s\t%s\t%d\n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }

    fclose(fp);
}


void aggiornaSaldo(Utenti *lista, int saldo, char nome[20], char password[20]) {
    FILE *fp;
    Utenti *nuovaListaUtenti;
    nuovaListaUtenti = malloc(sizeof(utenti));

    nuovaListaUtenti = lista;

    while(lista != NULL){
        if(lista->next != NULL){
            if (strcmp(lista->nome, nome) == 0 && strcmp(lista->password, password) == 0){
                lista->saldo = lista->saldo - saldo;
            }
        }
        lista = lista->next;
    }

    remove("FileUtenti.txt");

    scriviUtenti(nuovaListaUtenti, fp);
}
