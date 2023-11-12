#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int n = 100;

struct tLE
{
	tLE *next;
	int data;
} *head, *p, *q;

void FillInc(struct tLE *head);
void FillDec(struct tLE *head);
void FillRand(struct tLE *head);
int CheckSum(struct tLE *head);
int RunNumber(struct tLE *head);
void DeleteElements(struct tLE *head);
void Print(struct tLE *head);

int main()
{	
	
	head = (struct tLE*)malloc(sizeof(struct tLE*));
	head->next=NULL;
	int i, sum, count;
	
	printf("***Vozrastanie***\n");
	FillInc(head);
	Print(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DeleteElements(head);
	printf("\n\n");
	
	printf("***Ubivanie***\n");
	FillDec(head);
	Print(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DeleteElements(head);
	printf("\n\n");
	
	printf("***Random***\n");
	FillRand(head);
	Print(head);
	sum = CheckSum(head);
	printf("\nSumma = %d", sum);
	count = RunNumber(head);
	printf("\nSeria = %d", count);
	DeleteElements(head);
	printf("\n\n");
	
	return 0;
}

void FillInc(struct tLE *head)
{
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = i+1;
		p->next = head->next;
		head->next = p;
	}	
}

void FillDec(struct tLE *head)
{
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = n-i;
		p->next = head->next;
		head->next = p;
	}	
}

void FillRand(struct tLE *head)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = rand() % 100;
		p->next = head->next;
		head->next = p;
	}	
}

void Print(struct tLE *head)
{
	p = head->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

int CheckSum(struct tLE *head)
{
	int sum = 0;
	p = head->next;
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
	p = head->next;
	while (p->next != NULL)
	{
		q = p->next;
		if (p->data <= q->data);
		else count++;
		p = p->next;
	}
	
	return count;
}

void DeleteElements(struct tLE *head)
{
	for (int i = 0; i < n; i++)
	{
		if (head->next != NULL)
		{
			p = head->next;
			head->next = p->next;
			free(p);
		}
	}
}
