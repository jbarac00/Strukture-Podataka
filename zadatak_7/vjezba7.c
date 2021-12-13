#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _direktorij {
	char ime[20];
	struct _direktorij* child;
	struct _direktorij* sibling;
}Direktorij;

typedef struct _cvor {
	Direktorij* directory;
	struct _cvor* next;
	struct _cvor* prev;
}Cvor;

int Menu(Direktorij* Root, Cvor* Head);
int Linija(Cvor* Head, Direktorij* Root, Direktorij* currentFile);
Cvor* PronadiPosljednji(Cvor* Head);
int Md(Direktorij* currentFile);
Direktorij* Cd(Direktorij* currentFile, Cvor* Head);
Direktorij* Pronadi(char* name, Direktorij* currentFile);
int Push(Cvor* Head, Direktorij* directory);
Direktorij* Back(Direktorij* currentFile, Cvor* Head);
Direktorij* Pop(Cvor* Head);
int Dir(Direktorij* currentFile);

int main(void)
{
	Direktorij* Root = (Direktorij*)malloc(sizeof(Direktorij));
	Root->child = NULL;
	Root->sibling = NULL;

	Cvor* Head = (Cvor*)malloc(sizeof(Cvor));
	Head->next = NULL;
	Head->prev = NULL;

	int status = 0;

	do {
		status = Menu(Root, Head);
	} while (!status);

	return 0;
}
int Menu(Direktorij* Root, Cvor* Head) {
	Direktorij* CurrentFile = Root;
	char command[20] = { 0 };

	printf(" Stvori direktorij: md <filename>\n");
	printf(" Promijeni direktorij: cd <filename> \n");
	printf(" Povratak na predhodni direktorij: cd..\n");
	printf(" Ispisi poddirektorije trenutnog direktorija: dir\n");
	printf(" Izlaz: exit\n");

	while (1) {
		Linija(Head, Root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			Md(CurrentFile);
		}
		else if (!strcmp(command, "cd")) {
			CurrentFile = Cd(CurrentFile, Head);
		}
		else if (!strcmp(command, "cd..")) {
			CurrentFile = Back(CurrentFile, Head);
		}
		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}
		else if (!strcmp(command, "exit")) {
			return 1;
		}
		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}
int Linija(Cvor* Head, Direktorij* Root, Direktorij* currentFile) {
	Cvor* P;

	P = PronadiPosljednji(Head);

	if (Head->next == NULL) {
		printf("%s>", Root->ime);
		return 0;
	}

	while (P->prev != NULL) {
		printf("%s>", P->directory->ime);
		P = P->prev;
	}

	printf("%s>", currentFile->ime);

	return 0;
}
Cvor* PronadiPosljednji(Cvor* Head) {
	Cvor* P;
	P = Head->next;

	if (P == NULL) {
		return NULL;
	}

	while (P->next != NULL) {
		P = P->next;
	}

	return P;
}
int Md(Direktorij* currentFile) {
	Direktorij* directory = (Direktorij*)malloc(sizeof(Direktorij));

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = directory;
	}
	else
		currentFile->child = directory;

	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
}
Direktorij* Cd(Direktorij* currentFile, Cvor* Head) {
	Direktorij* SearchedFile;
	char imeDir[20];

	scanf(" %s", imeDir);

	if (currentFile->child == NULL) {
		printf("Ne postoji direktorij kojeg zelite otvoriti!\n");
		return currentFile;
	}

	SearchedFile = Pronadi(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	Push(Head, currentFile);

	return SearchedFile;
}
Direktorij* Pronadi(char* name, Direktorij* currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}
int Push(Cvor* Head, Direktorij* directory) {
	Cvor* q = (Cvor*)malloc(sizeof(Cvor));

	q->next = Head->next;
	q->prev = Head;
	if (Head->next != NULL) {
		Head->next->prev = q;
	}
	Head->next = q;
	q->directory = directory;

	return 0;
}
Direktorij* Back(Direktorij* currentFile, Cvor* Head) {
	Direktorij* SearchedFile;

	SearchedFile = Pop(Head);

	if (SearchedFile == NULL) {
		printf("Nije moguce izaci iz ovog direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}
Direktorij* Pop(Cvor* Head) {
	Cvor* q = (Cvor*)malloc(sizeof(Cvor));
	Direktorij* p;

	if (Head->next == NULL)
		return NULL;

	q = Head->next;
	p = q->directory;
	Head->next = Head->next->next;
	if (Head->next != NULL)
		Head->next->prev = Head;
	free(q);

	return p;
}
int Dir(Direktorij* currentFile) {
	if (currentFile->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}