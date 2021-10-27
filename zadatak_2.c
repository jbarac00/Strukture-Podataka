/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position head, char* surname);
int DeleteAfter(Position head, char* surname);

int main(int argc, char** argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;


	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	int x = 1;
	
	printf("Vezana lista je prazna.\n");
	
	while (x != 6) {

		printf("\n1 Ispisi listu\n"
			"2 Dodaj osobu na pocetak liste\n"
			"3 Dodaj osobu na kraj liste\n"
			"4 Izbrisi osobu iz liste\n"
			"5 Pronadi osobu\n"
			"6 Izadi iz programa\n"
			"\nVas odabir:\n");

		scanf("%d", &x);

		switch (x)
		{

		case 1:
			PrintList(p->next);
			break;

		case 2:
			printf("Unesite ime, prezime i godinu rodenja: ");
			scanf("%s %s %d", &name, &surname, &birthYear);
			PrependList(p, name, surname, birthYear);
			break;

		case 3:
			printf("Unesite ime, prezime i godinu rodenja: ");
			scanf("%s %s %d", &name, &surname, &birthYear);
			AppendList(p, name, surname, birthYear);
			break;

		case 4:
			printf("Unesite prezime osobe koju zelite izbrisati: ");
			scanf("%s", &surname);
			DeleteAfter(p, surname);
			break;

		case 5:
			printf("Unesite prezime osobe koju zelite pronaci: ");
			scanf("%s", &surname);
			Position temp = FindBySurname(p, surname);
			printf("%s %s %d", temp->name, temp->surname, temp->birthYear);
			break;

		case 6:
			printf("Kraj programa");
			break;

		default:
			printf("Morate unijeti broj od 1 do 6\n");
			break;
		}
	}
 
	return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear) {

	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp) {
		printf("Name: %s, Surname: %s, Birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}

int FindBySurname(Position first, char* surname)
{
	Position temp = first;
	while (temp) {
		if (strcmp(temp->surname, surname) == 0) 
			return temp;
			temp = temp->next;
	}
	return NULL;
}

Position FindBefore(Position head, char* surname)
{
	for (Position temp = head; temp->next; temp = temp->next) {
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;
}

int DeleteAfter(Position head, char* surname)
{
	Position temp;
	head = FindBefore(head, surname);
	if (NULL == head)
		printf("Osoba nije na listi\n");
	else {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}