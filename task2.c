#include"header.h"

int main(int argc, char* argv[]) 
{
    int T, N, M, K;
    char** matricea_initiala;

    FILE *in, *out;
    in = fopen(argv[1], "rt");

    if(in == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }

    out = fopen(argv[2], "wt");

    if(out == NULL)
    {
        puts("Fisierul nu poate fi deschis");
        exit(1);
    }

    //citim elementele de input din fisier
    fscanf(in, "%d", &T);  
    printf("%d", T);
    // Dacă T nu este 2, ieșim din program
    if (T != 2) {
       // printf("Trebuie să rulezi doar taskul 2\n");
        fclose(in);
        fclose(out);
        return 0;
    }

    fscanf(in, "%d %d", &N, &M);  
    fscanf(in, "%d", &K);


        //aloc dinamic matricea initiala
        matricea_initiala = (char**) malloc (N * sizeof(char*));

    int i, j;

    for(i=0;i<N;i++)
    {
        matricea_initiala[i]=(char*) malloc (M * sizeof(char));
        
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            fscanf(in, " %c", &matricea_initiala[i][j]);
            //printf("matricea_initiala[%d][%d] = %c\n", i, j, matricea_initiala[i][j]);

        }
    }

    fclose(in);

    //voi creea stiva care stocheaza generatiile si elementele care se schimba
    
    generatie* stiva = NULL;
    int k;
    //rulez ptr K generatii
    for(k=1; k<=K;k++)
    {
        char** nou = copie(matricea_initiala, N, M);
        celula* mode = NULL;//pointer catre inceputul unei liste de tip celula
                            //aceasta lista va contine toate celulele care s au modificat intr o anumita generatie
                            //=lista modificari pentru generatia curenta
        for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                int vecini=vecinii(matricea_initiala,N,M,i,j);//calc vecinii

                if((matricea_initiala[i][j] == 'X' && (vecini < 2 || vecini > 3)) || (matricea_initiala[i][j] == '+' && vecini == 3))//aplic regulile din GOL
                {
                    nou[i][j]=(matricea_initiala[i][j] == 'X') ? '+' : 'X';//transf GOL
                    adaugare(&mode, i, j);//creeaza un nod nou cu coord i, j si adauga acel nod in lista
                    //printf("Modificare: (%d, %d)\n", i, j); // DEBUG
                }
            }

        }

        if(mode!=NULL)

        {
        push(&stiva, k, mode);//adauga o noua generatie in varful stivei
        //printf("Push: generatie %d, modificari detectate.\n", k);
        }

        else

        {
        //printf("Stop la gen %d: fara modificari.\n", k);
        eliberare_matrice(nou, N);
        break;
        }
        eliberare_matrice(matricea_initiala, N);
        matricea_initiala=nou;
    }

    //printf("Afisez generatiile in fisier...\n");

    afisare(stiva, out);

    fclose(out);
    eliberare_matrice(matricea_initiala, N);

    return 0;
}