#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int const n = 500;
int A[1+n];
int M = 0, C = 0;

void FillInc(int A[], int n);
void FillDec(int A[], int n);
void FillRand(int A[], int n);
int CheckSum(int A[], int n);
int RunNumber(int A[], int n);
void PrintMas(int A[], int n);
void CreatePyramid(int A[], int L, int R);
void HeapSort(int A[], int n);

int main()
{
	int sum = 0, count = 0;	
	
	printf("--ASCENDING--");
	printf("\n\n");
	
	printf("Ascending array: ");
	printf("\n");
	FillInc(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	printf("\n\n");
	
	printf("Sorted ascending array: ");
	printf("\n");
	HeapSort(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d", count);
	
	printf("\n\n");
	
	printf("--DESCENDING--");
	printf("\n\n");
	
	printf("Descending array: ");
	printf("\n");
	FillDec(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	printf("\n\n");
	
	printf("Sorted descending array: ");
	printf("\n");
	HeapSort(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d", count);
	
	printf("\n\n");
	
	printf("--RANDOM--");
	printf("\n\n");
	
	printf("Random array: ");
	printf("\n");
	FillRand(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	printf("\n\n");
	
	printf("Sorted random array: ");
	printf("\n");
	HeapSort(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSum = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d", count);
	
	return 0;	
}

void FillInc(int A[], int n)
{
	int i;
	
	for (i = 1; i < n+1; i++) A[i] = i;
}

void FillDec(int A[], int n)
{
	int i, j = n;
	
	for (i = 1; i < n+1; i++, j--) A[i] = j;
}

void FillRand(int A[], int n)
{
	int i;
	
	srand(time(0));
	
	for (i = 1; i < n+1; i++) A[i] = rand() % 100 + 1;
}

int CheckSum(int A[], int n)
{
	int i, sum = 0;
	
	for (i = 1; i < n+1; i++)
	{
		sum += A[i];
	}
	
	return sum;
}

int RunNumber(int A[], int n)
{
	int count = 1, i;
	
	for (i = 1; i < n; i++)
	{
		if (A[i] <= A[i+1]) continue;
		else count++;
	}
	
	return count;
}

void PrintMas(int A[], int n)
{
	int i;
	
	for (i = 1; i < n+1; i++) printf("%d ", A[i]);
}

void CreatePyramid(int A[], int L, int R)
{
	int x, j, i;

	M++;
	x = A[L];
	i = L;
	
	for (;;)
	{
		j = 2*i;
		if (j > R) break;
		C++;
		if ((j < R) && (A[j+1] <= A[j])) j++;
		C++;
		if (x <= A[j]) break;
		M++;
		A[i] = A[j];
		i = j;
	}
	M++;
	A[i] = x;
}

void HeapSort(int A[], int n)
{
	int L, R, temp;
	M = 0;
	C = 0;
	//#1
	L = n/2;
	while (L > 0)
	{
		CreatePyramid(A, L, n);
		L--;
	}
	//#2
	R = n;
	while (R > 1)
	{
		M = M+3;
		temp = A[1];
		A[1] = A[R];
		A[R] = temp;
		R--;
		CreatePyramid(A, 1, R);
	}
		
	printf("\nCompares: %d\n", C);
	printf("Moves: %d\n", M);
	printf("Laboriousness: %d\n\n", M+C);
	
	printf("Theoretical compares: %d\n", 2*n*(int)log2(n) + n + 2);
	printf("Theoretical Moves: %d\n", n*(int)log2(n) + (int)6.5*n - 4);
	
	printf("Fact laboriousness (%d) is less than theoretical laboriousness (%d) for %d\n\n", C+M, (2*n*(int)log2(n) + n + 2) + (n*(int)log2(n) + (int)6.5*n - 4), abs(((2*n*(int)log2(n) + n + 2) + (n*(int)log2(n) + (int)6.5*n - 4)) - (M+C)));
}
