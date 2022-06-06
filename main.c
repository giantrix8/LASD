#include <stdio.h>
#include <stdlib.h>
#include "strutture.h"

int main() {
    system("color 0e");
    int op = 1, flag = 0, opzioneViaggio, offerta, k = 1, acquisto;
    char partenza[20], destinazione[20], hotel[20];
    AlberoCitta *grafocitta=NULL;
    Utenti *utenteInQuestione, *lista;
    Prenotazione *booking;
    FILE *fp;
    //Fine dichiarazioni----------------------------------------------------------------------------------
    Logo();
    lista= leggiFileUtenti(fp);
    grafocitta= carica_grafo(grafocitta);
    CaricaHotel(grafocitta);

    while(op != 3){
        printf("Inserisca 1 per loggarti 2 per registrarti 3 per uscire : ");
        scanf("%d", &op);

        if(op == CodAdmin){
            ControllaCittaInraggiungibile(grafocitta,grafocitta);
            mostra_notifiche(grafocitta);
            break;
        } else if(op == 1){
            utenteInQuestione= signUp(lista);
            flag = 1;

            break;
        } else if(op == 2){
            utenteInQuestione= signIn(fp);
            flag = 1;
            break;
        }
        else if(op == 3){
            printf("GRAZIE & ARRIVEDERCI %c",1);
            exit(1);
        } else printf("C'%c stato un errore, riprova\n",e_accentata);

        printf("\n");
    }
    if(flag == 1) {
        do {
            printf("\nInserisci 1 per vedere le mete, 0 per ricaricare il tuo saldo");
            scanf("%d",&op);
            if (op==0){
                RicaricaConto(utenteInQuestione);
            }
            printf("Le mete disponibili sono le seguenti : ");
            StampaCitta(grafocitta);
            printf("\nInserisca la citt%c di partenza : ",a_accentata);
            scanf("%s", partenza);
            printf("Inserisca la meta di destinazione : ");
            scanf("%s", destinazione);
            do {
                printf("Come opzioni di viaggio ti offriamo la possibilit%c di viaggiare in aereo, in treno e modalit%c mista",
                       a_accentata);
                printf("\nInserisca 0 per viaggiare in aereo 1 per viaggiare in treno, 2 per la modalit%c mista : ",
                       a_accentata,a_accentata);
                scanf("%d", &opzioneViaggio);
            } while (opzioneViaggio < 0 && opzioneViaggio > 2);
            do {
                printf("Vuoi il modo pi%c veloce o quello pi%c economico?", u_accentata, u_accentata);
                printf("\nInserisci 0 per il metodo veloce, 1 per quello economico");
                scanf("%d", &op);
            } while (op != 0 && op != 1);
            booking = prenotaViaggio(grafocitta, partenza, destinazione, opzioneViaggio, op);
            if (booking == NULL) {
                printf("Ops... Il viaggio non %c disponibile, inserisci 0 per riprovare o 1 per uscire", e_accentata);
                scanf("%d", &op);
            }
            if (op == 1) {
                SalvaGrafoHotel(grafocitta);
                salva_grafo(grafocitta);
                exit(1);
            }
        } while (booking == NULL);
        printf("\nRiepilogo prenotazione :");
        printf("\nPartenza ->%s\nDestinazione ->%s Hotel:%s\nprezzo->%.2f%c",partenza,destinazione,booking->hotel->nome,booking->prezzo,dollaro);
        printf("\nVuoi confermare? 1 per Si e 0 per No");
        scanf("%d",&op);
        if(op==1){
            aggiornaSaldo(lista,utenteInQuestione,booking->prezzo);
            printf("\nBuon Viaggio %c",1);
        }
    }
    SalvaGrafoHotel(grafocitta);
    salva_grafo(grafocitta);
    exit(0);
}



