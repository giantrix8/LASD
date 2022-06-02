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
    struct Hotel *ListaHotel;
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

typedef struct Hotel{
    char nome[dim1];
    struct Hotel *next;
} Hotel;

typedef struct DjkElem{
    Citta *citta;
    float peso[2];
    Citta* prev;
} DjkElem;

typedef struct path {
    Citta *citta;
    struct path *next;
} Path;

utenti *LoginRegistrazione(utenti **radice,int *errore);
AlberoCitta *EliminaNodo(AlberoCitta *padre,AlberoCitta *radice,char *nome);
AlberoCitta *carica_grafo(AlberoCitta *radice);
void salva_grafo(AlberoCitta *radice);
AlberoCitta *EliminaCitta(AlberoCitta *testa,char *nome);
int contaCitta(AlberoCitta *radice);
AlberoCitta *CercaNodo(AlberoCitta *radice,char *nome,int *errore);
Path *FindMinPath(AlberoCitta *radice, Citta *partenza, Citta *arrivo, int tipo, int modo);
void stampa_path(Path *cammino);
