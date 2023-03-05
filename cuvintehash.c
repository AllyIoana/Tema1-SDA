/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include "cuvinte.h"
#include <string.h>

int codHash(void *element)
{
	char litera = ((char *)element)[0];
	if (litera >= 'a')
		return litera - 'a';
	return litera - 'A';
}

TH *GenerareHash()
{
	TH *h = NULL;
	TLG p;
	int rez;

	/* calcul dimensiuni maxime pt tabela hash */
	size_t M = ('Z' - 'A' + 1);

	/* initializare tabela hash */
	h = (TH *)InitTH(M, codHash);
	if (h == NULL)
		return NULL;
	return h;
}

void InserareCuvant(TLung lungime, char *cuvant)
{
	TLG elem = lungime->cuvinte;

	/* primul cuvant de lungimea data */
	if (elem == NULL) {
		TCuv *aux;
		aux = (TCuv *)malloc(sizeof(TCuv));
		if (aux == NULL) {
			printf("Nu s-a alocat spatiu\n");
			return;
		}
		aux->apar = 1;
		aux->cuv = (char *)malloc(sizeof(char) * (strlen(cuvant) + 1));
		strcpy(aux->cuv, cuvant);
		Ins_IncLG(&elem, aux);
		lungime->cuvinte = elem;
		return;
	}

	/* exista deja cuvantul in lista */
	TLG prec = NULL;
	for (elem = lungime->cuvinte; elem != NULL; elem = elem->urm) {
		/* primul cuvant */
		if (elem == lungime->cuvinte) {
			TCuv *aux = (TCuv *)elem->info;
			if (strcmp(aux->cuv, cuvant) == 0) {
				aux->apar++;
				return;
			}
		}

		/* nu e primul cuvant */
		TCuv *aux = (TCuv *)elem->info;
		if (strcmp(aux->cuv, cuvant) == 0) {
			aux->apar++;
			TLG p, precp = NULL;
			for (p = lungime->cuvinte; p != elem; p = p->urm) {
				if (((TCuv *)(p->info))->apar < aux->apar ||
					(((TCuv *)(p->info))->apar == aux->apar &&
					 strcmp(((TCuv *)(p->info))->cuv, aux->cuv) > 0)) {
					prec->urm = elem->urm;
					if (p == lungime->cuvinte) {
						elem->urm = p;
						lungime->cuvinte = elem;
						return;
					}
					precp->urm = elem;
					elem->urm = p;
					return;
				}
				precp = p;
			}
			return;
		}
		prec = elem;
	}

	/* lista nevida, cuvant nou de adaugat */
	prec = NULL;
	for (elem = lungime->cuvinte; elem != NULL; elem = elem->urm) {
		TCuv *aux = (TCuv *)elem->info;
		TCuv *info = (TCuv *)malloc(sizeof(TCuv));
		if (info == NULL) {
			printf("Nu s-a alocat spatiu\n");
			return;
		}
		info->cuv = (char *)malloc(sizeof(char) * (strlen(cuvant) + 1));
		if (info->cuv == NULL) {
			printf("Nu s-a alocat spatiu\n");
			free(info);
			return;
		}
		if (aux->apar == 1 && strcmp(aux->cuv, cuvant) > 0) {
			info->apar = 1;
			strncpy(info->cuv, cuvant, strlen(cuvant) + 1);
			if (elem != lungime->cuvinte) {
				Ins_IncLG(&elem, info);
			} else {
				Ins_IncLG(&elem, info);
				lungime->cuvinte = elem;
			}
			if (prec != NULL)
				prec->urm = elem;
			return;
		}
		free(info->cuv);
		free(info);
		prec = elem;
	}

	/* altfel */
	TCuv *aux = (TCuv *)malloc(sizeof(TCuv));
	if (aux == NULL) {
		printf("Nu s-a alocat spatiu\n");
		return;
	}
	aux->apar = 1;
	aux->cuv = (char *)malloc(sizeof(char) * (strlen(cuvant) + 1));
	if (aux->cuv == NULL) {
		printf("Nu s-a alocat spatiu\n");
		free(aux);
		return;
	}
	strcpy(aux->cuv, cuvant);
	Ins_IncLG(&elem, (void *)(aux));
	if (prec != NULL)
		prec->urm = elem;
}

void InserareTH(TH *a, void *cuvant)
{
	int cod = a->fh(cuvant), lungime;
	TLG elem, prec = NULL;
	TLung aux;
	lungime = strlen((char *)(cuvant));
	elem = a->v[cod];
	for (; elem != NULL; elem = elem->urm) {
		aux = (TLung)(elem->info);
		if (aux->lung == lungime) {
			/* mai avem cuvinte de aceeasi lungime */
			InserareCuvant(aux, (char *)(cuvant));
			return;
		}
		if (aux->lung > lungime) {
			/* inseram inaintea unui element o noua lungime*/
			TLung new = (TLung)malloc(sizeof(TL));
			if (new == NULL) {
				printf("Nu s-a alocat spatiu\n");
				return;
			}
			new->lung = lungime;
			new->cuvinte = NULL;
			if (elem == a->v[cod]) {
				Ins_IncLG(&elem, new);
				a->v[cod] = elem;
			} else {
				Ins_IncLG(&elem, new);
			}
			InserareCuvant((TLung)(elem->info), (char *)(cuvant));
			if (prec != NULL)
				prec->urm = elem;
			return;
		}
		prec = elem;
	}
	/* inseram la final o noua lungime/ primul cuvant */
	TLung new = (TLung)malloc(sizeof(TL));
	if (new == NULL) {
		printf("Nu s-a alocat spatiu\n");
		return;
	}
	new->lung = lungime;
	new->cuvinte = NULL;
	elem = NULL;
	if (!Ins_IncLG(&elem, new)) {
		free(new);
		printf("Nu s-a inserat in lista!\n");
		return;
	}
	if (prec != NULL)
		prec->urm = elem;
	if (!a->v[cod]) /* doar pentru primul element */
		a->v[cod] = elem;
	InserareCuvant((TLung)(elem->info), (char *)(cuvant));
	new = (TLung)(elem->info);
	return;
}

void PrintWords(TLG *words)
{
	if (!*words) {
		printf("Lista vida\n");
		return;
	}
	TLG p = *words;
	TCuv aux;
	for (; p != NULL; p = p->urm) {
		aux = *((TCuv *)(p->info));
		printf("%s/%d", aux.cuv, aux.apar);
		if (p->urm == NULL)
			printf(")");
		else
			printf(", ");
	}
}

void PrintLen(TLG *lungime)
{
	if (!*lungime) {
		printf("Lista vida\n");
		return;
	}
	TLung aux = (TLung)((*lungime)->info);
	printf("(%d:", aux->lung);
	PrintWords(&(aux->cuvinte));
}

void PrintAll(TH *a)
{
	TLG p;
	int i;
	for (i = 0; i < a->M; i++)
		if (a->v[i] != NULL) {
			printf("pos %d: ", i);
			for (p = a->v[i]; p != NULL; p = p->urm)
				PrintLen(&p);
			printf("\n");
		}
}

void PrintCN(TH *a, char lit, int lg)
{
	TLG p;
	int cod = a->fh(&lit);
	if (a->v[cod] != NULL) {
		for (p = a->v[cod]; p != NULL; p = p->urm) {
			TLung lungime = (TLung)(p->info);
			if (lungime->lung == lg) {
				PrintLen(&p);
				break;
			}
		}
		if (p != NULL)
			printf("\n");
	}
}

void EliberareCuv(void *cuvant)
{
	TCuv *aux = (TCuv *)cuvant;
	free(aux->cuv);
	free(aux);
}

void EliberareLung(void *lungime)
{
	TLung aux = (TLung)lungime;
	DistrugeLG(&(aux->cuvinte), EliberareCuv);
	free(aux);
}
