/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tlg.h"
#include "thash.h"
#include "cuvinte.h"
#define MAX 100

int main(int argc, char *argv[])
{
	FILE *input = fopen(argv[1], "r");
	/* variabile folosite pentru determinarea cerintei */
	char *cerinta, *p;
	size_t dim = sizeof(char) * MAX;
	cerinta = (char *)malloc(dim);

	/* generare tabela hash goala + verificare */
	TH *h = NULL;
	h = GenerareHash();
	if (h == NULL) {
		printf("Tabela hash nu a putut fi generata\n");
		return 0;
	}

	/* citim linii cat timp intalnim "insert" sau "print" */
	while (getline(&cerinta, &dim, input) > 0) {
		p = strtok(cerinta, " \n");
		if (p != NULL) {
			/* task inserare in tabela hash */
			if (strcmp(p, "insert") == 0) {
				p = strtok(NULL, " \n.?!,");
				while (p != NULL) {
					if (isalpha(*p) && strlen(p) >= 3)
						InserareTH(h, p);
					p = strtok(NULL, " \n.?!,");
				}
			} else if (strcmp(p, "print") == 0) {
				p = strtok(NULL, " \n.?!,");
				if (p) {
					/* task print c n */
					if (isalpha(p[0])) {
						char c = p[0];
						p = strtok(NULL, " \n.?!,");
						int n = atoi(p);
						PrintCN(h, c, n);
					}

					/* task print n */
					else if (isdigit(p[0])) {
						int n = atoi(p);
						PrintAllMax(h, n);
					}
				} else { /* task printare totala */
					PrintAll(h);
				}
			} else { /* operatie invalida */
				free(cerinta);
				DistrTH(&h, EliberareLung);
				fclose(input);
				return 0;
			}
		} else { /* am citit o linie vida */
			free(cerinta);
			DistrTH(&h, EliberareLung);
			fclose(input);
			return 0;
		}
	}

	/* eliberare memorie */
	free(cerinta);
	DistrTH(&h, EliberareLung);
	fclose(input);
	return 0;
}
