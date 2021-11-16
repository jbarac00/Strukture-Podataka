#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	double number;
	Position next;
} Element;


Position CreateStackElement(double number);
int InsertAfter(Position position, Position newStackElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* resultDestination, Position head);
int CalculatePostfix(Position head, char operation);
int ReadPostfixFromFile(double* resultDestination, char* fileName);
int DeleteAll(Position head);

int main(int argc, char* argv[])
{
	double result = 0;

	if (argc == 1)
	{
		if (ReadPostfixFromFile( &result, "postfix.txt") == EXIT_SUCCESS)
		{
			printf("Rezultat je: %lf\n", result);
		}
	}
	else if (ReadPostfixFromFile( &result, argv[1]) == EXIT_SUCCESS)
	{
		printf("Rezultat je: %lf\n", result);
	}

	return 0;
}


Position CreateStackElement(double number)
{
	Position newStackElement = NULL;

	newStackElement = (Position)malloc(sizeof(Element));
	if (!newStackElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newStackElement->number = number;
	newStackElement->next = NULL;

	return newStackElement;

}

int InsertAfter(Position position, Position newStackElement)
{
	newStackElement->next=position->next;
	position->next = newStackElement;

	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position newStackElement = NULL;

	newStackElement = CreateStackElement(number);
	if (!newStackElement)
		return EXIT_FAILURE;

	InsertAfter(head, newStackElement);

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp)
		return EXIT_SUCCESS;

	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* resultDestination, Position head)
{
	Position first = head->next;

	if (!first)
	{
		perror("Postfix not valid!\n");
		return -1;
	}

	*resultDestination = first->number;
	DeleteAfter(head);

	return EXIT_SUCCESS;
}

int CalculatePostfix(Position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = 0;
	int status2 = 0;

	status1 = Pop(&operand1,head);
	if (status1 != EXIT_SUCCESS)
		return EXIT_FAILURE;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
		return EXIT_FAILURE;

	switch (operation)
	{
		case '+':
			result = operand1 + operand2;
			break;

		case '-':
			result = operand1 - operand2;
			break;

		case '*':
			result = operand1 * operand2;
			break;

		case '/':
			if (operand2 == 0)
			{
				perror("Can't divide with zero!\n");
				return EXIT_FAILURE;
			}
			result = operand1 / operand2;
			break;
		default:
			printf("This operation isn't supported.\n");
			return EXIT_FAILURE;
	}

	return Push(head, result);
}

int ReadPostfixFromFile(double* resultDestination, char* fileName)
{
	FILE* file = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	int number = 0;
	int status = 0;
	char operation = 0;
	Element head = { .next = NULL, .number = 0 };

	file = fopen(fileName, "rb");
	if (!file)
	{
		perror("Can't open file!\n");
		return EXIT_FAILURE;
	}

	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return EXIT_FAILURE;
	}

	rewind(file);
	fread(buffer, sizeof(char), fileLength, file);
	printf("|%s|\n", buffer);
	fclose(file);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %d %n", &number, &numBytes);
		if (status == 1)
		{
			status = Push(&head, number);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return EXIT_FAILURE;
			}
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = CalculatePostfix(&head, operation);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return EXIT_FAILURE;
			}
			currentBuffer += numBytes;
		}
	}

	free(buffer);

	status = Pop(resultDestination, &head);
	if (status != EXIT_SUCCESS)
	{
		DeleteAll(&head);
		return EXIT_FAILURE;
	}

	if (head.next)
	{
		printf("Postfix not valid!\n");
		DeleteAll(&head);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
	while (head->next)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}


