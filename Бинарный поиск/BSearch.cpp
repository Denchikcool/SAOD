#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int const n = 1000;
int A[n];
int C = 0;

void FillInc(int A[], int n);
void FillDec(int A[], int n);
void PrintMas(int A[], int n);


void BSearch1(int A[], int n, int x);
void BSearch2(int A[], int n, int x);

void QuickSort();

int main()
{
	int x;
	
	printf("Enter X: ");
	scanf("%d", &x);
	printf("\n");
	
	printf("--ASCENDING--");
	printf("\n\n");
	
	printf("Ascending array: ");
	printf("\n");
	FillInc(A,n);
	PrintMas(A,n);
	
	printf("\n\n");
	
	printf("--BSearch1--");
	printf("\n");
	BSearch1(A,n,x);
	
	printf("\n\n");
	
	printf("--BSearch2--");
	printf("\n");
	BSearch2(A,n,x);
	
		
	return 0;	
}

void FillInc(int A[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) A[i] = i+1;
}

void FillDec(int A[], int n)
{
	int i, j = n;
	
	for (i = 0; i < n; i++, j--) A[i] = j;
}

void PrintMas(int A[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) printf("%d ", A[i]);
}

void BSearch1(int A[], int n, int x)
{
	int m, L = 0, R = n-1, flag = 0;
	C = 0;
	
	while ((L <= R) && (flag == 0))
	{
		m = (L+R)/2;
		C++;
		if (A[m] == x)
		{
			flag = 1;
			break;
		}
		C++;
		if (A[m] < x) L = m+1;
		else R = m-1;
	}
	printf("\nResult of search: %d", m);
	printf("\nCompares: %d", C);
	printf("\nTheoretical compares: %d", int(log2(n)) + 1);
}

void BSearch2(int A[], int n, int x)
{
	int m, L = 0, R = n-1, flag = 0;
	C = 0;
	
	while (L < R)
	{
		m = (L+R)/2;
		C++;
		if (A[m] < x) L = m+1;
		else R = m;
	}
	C++;
	if (A[R] == x)
	{
		printf("\nResult of search: %d", R);
	}
	else printf("%d not found", x);
	printf("\nCompares: %d", C);
	printf("\nTheoretical compares: %d", int(log2(n)) + 1);
}
