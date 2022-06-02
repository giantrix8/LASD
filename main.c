#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

int main() {
    system("color 0e");

    int op = 1, flag = 0, opzioneViaggio, offerta, k = 1, acquisto;
    char partenza[20], destinazione[20], hotel[20];
    utenti *utenteInQuestione, **AlberoUtenti = NULL;
    FILE *fp;

    printf(" --- --- WELCOME ON TRAVELSP --- --- ");
    printf("\n");

    while(op != 3){
        printf("Inserisca 1 per registrarti 2 per loggarti 3 per uscire : ");
        scanf("%d", &op);

        if(op == 12345){
            //Gestisci Admin
            //CONTROLLARE IL FILE DELLE NOTIFICHE
            break;
        } else if(op == 1){
            utenteInQuestione = signIn(AlberoUtenti, fp);
            flag = 1;

            break;
        } else if(op == 2){
            //Loggati
            flag = 1;
            break;
        }
        else if(op == 3){
            printf("GRAZIE & ARRIVEDERCI");
            exit(0);
        } else printf("C'e' stato un errore, riprova\n");

        printf("\n");
    }

    if(flag == 1){
        //se non vogliamo fare il fatto del flag, facciamo un while all'inizio se vogliamo proporre
        //l'acquisto di un altro viaggio alla fine, in modo tale che rimandiamo sopra e poi vediamo come uscire
        while(k){
            printf("Le mete disponibili sono le seguenti : ");
            //stampa mete

            printf("Inserisca la meta di partenza : ");
            scanf("%c", partenza);
            printf("\n");

            printf("Inserisca la meta di destinazione : ");
            scanf("%c", destinazione);
            printf("\n");

            //Controlla destinazione esistente
            //Nel caso esiste k si pone a zero o si mette un break, altrimenti messaggio d'errore e riprovare

            k = 0; //è quì a caso perché altrimenti mi segna un loop, visto che ho messo k ad 1
        }

        printf("Come opzioni di viaggio ti offriamo la possibilità di dì viaggiare sia in aereo che in treno");
        printf("\n");

        printf("Inserisca 1 per viaggiare in aereo 2 per viaggiare in treno : ");
        scanf("%d", &opzioneViaggio);

        if(opzioneViaggio == 1){
            //Gestisti viaggio in aereo
            printf("Di seguito le varie offerte");
            //Scelta economica o più veloce

            printf("Inserisca l'offerta desiderata 1 per quella più economica 2 per quella più veloce : ");
            scanf("%d", &offerta);

            printf("Di seguito le forniamo una lista di hotel per la meta destinazione : ");
            //Stampa i vari hotel della meta destinazione

            printf("Inserisca l'hotel desiderato");
            scanf("%c", hotel);

            printf("Di seguito le indichiamo il modo più veloce per qrrivqre in hotel");
            //Spampa percorso

            printf("Vuoi procedere con l'acquisto? (se si inserire 1, 0 altrimenti");
            scanf("%d", &acquisto);
        }else if(opzioneViaggio == 2){
            //Gestisci viaggio in treno
            printf("Di seguito le varie offerte");
            //Scelta economica o più veloce

            printf("Inserisca l'offerta desiderata 1 per quella più economica 2 per quella più veloce : ");
            scanf("%d", &offerta);

            printf("Di seguito le forniamo una lista di hotel per la meta destinazione : ");
            //Stampa i vari hotel della meta destinazione

            printf("Inserisca l'hotel desiderato");
            scanf("%c", hotel);

            printf("Di seguito le indichiamo il modo più veloce per qrrivqre in hotel");
            //Spampa percorso

            printf("Vuoi procedere con l'acquisto? (se si inserire 1, 0 altrimenti");
            scanf("%d", &acquisto);

            if(acquisto == 1){
                //Aggiornare saldo account o se necessario anche altri file
                printf("Inserisci il pin per poter effettuare il pagamento");
                //pin fittizzio ovviamente che poi decidiamo

                //se pin va a buon fine
                //magari chiediamo anche un pin all'inizio, e facciamo un controllo su quello
                printf("ACQUISTO EFFETTUATO CON SUCCESSO. GRAZIE & ARRIVEDERCI");
                exit(0);
            } else if(acquisto == 0){
                printf("GRAZIE & ARRIVEDERCI");
                exit(0);
            }
        }
    }

}