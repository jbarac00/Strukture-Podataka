#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

struct cvor;
typedef struct cvor* pozicija;
typedef struct cvor {
    int el;
    pozicija lijevo;
    pozicija desno;
}_cvor;

struct lista;
typedef struct lista* pozicija_l;
typedef struct lista {
    int el;
    pozicija_l next;
}_lista;

pozicija insert(pozicija, int);
void ispis(pozicija);
int replace(pozicija);
void ispis_datoteka(pozicija);
void krozStablo(pozicija korijen, FILE* fp);

int main()
{
	pozicija korijen;
	korijen = NULL;
	int i = 0;
	int brojevi[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	while (i < 10) {
		korijen = insert(korijen, brojevi[i]);
		i++;
	}
	ispis(korijen);
	ispis_datoteka(korijen);



	korijen->el = replace(korijen->lijevo) + replace(korijen->desno);
	ispis(korijen);
	ispis_datoteka(korijen);

	
	srand(time(NULL));
	pozicija korijen2;
	FILE* fp;
	struct lista head = { .el = 0, .next = NULL };

	korijen2 = (pozicija)malloc(sizeof(_cvor));
	korijen2->el = rand() % 80 + 10;
	korijen2->lijevo = NULL;
	korijen2->desno = NULL;

	for (i = 1; i < 10; i++)
	{
		korijen2 = insert(korijen2, rand() % 80 + 10);
	}
	printf("\n");
	ispis(korijen2);

	ispis_datoteka(korijen2);

	return 0;
}

pozicija insert(pozicija korijen, int n)
{
	if (korijen == NULL) {
		korijen = (pozicija)malloc(sizeof(_cvor));
		korijen->el = n;
		korijen->lijevo = korijen->desno = NULL;
		return korijen;
	}

	else if (n >= korijen->el) {
		korijen->lijevo = insert(korijen->lijevo, n);
	}

	else if (n < korijen->el) {
		korijen->desno = insert(korijen->desno, n);
	}

	return korijen;
}

void ispis(pozicija korijen)
{
	if (korijen)
	{
		ispis(korijen->lijevo);
		printf("%d\n", korijen->el);
		ispis(korijen->desno);
	}
}

int replace(pozicija korijen)
{
	int temp = 0;
	if (korijen == NULL) {
		return 0;
	}
	temp = korijen->el;
	korijen->el = replace(korijen->lijevo) + replace(korijen->desno);
	return temp + korijen->el;
}

void ispis_datoteka(pozicija korijen)
{
	FILE* fp;
	fp = fopen("datoteka", "a");
	krozStablo(korijen, fp);
	fprintf(fp, "\n");
	fclose(fp);
}

void krozStablo(pozicija korijen, FILE* fp)
{
	if (korijen)
	{
		krozStablo(korijen->lijevo, fp);
		fprintf(fp, "%d ", korijen->el);
		krozStablo(korijen->desno, fp);
	}
}