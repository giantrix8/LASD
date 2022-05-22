#define LenC 20
#define e_accentata 138
#define a_accentata 160
#define u_accentata 151
#define dollaro 36


typedef struct  AlberoCitta{
    struct Citta *citta;
    struct AlberoCitta *dx;
    struct AlberoCitta *sx;
}AlberoCitta;

typedef struct Citta {
    char nome[LenC];
    short aereo;
    short treno;
    struct ListaNext *ListaAereo;
    struct ListaNext *ListaTreno;
}Citta;
typedef struct ListaNext{
    char citta[LenC];
    struct ListaNext *next;
}ListaNext;

//IMPLEMENTA ALBERO UTENTI