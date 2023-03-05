# Tema1-SDA

SDA = Stucturi de date si algoritmi

## Rezumat
- Am folosit resursele prezente in laboratorul 4, corespunzator tabelelor hash si listelor generice simplu inlantuite.
- In main.c am generat tabela hash si am analizat tipurile de cerinte pe care le puteam primi; am folosit strtok pentru
a imparti o cerinta data in cuvinte.
- Pentru fiecare cerinta am creat cate o functie si la final am eliberat memoria alocata pe parcurs.

## Comenzi
- Pentru partea de inserare in tabela hash creata (prin functia GenerareHash), am creat 2 functii sugestive (InserareCuvant si
InserareTH) care sunt impartite la randul lor pe mai multe cazuri ce pot fi intalnite (acestea sunt mentionate in comentarii).
- Pentru comanda "print", am creat 3 functii: PrintWords, PrintLen si PrintAll, corespunzatoare fiecarui tip de structura:
lista generica de cuvinte, lista generica de lungimi de cuvinte (unde va fi ulterior apelata PrintWords) si tabela hash
(in care va fi apelata PrintLen).
- Pentru comanda "print c n", am creat o singura functie in plus (PrintCN), unde am precizat modul in care va fi filtrata
informatia si am folosit functiile deja existente: PrintLen si PrintWords.
- Pentru comanda "print n", am creat functiile prezente in fisierul printN.c, folosite pentru a testa conditiile de
existenta in tabela hash, respectiv in fiecare sublista (corespunzatoare literelor alfabetului), ce are numarul de aparitii <= n.
Daca erau indeplinite conditiile, atunci in mod analog ca la "print" erau apelate functiile de printare create pentru fiecare tip
de structura in parte.

## Detalii
- Cele 3 printari au structuri diferite.
- Pentru fiecare functie creata exista o explicatie pe scurt in fisierele .h.

## Punctaj obtinut

= Tema 1 SD HashTable =

[in0.txt]...........................................passed  [05/85]
[VALGRIND: in0.txt].................................passed  [02/85]
[in1.txt]...........................................passed  [05/85]
[VALGRIND: in1.txt].................................passed  [02/85]
[in2.txt]...........................................passed  [05/85]
[VALGRIND: in2.txt].................................passed  [02/85]
[in3.txt]...........................................passed  [10/85]
[VALGRIND: in3.txt].................................passed  [02/85]
[in4.txt]...........................................passed  [10/85]
[VALGRIND: in4.txt].................................passed  [02/85]
[in5.txt]...........................................passed  [10/85]
[VALGRIND: in5.txt].................................passed  [02/85]
[in6.txt]...........................................passed  [10/85]
[VALGRIND: in6.txt].................................passed  [02/85]
[in7.txt]...........................................passed  [10/85]
[VALGRIND: in7.txt].................................passed  [02/85]
[in8.txt]...........................................passed  [10/85]
[VALGRIND: in8.txt].................................passed  [02/85]
[in9.txt]...........................................passed  [10/85]
[VALGRIND: in9.txt].................................passed  [02/85]

                                           Total: [105/85]
