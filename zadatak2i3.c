#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba osoba;

struct _osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;
	pozicija next;
};

pozicija StvoriCvor(void);
pozicija StvoriOsobu(const char*, const char*, int);
pozicija PronadiPrezime(pozicija, const char*);
pozicija PronadiPrethodni(pozicija, const char*, const char*, int);
pozicija Pronadi(pozicija, const char*, const char*, int);

int UnosP(pozicija, pozicija);
int UnosK(pozicija, pozicija);
int Ispis(pozicija);
int Brisi(pozicija, const char*, const char*, int);
int UnesiIspred(pozicija, const char*, const char*, int, const char*, const char*, int);
int UnesiIza(pozicija, const char*, const char*, int, const char*, const char*, int);
int UnosSort(pozicija, char*, char*, int);
int SortPrezime(pozicija);

int UpisDat(const char*, pozicija);
int IspisDat(const char*);

int main()
{
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina;

	char imeU[MAX] = { 0 };
	char prezimeU[MAX] = { 0 };
	int godinaU;

	char dat[MAX] = { 0 };

	char c;

	osoba head;
	pozicija p = NULL;

	head.next = NULL;

	printf("MENU:\n");

	while (1)
	{
		printf("\nAko zelite dodati osobu na pocetak, unesite p.\n");
		printf("Ako zelite dodati osobu na kraj, unesite k.\n");

		printf("Ako zelite dodati osobu abecedeno sortirano, unesite s.\n");

		printf("Ako zelite dodati osobu ispred odredene, unesite b.\n");
		printf("Ako zelite dodati osobu ispred odredene, unesite a.\n");

		printf("Ako zelite provjeriti postoji li osoba u listi, unesite l.\n");

		printf("Ako zelite izbrisati osobu iz liste, unesite o.\n");

		printf("Ako zelite sortirati listu po prezimenima, unesite r");
		printf("Ako zelite ispisati listu, unesite i.\n");

		printf("Ako zelite upisati listu u datoteku, unesite u.\n");
		printf("Ako zelite ispisati listu iz datoteke, unesite d.\n");

		printf("Ako zelite izaci iz programa, unesite z.\n\n");


		scanf(" %c", &c);

		switch (c)
		{
		case 'p':

			printf("\nUnesite ime: ");
			scanf(" %s", ime);

			printf("Unesite prezime: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja: ");
			scanf(" %d", &godina);

			p = StvoriOsobu(ime, prezime, godina);
			UnosP(&head, p);

			break;

		case 'k':

			printf("\nUnesite ime: ");
			scanf(" %s", ime);

			printf("Unesite prezime: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja: ");
			scanf(" %d", &godina);

			p = StvoriOsobu(ime, prezime, godina);
			UnosK(&head, p);

			break;

		case 's':

			printf("\nUnesite ime: ");
			scanf(" %s", ime);

			printf("Unesite prezime: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja: ");
			scanf(" %d", &godina);

			UnosSort(&head, ime, prezime, godina);

			break;

		case 'b':

			printf("\nUnesite ime osobe ispred koje zelite dodati novu: ");
			scanf(" %s", ime);

			printf("Unesite prezime osobe ispred koje zelite dodati novu: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja osobe ispred koje zelite dodati novu: ");
			scanf(" %d", &godina);

			printf("\nUnesite ime osobe koju zelite dodati: ");
			scanf(" %s", imeU);

			printf("Unesite prezime osobe koju zelite dodati: ");
			scanf(" %s", prezimeU);

			printf("Unesite godinu rodenja osobe koju zelite dodati novu: ");
			scanf(" %d", &godinaU);

			UnesiIspred(&head, ime, prezime, godina, imeU, prezimeU, godinaU);

			break;

		case 'a':

			printf("\nUnesite ime osobe iza koje zelite dodati novu: ");
			scanf(" %s", ime);

			printf("Unesite prezime osobe iza koje zelite dodati novu: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja osobe iza koje zelite dodati novu: ");
			scanf(" %d", &godina);

			printf("\nUnesite ime osobe koju zelite dodati: ");
			scanf(" %s", imeU);

			printf("Unesite prezime osobe koju zelite dodati: ");
			scanf(" %s", prezimeU);

			printf("Unesite godinu rodenja osobe koju zelite dodati novu: ");
			scanf(" %d", &godinaU);

			UnesiIza(&head, ime, prezime, godina, imeU, prezimeU, godinaU);

			break;

		case 'l':
			printf("\nUnesite prezime koje zelite pronaci: ");
			scanf(" %s", prezime);

			if (p = PronadiPrezime(head.next, prezime))
			{
				printf("Prezime postoji u listi!\n");
			}

			else
				printf("Prezime ne postoji u listi!\n");

			break;

		case 'o':

			printf("\nUnesite ime osobe koju zelite izbrisat: ");
			scanf(" %s", ime);

			printf("Unesite prezime osobe koju zelite izbrisat: ");
			scanf(" %s", prezime);

			printf("Unesite godinu rodenja osobe koju zelite izbrisat: ");
			scanf(" %d", &godina);

			Brisi(&head, ime, prezime, godina);

			break;

		case 'r':
			SortPrezime(&head);

			break;


		case 'i':
			Ispis(head.next);

			break;

		case 'u':

			printf("\nUnesite ime datoteke u koju zelite unijeti listu, npr. datoteka.txt: ");
			scanf(" %s", dat);

			UpisDat(dat, head.next);

			break;

		case 'd':
			printf("\nUnesite ime datoteke iz koje zelite ispisati listu, npr. datoteka.txt: ");
			scanf(" %s", dat);

			IspisDat(dat);

			break;

		case 'z':
			return 0;
			break;
		}

	}

	free(p);

	return 0;
}


//funkcija dinamciki alocira prostor za strukturu
pozicija StvoriCvor(void)
{
	pozicija p = NULL;

	p = (pozicija)malloc(sizeof(osoba));

	if (!p)
	{
		printf("Neuspjesno alociranje memorije!");

		return p;
	}

	p->next = NULL;

	return p;
}


//funkcija unosi ime, prezime i godinu u dinamicki alociranu strukturu
pozicija StvoriOsobu(const char* ime, const char* prezime, int godina)
{
	pozicija q = StvoriCvor();

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	q->godina = godina;

	return q;
}

//funkcija uzima adresu prvog cvora i pretrazuje postoji li u njoj uneseno prezime
pozicija PronadiPrezime(pozicija headn, const char* prezime)
{
	while (headn != NULL && strcmp(headn->prezime, prezime))
	{
		headn = headn->next;
	}

	if (!headn)
		return headn;

	return headn;
}


//funkcija uzima adresu head cvora i vraca adresu cvora koji se nalazi ispred trazenog
pozicija PronadiPrethodni(pozicija head, const char* ime, const char* prezime, int godina)
{


	while (head->next != NULL && (strcmp(head->next->ime, ime) || strcmp(head->next->prezime, prezime) || head->next->godina != godina))
		head = head->next;

	if (!head->next)
		return head->next;

	else
		return head;
}

//funkcija uzima adresu prvog cvora i vraca adresu trazenog cvora
pozicija Pronadi(pozicija headn, const char* ime, const char* prezime, int godina)
{
	while (headn != NULL && (strcmp(headn->ime, ime) || strcmp(headn->prezime, prezime) || headn->godina != godina))
	{
		headn = headn->next;
	}

	if (!headn)
		return headn;

	else
		return headn;
}

//funkcija unosi osobu na pocetak liste
int UnosP(pozicija head, pozicija p)
{
	p->next = head->next;
	head->next = p;

	return 1;
}

//funkcija unosi osobu na kraj liste
int UnosK(pozicija head, pozicija p)
{
	while (head->next != NULL)
	{
		head = head->next;
	}

	UnosP(head, p);

	return 2;
}

//funckija ispisuje listu, a salje se adresa prvog cvora
int Ispis(pozicija headn)
{
	if (headn == NULL)
		printf("Lista je prazna!\n");

	while (headn != NULL)
	{
		printf("%s %s %d\n", headn->ime, headn->prezime, headn->godina);

		headn = headn->next;
	}

	return 3;
}

//funkcija brise odredenu osobu iz liste
int Brisi(pozicija head, const char* ime, const char* prezime, int godina)
{
	pozicija temp = NULL;

	head = PronadiPrethodni(head, ime, prezime, godina);

	if (head)
	{
		temp = head->next->next;
		free(head->next);
		head->next = temp;
		free(temp);
	}

	else
		printf("Osoba ne postoji u listi!");

	return 4;
}

//funckija unosi novu osobu u listu ispred izabrane osobe
int UnesiIspred(pozicija head, const char* ime, const char* prezime, int godina, const char* imeU, const char* prezimeU, int godinaU)
{
	//ime je ono ispred kojeg unosimo, a imeU ono koje unosimo
	pozicija q = StvoriOsobu(imeU, prezimeU, godinaU);

	head = PronadiPrethodni(head, ime, prezime, godina);

	if (head)
	{
		UnosP(head, q);
	}

	else
		printf("Osoba ne postoji u listi!");

	return 5;
}

//funckija unosi novu osobu u listu iza izabrane osobe
int UnesiIza(pozicija head, const char* ime, const char* prezime, int godina, const char* imeU, const char* prezimeU, int godinaU)
{
	pozicija q = StvoriOsobu(imeU, prezimeU, godinaU);

	head = Pronadi(head->next, ime, prezime, godina);

	if (head)
	{
		UnosP(head, q);
	}

	else
		printf("Osoba ne postoji u listi!");

	return 6;
}


//funckija abecedeno sortira prilikom unosenja u listu
int UnosSort(pozicija head, char* ime, char* prezime, int godina)
{
	pozicija p = StvoriOsobu(ime, prezime, godina);

	while (head->next != NULL && strcmp(_strlwr(head->next->ime), _strlwr(ime)) < 0)
		head = head->next;

	if (head->next != NULL)
	{
		if (strcmp(_strlwr(head->next->ime), _strlwr(ime)) > 0)
			UnosP(head, p);

		else
		{
			while (head->next != NULL && strcmp(_strlwr(head->next->prezime), _strlwr(prezime)) < 0)
				head = head->next;

			if (head->next != NULL)
			{

				if (strcmp(_strlwr(head->next->prezime), _strlwr(prezime)) > 0)
					UnosP(head, p);

				else
				{
					while (head->next != NULL && head->next->godina < godina)
						head = head->next;

					UnosP(head, p);
				}
			}

			else
				UnosP(head, p);
		}
	}

	else
		UnosP(head, p);

	return 7;
}

//funckija abecedeno sortira listu po prezimenu
int SortPrezime(pozicija head)
{
	pozicija end, prev, p, temp;

	end = NULL;

	while (head->next != end)
	{
		prev = head;
		p = head->next;

		while (p->next != end)
		{
			if (strcmp(_strlwr(p->prezime), _strlwr(p->next->prezime)) > 0)
			{
				temp = p->next;

				p->next = temp->next;
				prev->next = temp;
				temp->next = p;

				p = temp;
			}

			prev = p;
			p = p->next;
		}

		end = p;
	}

	return 8;
}

//upisuje listu u datoteku
int UpisDat(const char* imeDat, pozicija head)
{
	FILE* pf = NULL;

	pf = fopen(imeDat, "w");

	if (!pf)
	{
		printf("Neuspjesno otvaranje datoteke!");

		return -1;
	}

	while (head != NULL)
	{
		fprintf(pf, "%-10s %-10s %-4d\n", head->ime, head->prezime, head->godina);
		head = head->next;
	}

	fclose(pf);

	return 9;
}

int IspisDat(const char* imeDat)
{
	FILE* pf = NULL;

	char str[3 * MAX] = { 0 };

	pf = fopen(imeDat, "r");

	if (!pf)
	{
		printf("Neuspjesno otvaranje datoteke!");

		return -2;
	}

	while (fgets(str, 3 * MAX, pf) != NULL)
		puts(str);

	fclose(pf);

	return 10;
}