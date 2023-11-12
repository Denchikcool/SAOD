#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int C, M;
const int n = 100;

struct tLE
{
	tLE *next;
	union
	{
		int data;
		unsigned char Digit[sizeof(data)];
	};
} *head, *tail;

struct Queue
{
	tLE *head;
	tLE *tail;
};

void FillInc(struct tLE **head);
void FillDec(struct tLE **head);
void FillRand(struct tLE **head);
int CheckSum(struct tLE *head);
int RunNumber(struct tLE *head);
void DeleteElements(struct tLE **head);
void PrintMas(struct tLE *head);
void DigitalSortInc(tLE *&head, int queueLength);


int main()
{
	int L = 4;
	head = NULL;
	tail = (tLE *)&head;
	int i, sum, count;
	
	printf("***Vozrastanie***\n");
	FillInc(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DigitalSortInc(head, L);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	printf("\n\nTeoria sravnenia = %3.2f \n", (n * log2(n)));
	printf("Teoria peresilki = %3.2f \n", (n * log2(n) + n));
	printf("Real sravnenia = %d \n", C);
	printf("Real peresilki = %d \n", M);
	printf("Trudoemkost' = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	printf("***Ubivanie***\n");
	FillDec(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DigitalSortInc(head, L);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	printf("\n\nTeoria sravnenia = %3.2f \n", (n * log2(n)));
	printf("Teoria peresilki = %3.2f \n", (n * log2(n) + n));
	printf("Real sravnenia = %d \n", C);
	printf("Real peresilki = %d \n", M);
	printf("Trudoemkost' = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	printf("***Random***\n");
	FillRand(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DigitalSortInc(head, L);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	printf("\n\nTeoria sravnenia = %3.2f \n", (n * log2(n)));
	printf("Teoria peresilki = %3.2f \n", (n * log2(n) + n));
	printf("Real sravnenia = %d \n", C);
	printf("Real peresilki = %d \n", M);
	printf("Trudoemkost' = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	return 0;
}

void FillInc(struct tLE **head)
{
	struct tLE *p;
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = n-i;
		p->next = *head;
		*head = p;
	}	
}

void FillDec(struct tLE **head)
{
	struct tLE *p;
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = i+1;
		p->next = *head;
		*head = p;
	}	
}

void FillRand(struct tLE **head)
{
	struct tLE *p;
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = rand() % 100;
		p->next = *head;
		*head = p;
	}	
}

void PrintMas(struct tLE *head)
{
	struct tLE *p = head;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

int CheckSum(struct tLE *head)
{
	int sum = 0;
	struct tLE *p = head;
	while (p != NULL)
	{
		sum+= p->data;
		p = p->next;
	}
	
	return sum;
}

int RunNumber(struct tLE *head)
{
	int count = 1;
	if (head != NULL)
	{
		struct tLE *p = head, *q = p->next;
		while (p->next != NULL)
		{
			q = p->next;
			if (p->data <= q->data);
			else count++;
			p = p->next;
		}
		return count;
	}
	else return 0;
}

void DeleteElements(struct tLE **head)
{
	struct tLE *p = *head;
	for (int i = 0; i < n; i++)
	{
		if (head != NULL)
		{
			p = *head;
			*head = p->next;
			free(p);
		}
	}
}

void DigitalSortInc(tLE *&head, int L)
{
	int KDI[4] = { 3,2,1,0 };
	int j, i, d, k;
	tLE* p;
	Queue Q[256];
	for (j = L - 1; j >= 0; j--)
	{ 
		for (i = 0; i < 256; i++)	Q[i].tail = (tLE*)&Q[i].head;
		
		p = head;
		k = KDI[j];
		
		while (p)
		{
			d = p->Digit[k];
			Q[d].tail->next = p;
			Q[d].tail = p;
			p = p->next;
		}
		
		p = (tLE*)&head;
		for (i = 0; i < 256; i++)
		{
			if (Q[i].tail != (tLE*)&Q[i].head)
			{
				p->next = Q[i].head;
				p = Q[i].tail;
			}
		}
		p->next = NULL;
	}
}
