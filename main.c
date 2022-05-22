#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

int main() {
    system("color 0e");
    utenti *AlberoUtenti = NULL; //Albero utenti contiene tutti gli utenti
    utenti *utente; //contiene l'utente che utilizzerà l'applicazione
    int errore = 0;
    utente = LoginRegistrazione(&AlberoUtenti, &errore);
    if (errore==CodAdmin){
        //ALLORA è UN ADMIN
        //MENU' ADMIN ETC...
    }
    else{
        //MENU' NON ADMIN
    }
}