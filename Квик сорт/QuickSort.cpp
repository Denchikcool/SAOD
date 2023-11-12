#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int M = 0, C = 0;

void FillInc(int A[], int n);
void FillDec(int A[], int n);
void FillRand(int A[], int n);
int CheckSum(int A[], int n);
int RunNumber(int A[], int n);
void PrintMas(int A[], int n);
void QuickSortV1(int A[], int L, int R);
void QuickSortV2(int A[], int L, int R);
int Median(int A[], int L, int R);

int main()
{
	int sum = 0, count = 0, n;
	
	printf("Enter size of massive: ");
	scanf("%d", &n);
	int A[n];	
	
	printf("***Vozrastanie***\n\n");
	
	printf("Vozrastauchi massive: \n");
	FillInc(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
	printf("Sortirovani vozrastauchi massive: \n");
	C = 0;
	M = 0;
	QuickSortV1(A,0,n-1);
	

	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n", M);
	printf("Prakticheskaia trudoemkost': %d\n", M+C);
	printf("Teoreticheskaia sravnenia: %d\n", n*(int)log2(n));
	printf("Teoreticheskaia peresilki: %d\n\n", n*(int)log2(n));
	

	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d", count);
	
	printf("\n\n");
	
	printf("***Ubivanie***\n\n");
	
	printf("Ubivauchi massive: \n");
	FillDec(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
	printf("Sortirovani ubivauchi massive: \n");
	C = 0;
	M = 0;
	QuickSortV1(A,0,n-1);
	

	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n", M);
	printf("Prakticheskaia trudoemkost': %d\n", M+C);
	printf("Teoreticheskaia sravnenia: %d\n", n*(int)log2(n));
	printf("Teoreticheskaia peresilki: %d\n\n", n*(int)log2(n));

	
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d\n\n", count);
	
	
	printf("***Random***\n\n");
	
	printf("Sluchaini massive: \n");
	FillRand(A,n);
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
	printf("Sortirovani sluchaini massive: \n");
	C = 0;
	M = 0;
	QuickSortV1(A,0,n-1);
	
	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n", M);
	printf("Prakticheskaia trudoemkost': %d\n", M+C);
	printf("Teoreticheskaia sravnenia: %d\n", n*(int)log2(n));
	printf("Teoreticheskaia peresilki: %d\n\n", n*(int)log2(n));
	
	PrintMas(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nRunNumber = %d", count);
	
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

void FillRand(int A[], int n)
{
	int i;
	
	srand(time(0));
	
	for (i = 0; i < n; i++) A[i] = rand() % 100 + 1;
}

int CheckSum(int A[], int n)
{
	int i, sum = 0;
	
	for (i = 0; i < n; i++)
	{
		sum += A[i];
	}
	
	return sum;
}

int RunNumber(int A[], int n)
{
	int count = 1, i;
	
	for (i = 0; i < n-1; i++)
	{
		if (A[i] <= A[i+1]) continue;
		else count++;
	}
	
	return count;
}

void PrintMas(int A[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) printf("%d ", A[i]);
}

int Median(int A[], int L, int R)
{
	int i, j, min = 9999, max = -9999, avg, k = 0;
	
	for (i = L; i <= R; i++)
	{
		if (min > A[i]) min = A[i];
		if (max < A[i]) max = A[i];
	}
	avg = lroundf((float)(min+max)/2);
	
	for (i = L; i <= R; i++)
	{
		if (A[k] > avg) k++;
		if (A[i] == avg) k = i;
		if ((A[i] < avg) && (A[i] >= A[k])) k = i;
	}
	
	return k;
}

void QuickSortV1(int A[], int L, int R)
{
	int x, i, j, temp, index;
	index = Median(A, L, R);
	
	M++;
	x = A[index];
	i = L;
	j = R;
	
	while (i <= j)
	{
		while (C++, A[i] < x) i++;
		while (C++, A[j] > x) j--;
		if (i <= j)
		{
			M = M+3;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			i++;
			j--;
		}
	}
	
	if (L < j) QuickSortV1(A,L,j);
	if (i < R) QuickSortV1(A,i,R);	
}

void QuickSortV2(int A[], int L, int R)
{
	int x, i, j, temp, index;
	index = Median(A, L, R);

	M++;
	x = A[index];
	i = L;
	j = R;
	
	while (L < R)
	{
		while (L < R)
		{
			while (C++, A[i] < x) i++;
			while (C++, A[j] > x) j--;
			if (i <= j)
			{
				M = M+3;
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
				i++;
				j--;
			}
		}
	
		if ((j-L) < (R-i))
		{
			QuickSortV2(A,L,j);
			L = i;
		}
		else
		{
			QuickSortV2(A,i,R);
			R = j;
		}
	}
}
