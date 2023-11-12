#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct tLE
{
	tLE *next;
	char data;
};

struct Queue
{
	tLE *head;
	tLE *tail;
};

void hash(char *str, int n);
int prime(int k);

int main()
{
	int n;
	printf("Enter size of string: ");
	scanf("%d", &n);
	char str[n];
	srand(time(0));
	for (int i = 0; i < n; i++) str[i] = rand()%26+'A';
	printf("\n");
	for (int i = 0; i < n; i++) printf("%c ", str[i]);
	printf("\n");
	hash(str, n);
	return 0;
}

int prime(int InputNumber)
{
	int flag = 0;
	while (1)
	{
		for (int i = 2; i < InputNumber; i++)
		{
			if (InputNumber % i == 0)
			{
				flag = 0;
				break;
			} 
			else flag = 1;
		}
		if (flag == 1) break;
		InputNumber++;
	}
	return InputNumber;
}

void hash(char *str, int n)
{
	int h = 0, i, coll = 0;
	int count =(int)(n/(2*log2(n)));
	int m = prime(count+1);
	
	int C = (int)(n/(2*m));
	printf("\nHash compares = %d\n", C);
	C = (int)(log2(n));
	printf("Binary search compares = %d\n\n", C);

	struct tLE *p;
	struct Queue Q[256];
	
	for (i = 0; i < m; i++)	Q[i].tail = (tLE*)&Q[i].head;
	for (i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
				if (i >= 1 && str[i] == str[j])	goto l;
				
		h = (h*256 + (int)str[i]) % m;
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = str[i];
		Q[h].tail->next = p;
		Q[h].tail = p;
		if (Q[h].head != Q[h].tail) coll++;
		l:;
	}
	for (int i = 0; i < m; i++)
		Q[i].tail->next = NULL;
	for (i = 0; i < m; i++)
	{
		printf("%d - ", i);
		for (p = Q[i].head; p != NULL; p = p->next) printf("%c ", p->data);
		printf("\n");
	}
	
	printf("\n");
	printf("\n_____________________________________________________________\n");
	printf("| Size of hash-table | Count of chars | Count of collisions |");
	printf("\n|____________________|________________|_____________________|\n");
 	printf("|          %d         |       %d       |          %d          |", m, n, coll);
	printf("\n|____________________|________________|_____________________|\n");
	
	
}
