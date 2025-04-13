#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//lista din care e alcatuita stiva
struct celula
{
    int l;
    int c;
    struct celula *next;
};

typedef struct celula celula;

//stiva propriu-zisa, prin care reprezentam cate un element corespunzator unei generatii

struct generatie
{   int k;  //numarul generatiei
    celula* x;//lista de celule modificate din aceasta generatie
    struct generatie* next;//pointer catre urmatoarea generatie din stiva
};

typedef struct generatie generatie;

void push (generatie** stiva, int k, celula* x);
int vecinii(char** m, int N, int M, int i, int j);
void adaugare(celula** head, int l, int c);
char** copie(char** m, int N, int M);
void eliberare_matrice(char** m, int N);
void afisare(generatie* stiva, FILE* out);

