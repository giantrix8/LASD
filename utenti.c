#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Utenti{
    char nome[20];
    char password[20];
    int saldo;
    struct Utenti *next;
}utenti;


utenti *inserisciInListaUtenti(utenti *lista, utenti *utente){
    if(lista==NULL){
        utente->next = lista;
        return utente;
    }
    lista->next = inserisciInListaUtenti(lista->next, utente);

    return lista;
}


utenti *leggiFileUtenti(FILE *fp){
    utenti *tmp, *lista = NULL;

    fp = fopen("FileUtenti.txt", "r");

    while(!feof(fp)){
        tmp = (utenti *) malloc(sizeof(utenti));

        fscanf(fp,"%s\t%s\t%d",tmp->nome, tmp->password, &tmp->saldo);

        lista = inserisciInListaUtenti(lista,tmp);
    }

    fclose(fp);

    return lista;
}


void scriviSuFileListaUtenti(utenti *lista, FILE *fp){
    fp = fopen("FileUtenti.txt", "a+");

    while(lista != NULL){
        if(lista->next != NULL){
            fprintf(fp, "%s\t%s\t%d\n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }

    fclose(fp);
}


utenti *signIn(FILE *fp){
    int controllo;
    utenti *tmp;
    tmp = malloc(sizeof(utenti));
    char ps[20];

    utenti *utente = malloc(sizeof (utenti));

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

    fprintf(fp, "%s\t%s\t%d\n", utente->nome, utente->password, utente->saldo);

    printf("\nREGISTRAZIONE EFFETTUATA CON SUCCESSO\n");

    fclose(fp);

    return utente;
}


void stampaListaUtenti(utenti *lista){
    while(lista != NULL){
        if (lista->next != NULL){
            printf("%s %s %d \n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }
}


utenti *signUp(utenti *listaUtenti, char nome[20], char password[20]){
    utenti *utente;
    utente = malloc(sizeof(utenti));
    int controllo = 0, riprova = 1;

    while(listaUtenti != NULL){
        if(listaUtenti->next != NULL){
            if(strcmp(listaUtenti->nome, nome) == 0 && strcmp(listaUtenti->password, password) == 0){
                strcpy(utente->nome, listaUtenti->nome);
                strcpy(utente->password, listaUtenti->password);
                utente->saldo = listaUtenti->saldo;
                controllo = 1;
            }
        }
        listaUtenti = listaUtenti->next;
    }

    if(controllo == 1){
        printf("LOGIN EFFETTUATO CON SUCCESSO \n");
    }

    return utente;
}


void scriviUtenti(utenti *lista, FILE *fp){

    fp = fopen("FileUtenti.txt", "a+");

    while (lista != NULL) {
        if (lista->next != NULL) {
            fprintf(fp, "%s\t%s\t%d\n", lista->nome, lista->password, lista->saldo);
        }
        lista = lista->next;
    }

    fclose(fp);
}


void aggiornaSaldo(utenti *lista, int saldo, char nome[20], char password[20]) {
    FILE *fp;
    utenti *nuovaListaUtenti;
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



utenti *inserisciInListaUtenti(utenti *lista, utenti *utente);
utenti *leggiFileUtenti(FILE *fp);
void scriviSuFileListaUtenti(utenti *lista, FILE *fp);
utenti *signIn(FILE *fp);
void stampaListaUtenti(utenti *lista);
utenti *signUp(utenti *listaUtenti, char nome[20], char password[20]);
void scriviUtenti(utenti *lista, FILE *fp);
void aggiornaSaldo(utenti *lista, int saldo, char nome[20], char password[20]);
