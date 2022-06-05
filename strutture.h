#define LenC 20
#define e_accentata 138
#define a_accentata 160
#define u_accentata 151
#define dollaro 36
#define dim1 20
#define CodAdmin 100


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

typedef struct utenti {
    char 	*nickname;
    char 	*password;
    float 	saldo;
    struct 	albero_Utenti* sx;
    struct 	albero_Utenti* dx;
} utenti;

typedef struct GrafoHotel{
    int dim;
    int indice;
    struct Hotel **hotel; //il primo hotel nel vettore è il più vicino alla stazione/aereoporto
}GrafoHotel;

typedef struct Arco{
    int distanza;
    struct Hotel *destinanzione;
    struct Arco *next;
}Arco;

typedef struct Hotel{
    char nome[dim1];
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

//CITTA------------------------------------------------------------------------------------------
AlberoCitta *carica_grafo(AlberoCitta *radice);
void salva_grafo(AlberoCitta *radice);
void InserisciListaAdiacenza(AlberoCitta *radice,char *partenza, char *destinazione, float prezzo, float tempo,short tipo);
AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome);
void contaCitta(AlberoCitta *radice, int *n);
AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome,int *errore);
void StampaCitta(AlberoCitta *radice);
//HOTEL------------------------------------------------------------------------------------------
void CaricaHotel(AlberoCitta *radice);
Hotel *CercaHotel(AlberoCitta *radice, char *NomeCitta, char *NomeAlbergo);
//OPERAZIONI UTENTE------------------------------------------------------------------------------
utenti *LoginRegistrazione(utenti **radice,int *errore);
Prenotazione *prenotaViaggio(AlberoCitta *radice, Citta *partenza, Citta *arrivo, int tipo, int modo);
//GESTIONE NOTIFICHE-----------------------------------------------------------------------------
void crea_notifica(Citta *citta, int tipo);
void mostra_notifiche(AlberoCitta *radice);
