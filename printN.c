/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "tlg.h"
#include "thash.h"
#include "cuvinte.h"

int LungimeaN(TLG *cuvinte, int n)
{
    TLG p = *cuvinte;
    for (; p != NULL; p = p->urm) {
        TCuv *aux = (TCuv *)(p->info);
        if (aux->apar <= n)
            return 1;
    }
    return 0;
}

int LiteraN(TLG *litera, int n)
{
    TLG p = *litera;
    for (; p != NULL; p = p->urm)
        if (LungimeaN(&(((TLung)(p->info))->cuvinte), n))
            return 1;
    return 0;
}

void PrintWordsN(TLG *words, int n)
{
    TLG p = *words;
    TCuv aux;
    for (; p != NULL; p = p->urm) {
        aux = *((TCuv *)(p->info));
        if (aux.apar <= n) {
            printf("%s/%d", aux.cuv, aux.apar);
            if (LungimeaN(&(p->urm), n))
                printf(", ");
            else
                printf(")");
        }
    }
}

void PrintLenN(TLG *lungime, int n)
{
    TLung aux = (TLung)((*lungime)->info);
    printf("(%d: ", aux->lung);
    PrintWordsN(&(aux->cuvinte), n);
}

void PrintAllMax(TH *a, int n)
{
    TLG p;
    int i;
    for (i = 0; i < a->M; i++)
        /* cuvinte cu litera data care au >n aparitii*/
        if (a->v[i] != NULL && LiteraN(&(a->v[i]), n)) {
            printf("pos%d: ", i);
            for (p = a->v[i]; p != NULL; p = p->urm) {
                /* cuvinte de lungimea data cu >n aparitii*/
                if (LungimeaN(&(((TLung)(p->info))->cuvinte), n))
                    PrintLenN(&p, n);
            }
            printf("\n");
        }
}
