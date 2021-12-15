#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct stablo_* Pozicija;
typedef struct stablo_ {
	int element;
	Pozicija left;
	Pozicija right;
}Stablo;

int getNumber(void);
Pozicija Unos(Pozicija Root, int element);
Pozicija newRoot(int element);
void ispisPostorder(Pozicija Root);
void ispisInorder(Pozicija Root);
void ispisPreorder(Pozicija Root);
Pozicija Brisi(Pozicija Root, int element);
Pozicija Min(Pozicija Root);
Pozicija Trazi(Pozicija Root, int element);


int main() {

	Pozicija Root = NULL;
	int x;

	do {
		printf("1-Dodaj element\n"
			"2-Inorder ispis\n"
			"3-Preorder ispis\n"
			"4-Postorder ispis\n"
			"5-Pronadi element\n"
			"6-Izbrisi element\n"
			"7-Izlaz\n");

		scanf("%d", &x);

		switch (x) {
			
		case 1:
			Root = Unos(Root, getNumber());
			break;

		case 2:
			ispisInorder(Root);
			printf("\n");
			break;

		case 3:
			ispisPreorder(Root);
			printf("\n");
			break;

		case 4:
			ispisPostorder(Root);
			printf("\n");
			break;

		case 5:
			Root = Trazi(Root, getNumber());
			break;

		case 6:
			Root = Brisi(Root, Trazi(Root, getNumber()));
			break;

		case 7:
			printf("Izasli ste iz programa\n");
			break;
			
		default:
			printf("Krivi odabir!\n");
			break;
		}

	} while (x != 7);

	return 0;
}

int getNumber(void) {

	int a;
	printf("Unesite broj:\n");
	scanf("%d", &a);

	return a;
}

Pozicija newRoot(int element) {

	Pozicija Root = malloc(sizeof(Stablo));

	Root->element = element;
	Root->left = NULL;
	Root->right = NULL;

	return Root;

}

Pozicija Unos(Pozicija Root, int element) {
	
	if (!Root)
		Root = newRoot(element);

	else if (element < Root->element)
		Root->left = Unos(Root->left, element);
	
	else if (element > Root->element)
		Root->right = Unos(Root->right, element);

	return Root;

}

void ispisPostorder(Pozicija Root) {
	
	if (Root == NULL)
		return;
	
	ispisPostorder(Root->left);
	ispisPostorder(Root->right);

	printf("%d", Root->element);
}

void ispisInorder(Pozicija Root)
{
	if (Root == NULL)
		return;

	ispisInorder(Root->left);

	printf("%d", Root->element);

	ispisInorder(Root->right);
}

void ispisPreorder(Pozicija Root)
{
	if (Root == NULL)
		return;

	printf("%d", Root->element);

	ispisPreorder(Root->left);

	ispisPreorder(Root->right);
}

Pozicija Brisi(Pozicija Root, int element) {

	Pozicija temp = NULL;

	if (!Root)
		return;

	else if (element < Root->element)
		Root->left = Brisi(Root->left, element);


	else if (element > Root->element)
		Root->right = Brisi(Root->right, element);

	else if (Root->left != NULL && Root->right != NULL)
	{
		temp = Min(Root->right);
		Root->element = temp->element;
		Root->right = Brisi(Root->right, Root->element);
	}

	else {
		temp = Root;
		if (NULL == Root->left)
			Root = Root->right;
		else
			Root = Root->left;
		free(temp);
	}

	return Root;
}

Pozicija Min(Pozicija Root) {

	if (NULL == Root)
		return;

	else if (NULL == Root->left)
		return Root;

	else
		return Min(Root->left);

}

Pozicija Trazi(Pozicija Root, int element) {

	if (!Root)
		return;

	else if (element < Root->element)
		Root = Trazi(Root->left, element);

	else if (element > Root->element)
		Root = Trazi(Root->right, element);

	return Root;

}
