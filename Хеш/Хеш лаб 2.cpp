#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

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

int prime(int k);
int Table_Size(int n);

int Hash(char K, int i, int m);
int Hash_Insert_Linear(int *T, char K, int m, int &collision);
int Hash_Insert_Square(int *T, char K, int m, int &collision);
int Hash_Search(int *T, char K, int m);

int main()
{
	int n;
	printf("Enter size of string: ");
	scanf("%d", &n);
	
	int m = Table_Size(n);
	printf("\nm = %d\n", m);
	int Table_Linear[m], h;
	for (int i = 0; i < m; i++) Table_Linear[i] = 0;
	int Table_Square[m];
	for (int i = 0; i < m; i++) Table_Square[i] = 0;
	
	char str[n];
	srand(time(0));
	for (int i = 0; i < n; i++) str[i] = rand()%26+'A';
	printf("\n");
	for (int i = 0; i < n; i++) printf("%c ", str[i]);
	printf("\n");
	
	
	printf("\n-----------------------------------------------------------\n");
	printf("\nHash_Insert_Linear\n");
	
	int collision_linear = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++) if (i >= 1 && str[j] == str[i]) goto q;
		h = Hash_Insert_Linear(Table_Linear, str[i], m, collision_linear);
		q:
		if (h == -1) break;
	}
	printf("\n");
	for (int i = 0; i < m; i++) printf("%2d ", i);
	printf("\n");
	for (int i = 0; i < m; i++) printf("%2c ", Table_Linear[i]);
	printf("\n\nCollisions = %d\n", collision_linear);
	
	
	printf("\n-----------------------------------------------------------\n");
	printf("\nHash_Insert_Square\n");
	
	int collision_square = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++) if (i >= 1 && str[j] == str[i]) goto l;
		h = Hash_Insert_Square(Table_Square, str[i], m, collision_square);
		l:
		if (h == -1) break;
	}
	printf("\n");
	for (int i = 0; i < m; i++) printf("%2d ", i);
	printf("\n");
	for (int i = 0; i < m; i++) printf("%2c ", Table_Square[i]);
	printf("\n\nCollisions = %d\n", collision_square);
	
	
	printf("\n\n\n");
	
	printf("\n________________________________________________________________________\n");
	printf("| Size of hash-table | Count of chars |       Count of collisions      |\n");
	printf("|\t\t     |\t              |--------------------------------|");
	printf("\n|                    |                |     Linear    |     Square     |");
	printf("\n|____________________|________________|_______________|________________|\n");
	printf("|         %d          |       %d       |       %d       |       %d        |", m, n, collision_linear, collision_square);
	printf("\n|____________________|________________|_______________|________________|\n");
	
	char Yes_No, KEY;
	int result_of_search;
	printf("\n\nWould u like to find char? (y) or (n)");
	std::cin >> Yes_No;
	if (Yes_No == 'y')
	{
		printf("Enter ur KEY: ");
		std::cin >> KEY;
		result_of_search = Hash_Search(Table_Linear, KEY, m);
		printf("\nResult of linear search = %d", result_of_search);
		result_of_search = Hash_Search(Table_Square, KEY, m);
		printf("\nResult of square search = %d", result_of_search);
	} 
	

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

int Table_Size(int n)
{
	int count =(int)(n/(2*log2(n)));
	int m = prime(count+1);
	return m;
}

int Hash(char K, int i, int m)
{
	int h = 0;
	h = ((int)K + i) % m;
	return h;
}

int Hash_Insert_Linear(int *T, char K, int m, int &collision)
{
	int i = 0, j;
	while (i <= m)
	{
		j = Hash(K, i, m);
		if (T[j] == NULL)
		{
			T[j] = K;
			return j;
		}
		else collision++;
		i++;
	}
	printf("\nTable overflow\n");
	return -1;
}

int Hash_Insert_Square(int *T, char K, int m, int &collision)
{
	int i = 0, j;
	while (i <= m)
	{
		j = Hash(K, i, m);
		if (T[j] == NULL)
		{
			T[j] = K;
			return j;
		}
		else collision++;
		if (i == 0) i = 1;
		else i += 2;
	}
	printf("\nTable overflow\n");
	return -1;
}

int Hash_Search(int *T, char K, int m)
{
	int i = 0, j;
	while (T[i] != 0 || i <= m)
	{
		j = Hash(K, i, m);
		if (T[j] == K) return j;
		i++;
	}
	return 0;
}
