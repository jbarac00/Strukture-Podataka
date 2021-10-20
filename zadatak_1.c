/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_BODOVI 100

typedef struct _student{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bodovi;
}student;

int BrojRedaka() {
    FILE* file = fopen("studenti.txt", "r");

    if (file == NULL) {
        printf("Datoteka se ne moze otvoriti!");
        return -1;
    }

    
    int brojac = 0;
    char buffer[MAX_LINE] = { 0 };
    while (!feof(file)) {
        fgets(buffer, MAX_LINE, file);
        brojac++;
        }
   

     fclose(file);
     return brojac;
 
}


int ProcitajStudente(int size, student* students) {
    FILE* file = fopen("studenti.txt", "r");

    if (file == NULL) {
        printf("Datoteka se ne moze otvoriti!");
        return 1;
    }

    int i;

    for (i = 0; i < size; i++) {
        fscanf(
            file,
            "%s %s %d",
            students[i].ime,
            students[i].prezime,
            &students[i].bodovi
        );
    }

    fclose(file);

    return 0;
}


int main() {
    student* students;
    int brojac;
    int i;


    brojac = BrojRedaka();
    students = (student*)malloc(sizeof(student) * brojac);
    ProcitajStudente(brojac, students);


    float relativni_bodovi;

    printf("Ime\tPrezime\tR. bodovi\tBodovi\n");
    for (i = 0; i < brojac; i++) {
        relativni_bodovi = (float)students[i].bodovi / (float)MAX_BODOVI;
        printf(
            "%s\t%s\t%.2f\t\t%d\n",
            students[i].ime,
            students[i].prezime,
            relativni_bodovi * 100,
            students[i].bodovi
        );
    }

    return 0;
}