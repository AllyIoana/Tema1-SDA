/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include "tlg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* structura de cuvinte */
typedef struct {
	char *cuv;
	int apar;
} TCuv;

/* structura sublistelor de lungime a cuvintelor*/
typedef struct {
    TLG cuvinte;
    int lung;
} TL, *TLung;

/* functii pentru generare tabela de cuvinte */
int codHash(void *element); /* fh */
TH *GenerareHash(); /* generare tabela hash goala */
/* inserare in lista lungimilor */
void InserareCuvant(TLung lungime, char *cuvant);
void InserareTH(TH *a, void *cuvant); /* pentru comanda insert */

/* functii pentru printare */
void PrintWords(TLG *words); /* printeaza o lista de cuvinte */
void PrintLen(TLG *lungime); /* printeaza o lista de lungimi de cuvinte */
void PrintAll(TH *a); /* pentru comanda print */
void PrintCN(TH *a, char lit, int lg); /* pentru comanda print c n */
int LungimeaN(TLG *lungime, int n); /* verifica daca numarul de aparitii <= n */
/* verifica daca exista cuvinte potrivite pentru o litera */
int LiteraN(TLG *litera, int n);
/* printeaza cuvintele dintr-o lista de cuvinte */
void PrintWordsN(TLG *words, int n);
/* printeaza cuvintele corespunzatoare unei lungimi */
void PrintLenN(TLG *lungime, int n);
void PrintAllMax(TH *a, int n); /* pentru comanda print n */

/* functii pentru eliberarea memoriei */
void EliberareCuv(void *cuvant); /* eliberarea unei liste de cuvinte */
/* eliberarea unei liste de lungimi de cuvinte */
void EliberareLung(void *lungime);
