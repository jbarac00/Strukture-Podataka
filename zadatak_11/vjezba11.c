#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 250
#define SIZE 11

struct _stablo;
typedef struct _stablo* pStablo;
typedef struct _stablo {
	char grad[MAX];
	int populacija;
	pStablo lijevo;
	pStablo desno;
} stablo;

struct _lista;
typedef struct _lista* pLista;
typedef struct _lista {
	char drzava[MAX];
	pStablo gradovi;
	pLista next;
} lista;

struct _HashT;
typedef struct _HashT* HashTab;
typedef struct _HashT {
	pLista* HeadList;
}HashT;

pLista StvoriClanListe();
pLista TraziDrzavu(pLista, char*);
pStablo StvoriClanStabla();
int Drzave(HashTab, char*);
int DodajDrzavu(pLista, char*, char*);
pStablo DodajGrad(pStablo, char*, int);
pStablo Gradovi(pStablo, char*);
int Ispis(pLista);
int IspisStablo(pStablo);
int Odabir(HashTab);
int IspisGradovi(pStablo, int);
int DodajUHash(HashTab, char*, char*);
HashTab StvoriHashTablicu();
int HashFunkcija(char*);

int main() {

	HashTab hashTab = NULL;

	hashTab = StvoriHashTablicu();

	Drzave(hashTab, "drzave.txt");

	Odabir(hashTab);


	return EXIT_SUCCESS;
}

pLista TraziDrzavu(pLista headLista, char* drzava) {
	int index = HashFunkcija(drzava);
	pLista headList = hashTab->HeadList[index];

	while (headLista != NULL) {
		if (strcmp(drzava, headLista->drzava) == 0) {
			return headLista;
		}
		else {
			headLista = headLista->next;
		}
	}
	return NULL;
}

int Odabir(HashTab hashTab) {
	pLista q = NULL;
	char temp1[MAX];
	int temp2;
	printf("Unesite ime drzave koju zelite pretraziti: \n");
	scanf(" %s", temp1);
	printf("Ispis svih gradova koji imaju broj stanovnika veci od  \n");
	scanf("%d", &temp2);
	q = TraziDrzavu(hashTab, temp1);
	if (!q) {
		printf("Zadana drzava ne postoji!");
		return EXIT_FAILURE;
	}
	IspisGradovi(q->gradovi, temp2);

	return EXIT_SUCCESS;
}

int IspisGradovi(pStablo p, int populacijaX) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}

	IspisGradovi(p->lijevo, populacijaX);

	if (p->populacija > populacijaX) {
		printf("%s %d", p->grad, p->populacija);
	}
	IspisGradovi(p->desno, populacijaX);

	return EXIT_SUCCESS;
}


int Ispis(pLista headLista) {
	while (headLista != NULL) {
		printf("%s gradovi:\n", headLista->drzava);
		IspisStablo(headLista->gradovi);
		printf("\n\n");
		headLista = headLista->next;
	}
}

pLista StvoriClanListe() {
	pLista q = malloc(sizeof(lista));
	if (q == NULL) {
		printf("Greska pri alokaciji");
		return NULL;
	}
	strcpy(q->drzava, "");
	q->gradovi = NULL;
	q->next = NULL;
	return q;
}

pStablo StvoriClanStabla(char* grad, int populacija) {
	pStablo q = malloc(sizeof(stablo));

	if (q == NULL) {
		printf("Greska pri alokaciji");
		return NULL;
	}

	strcpy(q->grad, grad);
	q->populacija = populacija;
	q->lijevo = NULL;
	q->desno = NULL;

	return q;
}

int IspisStablo(pStablo p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}

	IspisStablo(p->lijevo);
	printf("%s %d\n", p->grad, p->populacija);
	IspisStablo(p->desno);

	return EXIT_SUCCESS;
}


int Drzave(HashTab hashTab, char* imeDat) {
	char imeDrzava[MAX] = "", imeGradoviDat[MAX] = "";

	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke\n");
		return EXIT_FAILURE;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %s", imeDrzava, imeGradoviDat);
		AddCountryToHashTab(hashTab, imeDrzava, imeGradoviDat);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int DodajDrzavu(pLista headLista, char* drzava, char* imeGradoviDat) {
	pLista temp = NULL;
	char temp1[MAX], temp2[MAX];

	temp = StvoriClanListe();
	strcpy(temp->drzava, drzava);

	temp->gradovi = Gradovi(temp->gradovi, imeGradoviDat);

	strcpy(temp1, drzava);
	while (headLista->next != NULL) {
		strcpy(temp2, headLista->next->drzava);
		if (strcmp(temp1, temp2) > 0) {
			headLista = headLista->next;
			continue;
		}
		break;
	}

	temp->next = headLista->next;
	headLista->next = temp;
}

pStablo Gradovi(pStablo headStablo, char* imeDat) {
	char gradIme[MAX] = "";
	int gradPopulacija = 0;
	FILE* dat = NULL;

	dat = fopen(imeDat, "r");
	if (!dat) {
		printf("Greska pri otvaranju datoteke\n");
		return NULL;
	}

	while (!feof(dat)) {
		fscanf(dat, "%s %d", gradIme, &gradPopulacija);
		headStablo = DodajGrad(headStablo, gradIme, gradPopulacija);
	}
	fclose(dat);
	return headStablo;
}

pStablo DodajGrad(pStablo p, char* grad, int populacija) {
	if (p == NULL) {
		p = StvoriClanStabla(grad, populacija);
	}
	else if (populacija == p->populacija) {
		if (strcmp(grad, p->grad) < 0) {
			p->lijevo = DodajGrad(p->lijevo, grad, populacija);
		}
		if (strcmp(grad, p->grad) > 0) {
			p->desno = DodajGrad(p->desno, grad, populacija);
		}
	}
	else {
		if (populacija < p->populacija) {
			p->lijevo = DodajGrad(p->lijevo, grad, populacija);
		}
		if (populacija > p->populacija) {
			p->desno = DodajGrad(p->desno, grad, populacija);
		}
	}
	return p;
}

int HashFunkcija(char* drzava)
{
	int key = 0;

	for (int i = 0; i < strlen(drzava) || i < 5; i++)
	{
		key += drzava[i];
	}

	return key % SIZE;
}

HashTab StvoriHashTablicu()
{
	HashTab hash = NULL;
	int i = 0;

	hash = (HashTab)malloc(sizeof(HashT));

	if (hash == NULL)
	{
		printf("Greska u alokaciji\n");
		return NULL;
	}

	hash->HeadList = (pLista*)malloc(sizeof(pLista) * SIZE);
	if (hash->HeadList == NULL)
	{
		printf("Greska u alokaciji\n");
		return NULL;
	}

	for (i = 0; i < SIZE; i++)
	{
		hash->HeadList[i] = StvoriClanListe();
	}

	return hash;
}

int DodajUHash(HashTab hashTab, char* drzava, char* imeGradoviDat)
{
	int index = 0;

	index = HashFunkcija(drzava);

	DodajDrzavu(hashTab->HeadList[index], drzava, imeGradoviDat);

	return EXIT_SUCCESS;
}