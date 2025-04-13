#include"header.h"

// Adaugă un element în vârful stivei
void push (generatie** stiva, int k, celula* x) {
    generatie* newNode = (generatie*)malloc(sizeof(generatie));
    newNode->k = k;
    newNode->x = x;
    newNode->next=*stiva;
    *stiva = newNode;
}

//Functie pentru numararea vecinilor vii ai unei celule(task 1)
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

// adauga o celula in lista modificarilor, mentine ordinea dupa linie si coloana
void adaugare(celula** head, int l, int c)
{
    celula* new = (celula*)malloc(sizeof(celula));//aloca memorie pentru noua celula
    new->l=l;
    new->c=c;
    new->next=NULL;

    if (*head == NULL || l < (*head)->l || (l == (*head)->l && c < (*head)->c))


    {
        new->next = *head;//leaga vechiul head dupa noul nod
        *head = new;//actualizeaza head
        return;
    }

    celula* curent = *head;
    while( curent->next && (curent->next->l < l || (curent->next->l == l && curent->next->c < c)))
    //avansam prin lista atata timp cat urm element este "<" (l,c)
    {
        curent=curent->next;
    }
    new->next = curent->next;//leg noul nod dupa curent
    curent->next = new;//leg vechiul next dupa new
}

//copiere matrice caracter cu caracter

char** copie(char** m, int N, int M)
{   int i, j;
    char** aux = (char**)malloc(N*sizeof(char*));
    for(i=0;i<N;i++)
    {
        aux[i]=(char*)malloc(M*sizeof(char));
        for(j=0;j<M;j++)
        {
            aux[i][j]=m[i][j];
        }
    }
    return aux;
}

void eliberare_matrice(char** m, int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        free(m[i]);
    }
    free(m);
}

//afisarea in ordine a stivei cu coordonatele celulelor modificate de la 1 la K

void afisare(generatie* stiva, FILE* out)
{
    if(stiva==NULL)
    {
        return;
    }

    afisare(stiva->next, out);

    fprintf(out, "%d:", stiva->k);
    celula* curent = stiva->x;
    while(curent)
    {
        fprintf(out, "(%d, %d);", curent->l, curent->c);
        curent = curent->next;
    }

    fprintf(out, "\n");
}


