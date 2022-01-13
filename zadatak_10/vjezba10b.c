#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 250

struct _lista;
typedef struct _lista* pLista;
typedef struct _lista {
	char grad[MAX];
	int populacija;
	pLista next;
} lista;

struct _stablo;
typedef struct _stablo* pStablo;
typedef struct _stablo {
	char drzava[MAX];
	pLista gradovi;
	pStablo lijevo;
	pStablo desno;
} stablo;



pLista StvoriClanListe();
pStablo TraziDrzavu(pStablo, char*);
pStablo StvoriClanStabla(char*, pLista);

int Drzave(pStablo, char*);
int DodajGrad(pLista, char*, int);
pStablo DodajDrzavu(char*, pLista, pStablo);
pLista Gradovi(pLista);
int Ispis(pLista);
int IspisStablo(pStablo);

int Odabir(pStablo);
int IspisGradovi(pLista, int);

int main() {

	pStablo headStablo= NULL;

	headStablo = Drzave(headStablo, "drzave.txt");

	IspisStablo(headStablo);

	Odabir(headStablo);

	return EXIT_SUCCESS;
}

pStablo TraziDrzavu(pStablo p, char* drzava) {
	if (p == NULL) {
		return NULL;
	}
	if (strcmp(drzava, p->drzava) == 0) {
		return p;
	}
	else if (strcmp(drzava, p->drzava) > 0) {
		return TraziDrzavu(p->desno, drzava);
	}
	return TraziDrzavu(p->lijevo, drzava);
}

int Odabir(pStablo headStablo) {
	pStablo q = NULL;
	char temp1[MAX];
	int temp2;
	printf("Unesite ime drzave koju zelite pretraziti: ");
	scanf(" %s", temp1);
	printf("Ispis svih gradova koji imaju broj stanovnika veci od ");
	scanf(" %d", &temp2);
	q = TraziDrzavu(headStablo, temp1);
	if (!q) {
		printf("Zadana drzava ne postoji!");
		return EXIT_FAILURE;
	}
	IspisGradovi(q->gradovi, temp2);
	return EXIT_SUCCESS;
}

int IspisGradovi(pLista headLista, int populacijaX) {
	while (headLista->next != NULL) {
		if (headLista->populacija > populacijaX) {
			printf("%s %d\n", headLista->grad, headLista->populacija);
		}
		headLista = headLista->next;
	}
	return EXIT_SUCCESS;
}

int Ispis(pLista headLista){
	while (headLista->next != NULL) {
		printf("%s %d\n", headLista->grad, headLista->populacija);
		headLista = headLista->next;
	}
	printf("\n\n");
	return EXIT_SUCCESS;
}

pLista StvoriClanListe() {
	pLista q = malloc(sizeof(lista));
	if (q == NULL) {
		printf("Greska pri alokaciji");
		return NULL;
	}
	strcpy(q->grad, "");
	q->populacija = 0;
	q->next = NULL;
	return q;
}

pStablo StvoriClanStabla(char* drzava, pLista gradovi) {
	pStablo q = malloc(sizeof(stablo));

	if (q == NULL) {
		printf("Greska pri alokaciji");
		return NULL;
	}

	q->gradovi = gradovi;
	strcpy(q->drzava, drzava);
	q->lijevo = NULL;
	q->desno = NULL;

	return q;
}

int IspisStablo(pStablo p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}

	IspisStablo(p->lijevo);
	printf("%s gradovi:\n", p->drzava);
	Ispis(p->gradovi->next);
	IspisStablo(p->desno);

	return EXIT_SUCCESS;
}

int Drzave(pStablo headStablo, char* imeDat) {
	pLista gradovi = NULL;
	char imeDrzava[MAX] = "", imeGradoviDat[MAX] = "";

	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %s", imeDrzava, imeGradoviDat);
		gradovi = Gradovi(imeGradoviDat);
		headStablo = DodajDrzavu(imeDrzava, gradovi, headStablo);
	}
	fclose(dat);
	return headStablo;
}

int DodajGrad(pLista headLista, char* grad, int populacija) {
	pLista q = StvoriClanListe();
	strcpy(q->grad, grad);
	q->populacija = populacija;
	while (headLista->next != NULL) {
		if (q->populacija < headLista->next->populacija) {
			break;
		}
		headLista = headLista->next;
	}
	q->next = headLista->next;
	headLista->next = q;
	return EXIT_SUCCESS;
}

pLista Gradovi(char* imeDat) {
	pLista q = NULL;
	q = StvoriClanListe();
	char gradIme[MAX] = "";
	int gradPopulacija = 0;
	FILE* dat = NULL;

	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %d", gradIme, &gradPopulacija);
		DodajGrad(q, gradIme, gradPopulacija);
	}
	fclose(dat);
	return q;
}

pStablo DodajDrzavu(char* drzava, pLista gradovi, pStablo p) {
	if (p == NULL) {
		p = StvoriClanStabla(drzava, gradovi);
	}
	else  {
		if (strcmp(drzava, p->drzava) < 0) {
			p->lijevo = DodajDrzavu(drzava, gradovi, p->lijevo);
		}
		if (strcmp(drzava, p->drzava) > 0) {
			p->desno = DodajDrzavu(drzava, gradovi, p->desno);
		}
	}

	return p;
}
