/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include "thash.h"

TH *InitTH(size_t M, TFHash fh) /*NONE*/
{
    TH *h = (TH *)calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }
    h->v = (TLG *)calloc(M, sizeof(TLG));
    if (!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }
    h->M = M;
    h->fh = fh;
    return h;
}

void DistrTH(TH **ah, TF elib_elem)
{
    TLG *p, el, aux;

    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        /* daca exista elemente corespunzatoare acestui hash
         * eliberam info din celula si apoi eliberam celula */
        for (el = *p; el != NULL;) {
            aux = el;
            el = el->urm;
            elib_elem(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}
