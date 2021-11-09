#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

struct _Polinom;

typedef struct _Polinom* Polinom;

struct _Polinom
{
	int koeficijent;
	int eksponent;
	Polinom next;
};

int ImeDatoteke(char* datoteka);
int UcitajPodatke(Polinom pol1, Polinom pol2, char* datoteka);
int UcitajPolinom(Polinom pol, char* linija);
void IspisiPolinom(Polinom pol);
void ZbrojiPolinome(Polinom pol1, Polinom pol2, Polinom suma);
void PomnoziPolinome(Polinom pol1, Polinom pol2, Polinom produkt);

int main(void)
{
	struct _Polinom pol1, pol2, suma, produkt;

	pol1.next = NULL;
	pol2.next = NULL;
	suma.next = NULL;
	produkt.next = NULL;

	char datoteka[MAX] = { 0 };
	ImeDatoteke(datoteka);

	UcitajPodatke(&pol1, &pol2, datoteka);
	IspisiPolinom(&pol1);
	IspisiPolinom(&pol2);

	ZbrojiPolinome(pol1.next, pol2.next, &suma);
	printf("Suma je:\n");
	IspisiPolinom(&suma);

	PomnoziPolinome(pol1.next, pol2.next, &produkt);
	printf("Produkt je:\n");
	IspisiPolinom(&produkt);

	return EXIT_SUCCESS;
}

int ImeDatoteke(char* datoteka)
{
	printf("Upisite ime datoteke:\n");
	scanf(" %s", datoteka);

	return EXIT_SUCCESS;
}

int UcitajPodatke(Polinom pol1, Polinom pol2, char* datoteka)
{
	FILE* file = NULL;
	char linija[MAX] = { 0 };

	file = fopen(datoteka, "r");
	if (!file)
	{
		perror("Greska!\n");
		return EXIT_FAILURE;
	}

	fgets(linija, MAX, file);
	UcitajPolinom(pol1, linija);
	fgets(linija, MAX, file);
	UcitajPolinom(pol2, linija);

	fclose(file);

	return EXIT_SUCCESS;
}

int UcitajPolinom(Polinom pol, char* linija)
{
	Polinom q, temp, prev;
	int n = 0;
	int status = 0;
	char* pRed = linija;

	while (strlen(pRed) > 0)
	{
		q = (Polinom)malloc(sizeof(struct _Polinom));

		status = sscanf(pRed, " %d %d %n", &q->koeficijent, &q->eksponent, &n);
		if (status != 2) {
			printf("Greska!");
			return EXIT_FAILURE;
		}

		temp = pol->next;
		prev = pol;
		while (temp != NULL && temp->eksponent > q->eksponent)
		{
			prev = temp;
			temp = temp->next;
		}

		prev->next = q;
		if (temp != NULL)
		{
			q->next = temp;
		}
		else
		{
			q->next = NULL;
		}

		pRed += n;

	}
	return EXIT_SUCCESS;
}

void IspisiPolinom(Polinom pol)
{
	pol = pol->next;

	printf("\n");

	while (pol != NULL)
	{
		if (pol->koeficijent > 0)
		{
			printf("\t+%d*x^%d", pol->koeficijent, pol->eksponent);
		}
		else
		{
			printf("\t%d*x^%d", pol->koeficijent, pol->eksponent);
		}
		pol = pol->next;
	}

	printf("\n");
}

void ZbrojiPolinome(Polinom pol1, Polinom pol2, Polinom S)
{
	Polinom q, temp;

	while (pol1 != NULL && pol2 != NULL)
	{
		q = (Polinom)malloc(sizeof(struct _Polinom));
		q->next = NULL;


		if (pol1->eksponent > pol2->eksponent)
		{
			q->eksponent = pol1->eksponent;
			q->koeficijent = pol1->koeficijent;
			pol1 = pol1->next;
		}
		else if (pol1->eksponent < pol2->eksponent)
		{
			q->eksponent = pol2->eksponent;
			q->koeficijent = pol2->koeficijent;
			pol2 = pol2->next;
		}
		else
		{
			q->eksponent = pol1->eksponent;
			q->koeficijent = pol1->koeficijent + pol2->koeficijent;
			pol1 = pol1->next;
			pol2 = pol2->next;
		}
		S->next = q;
		S = q;
	}

	if (pol1 != NULL)
	{
		temp = pol1;
	}
	else
	{
		temp = pol2;
	}

	while (temp != NULL)
	{
		q = (Polinom)malloc(sizeof(struct _Polinom));
		q->next = NULL;
		q->eksponent = temp->eksponent;
		q->koeficijent = temp->koeficijent;
		S->next = q;
		S = q;
		temp = temp->next;
	}
}

void PomnoziPolinome(Polinom pol1, Polinom pol2, Polinom pol)
{
	Polinom q, prvi = pol1, drugi = pol2, temp, prev;
	int n;

	while (prvi != NULL)
	{
		drugi = pol2;
		while (drugi != NULL)
		{
			temp = pol->next;
			prev = pol;

			n = prvi->eksponent + drugi->eksponent;

			while (temp != NULL && temp->eksponent > n)
			{
				prev = temp;
				temp = temp->next;
			}

			if (temp != NULL && temp->eksponent == n)
			{
				temp->koeficijent += prvi->koeficijent * drugi->koeficijent;
			}
			else
			{
				q = (Polinom)malloc(sizeof(struct _Polinom));

				q->eksponent = n;
				q->koeficijent = prvi->koeficijent * drugi->koeficijent;

				prev->next = q;
				q->next = temp;
			}

			drugi = drugi->next;
		}
		prvi = prvi->next;
	}

	while (pol->next != NULL)
	{
		if (pol->next->koeficijent == 0)
		{
			temp = pol->next;
			pol->next = pol->next->next;
			free(temp);
		}
		pol = pol->next;
	}
}