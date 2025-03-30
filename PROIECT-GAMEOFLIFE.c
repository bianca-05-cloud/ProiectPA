#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
//Functie pentru citire matrice
void citire_matrice(char** m, FILE* in, int N, int M)
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            fscanf(in, " %c", &m[i][j]);
        }
    }
}
 
//Functie pentru afisare matrice
void afisare_matrice(char** m, int N, int M)
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}
 
//Functie pentru numararea vecinilor vii ai unei celule
int vecinii(char** m, int N, int M, int i, int j)
{
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};  // deplasare pe linie
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};  // deplasare pe coloana
 
    int d;
    int aux = 0;  // contor pentru vecinii vii
 
    // parcurg fiecare din cei 8 vecini posibili ai unei celule
    for(d = 0; d < 8; d++)
    {
        int ni = i + x[d];  // calculez linia vecinului
        int nj = j + y[d];  // calculez coloana vecinului
 
        // verific daca vecinul este in interiorul matricei
        if(ni >= 0 && ni < N && nj >= 0 && nj < M)
        {
            // verific daca vecinul este viu
            if(m[ni][nj] == 'X')
            {
                aux++;
            }
        }
    }
 
    return aux;  // returnez nr total de vecini vii
}
 
//functie de actualizare a matricei originale
void actualizare_matrice(char** m, char** q, int N, int M)
{
    int i, j, vecinii_vii;
 
    // Calculăm noile stări în matricea auxiliară q
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            vecinii_vii = vecinii(m, N, M, i, j);
 
            if(m[i][j] == 'X' && (vecinii_vii < 2 || vecinii_vii > 3))
            {
                q[i][j] = '+';  // celula moare
            }
            else if(m[i][j] == '+' && vecinii_vii == 3)
            {
                q[i][j] = 'X';  // celula devine vie
            }
            else
            {
                q[i][j] = m[i][j];  // celula rămâne neschimbată
            }
        }
    }
 
    // Copiem noile stări din matricea auxiliară în matricea principală
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            m[i][j] = q[i][j];  // actualizăm matricea principală
        }
    }
}
 
int main(int argc, char* argv[])
{
    int T, N, M, K;
    int k;
 
    FILE *in, *out;
    in = fopen(argv[1], "rt");
    //printf("Fisierul de in este: %s\n", argv[1]);
 
    if(in == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
 
    out = fopen(argv[2], "wt");
    //printf("Fisierul de out este: %s\n", argv[2]);
 
    if(out == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }
 
    fscanf(in, "%d", &T);  
    fscanf(in, "%d %d", &N, &M);  
    fscanf(in, "%d", &K);  
 
    // Alocăm memorie pentru matricea principală (m) și matricea auxiliară (q)
    char** m = (char**)malloc(N * sizeof(char*));
    char** q = (char**)malloc(N * sizeof(char*));
    int i, j;
    for(i = 0; i < N; i++)
    {
        m[i] = (char*)malloc(M * sizeof(char));
        q[i] = (char*)malloc(M * sizeof(char));
    }
 
    citire_matrice(m, in, N, M);  // citim matricea inițială
    fclose(in);
 
    // Rulez jocul pentru K generații
    for(k = 0; k <= K; k++)
    {
 
        // Scriem rezultatul pentru generația curentă în fișierul de ieșire
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < M; j++)
            {
                fprintf(out, "%c", m[i][j]);  // scriem în fișier
            }
            fprintf(out, "\n");
        }
 
        // Dacă nu este ultima generație, adăugăm o linie goală
        fprintf(out, "\n");
 
        actualizare_matrice(m, q, N, M);
    }
 
    fclose(out);
 
    // Eliberăm memoria alocată
    for(i = 0; i < N; i++)
    {
        free(m[i]);
        free(q[i]);
    }
 
    free(m);
    free(q);
 
    return 0;
}