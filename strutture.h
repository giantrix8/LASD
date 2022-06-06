#define LenC 20
#define e_accentata 138
#define a_accentata 160
#define u_accentata 151
#define dollaro 36
#define dim1 20
#define CodAdmin 12345


typedef struct  AlberoCitta{
    struct Citta *citta;
    struct AlberoCitta *dx;
    struct AlberoCitta *sx;
} AlberoCitta;

typedef struct Citta {
    int key;
    char nome[LenC];
    short aereo;
    short treno;
    struct ListaNext *ListaAereo;
    struct ListaNext *ListaTreno;
    struct GrafoHotel *Grafohotel;
} Citta;

typedef struct ListaNext{
    Citta *citta;
    struct ListaNext *next;
    float prezzo;
    float durata;
} ListaNext;

typedef struct GrafoHotel{
    int dim;
    struct Hotel **hotel; //il primo hotel nel vettore è il più vicino alla stazione/aereoporto
}GrafoHotel;

typedef struct Arco{
    int distanza;
    struct Hotel *destinanzione;
    struct Arco *next;
}Arco;

typedef struct Hotel{
    char nome[dim1];
    int key;
    float prezzo;
    struct Arco *adiacenti;
}Hotel;

typedef struct DjkElem{
    Citta *citta;
    float peso[2];
    int tipo; // 0 per aereo, 1 per treno, 2 per non raggiungibile
    Citta* prev;
} DjkElem;

typedef struct path {
    Citta *citta;
    int tipo; //0 per aereo, 1 per treno
    struct path *next;
} Path;

typedef struct Prenotazione{
    Hotel *hotel;
    Path *viaggio;
    float durata;
    float prezzo;
} Prenotazione;
typedef struct Utenti{
    char nome[dim1];
    char password[dim1];
    int saldo;
    struct Utenti *next;
}Utenti;

//CITTA------------------------------------------------------------------------------------------
AlberoCitta *carica_grafo(AlberoCitta *radice);
void salva_grafo(AlberoCitta *radice);
void InserisciListaAdiacenza(AlberoCitta *radice,char *partenza, char *destinazione, float prezzo, float tempo,short tipo);
AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome);
void contaCitta(AlberoCitta *radice, int *n);
AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome,int *errore);
void StampaCitta(AlberoCitta *radice);
void ControllaCittaInraggiungibile(AlberoCitta *radice, AlberoCitta *CittaCorrente);
//HOTEL------------------------------------------------------------------------------------------
void CaricaHotel(AlberoCitta *radice);
Hotel *CercaHotel(AlberoCitta *radice, char *NomeCitta, char *NomeAlbergo);
Hotel *SceltaHotel(AlberoCitta *radice, char *NomeCitta);
void StampaHotel (Hotel **hotel, int dim);
void SalvaGrafoHotel(AlberoCitta *radice);
void djkHotel(GrafoHotel *graph, Hotel *arrivo);
//OPERAZIONI UTENTE------------------------------------------------------------------------------
Utenti *signIn(FILE *fp);
Utenti *signUp(Utenti *lista);
Prenotazione *prenotaViaggio(AlberoCitta *radice, char *cittap, char *cittaa, int tipo, int modo);
Utenti *inserisciInListaUtenti(Utenti *lista, Utenti *utente);
Utenti *leggiFileUtenti(FILE *fp);
void scriviSuFileListaUtenti(Utenti *lista, FILE *fp);
void scriviUtenti(Utenti *lista, FILE *fp);
void aggiornaSaldo(Utenti *lista,Utenti *utente, float saldo);
void RicaricaConto(Utenti *utente);
//GESTIONE NOTIFICHE-----------------------------------------------------------------------------
void crea_notifica(Citta *citta);
void mostra_notifiche(AlberoCitta *radice);
void Logo();
