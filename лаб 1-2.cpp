#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int A[], int n); 
void FillDec(int A[], int n); 
void FillRand(int A[], int n); 
int CheckSum(int A[], int n); 
int RunNumber(int A[], int n); 
void Print(int A[], int n); 
void Sort(int A[], int n); 
void BubbleSort(int A[], int n);
void ShakerSort(int A[], int n);
void InsertSort(int A[], int n);

int main()
{
	int n, count, sum;	
	printf("Please, enter number of massive: \n");
	scanf("%d", &n);
	printf("\n\n");
	int A[n];
	
	printf("***Vozrastanie***\n\n");
	
	printf("Vozrastauchi massive: \n");
	FillInc(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
//	printf("Sortirovani vozrastauchi massive: \n");
//	Sort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);

//	printf("Sortirovani vozrastauchi massive: \n");
//	BubbleSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
//	printf("Sortirovani vozrastauchi massive: \n");
//	ShakerSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
	printf("Sortirovani vozrastauchi massive: \n");
	InsertSort(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nSeria = %d\n\n", count);
	
	printf("***Ubivanie***\n\n");
	
	printf("Ubivauchi massive: \n");
	FillDec(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
//	printf("Sortirovani ubivauchi massive: \n");
//	Sort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);

//	printf("Sortirovani ubivauchi massive: \n");
//	BubbleSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
//	printf("Sortirovani ubivauchi massive: \n");
//	ShakerSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
	printf("Sortirovani ubivauchi massive: \n");
	InsertSort(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nSeria = %d\n\n", count);
	
	printf("***Random***\n\n");
	
	printf("Sluchaini massive: \n");
	FillRand(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d\n\n", sum);
	
//	printf("Sortirovani sluchaini massive: \n");
//	Sort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d", count);

//	printf("Sortirovani sluchaini massive: \n");
//	BubbleSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
//	printf("Sortirovani sluchaini massive: \n");
//	ShakerSort(A,n);
//	Print(A,n);
//	sum = CheckSum(A,n);
//	printf("\nSumma = %d", sum);
//	count = RunNumber(A,n);
//	printf("\nSeria = %d\n\n", count);
	
	printf("Sortirovani sluchaini massive: \n");
	InsertSort(A,n);
	Print(A,n);
	sum = CheckSum(A,n);
	printf("\nSumma = %d", sum);
	count = RunNumber(A,n);
	printf("\nSeria = %d\n\n", count);
	
	return 0;	
}

void FillInc(int A[], int n){
	int i;
	
	for (i = 0; i < n; i++){
		A[i] = i+1;
	} 
}

void FillDec(int A[], int n){
	int i, j = n;
	
	for (i = 0; i < n; i++, j--){
		A[i] = j;
	} 
}

void FillRand(int A[], int n){
	int i;
	
	srand(time(0));
	
	for (i = 0; i < n; i++){
		A[i] = rand() % 50 + 1;
	} 
}

int CheckSum(int A[], int n){
	int i, summa = 0;
	
	for (i = 0; i < n; i++)
	{
		summa += A[i];
	}
	return summa;
}

int RunNumber(int A[], int n){
	int count = 1, i;
	
	for (i = 0; i < n - 1; i++)
	{
		if (A[i] <= A[i+1]){
			continue;
		} 
		else{
			count++;
		} 
	}
	return count;
}

void Print(int A[], int n){
	int i;
	
	for (i = 0; i < n; i++){
		printf("%d ", A[i]);
	} 
}

void Sort(int A[], int n){
	int i, j, a, temp;
	int C = 0, M = 0;
	
	for (i = 0; i < n-1; i++){
		a = i;
		for (j = i+1; j < n; j++){
			C++;
			if (A[j] < A[a]){
				a = j;
			} 
		}
		if (i != a){
			temp = A[i];
			A[i] = A[a];
			A[a] = temp;
			M = M + 3;
		}		
	}
		
	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n\n", M);
	
	printf("Sravnenia po formule: %d\n", (n*n - n)/2);
	printf("Peresilki po formule: %d\n\n", 3*(n-1));
	
	printf("Prakticheskaia trudoemkost': %d\nTeoreticheskaia trudoemkost': %d\nRaznica mejdu teoriei i praktikoi: %d\n\n", C+M, ((n*n - n)/2) + (3*(n-1)), abs((((n*n - n)/2) + (3*(n-1))) - (C+M)));
}


void BubbleSort(int A[], int n)
{
	int i, j, temp;
	int C = 0, M = 0;
	
	for (i = 0; i < n-1; i++)
	{
		for (j = n-1; j > i; j--)
		{
			C++;
			if (A[j] < A[j - 1])
			{
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
				M = M + 3;
			}
		}
	}
		
	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n\n", M);
	
	printf("Sravnenia po formule: %d\n", (n*n - n)/2);
	printf("Peresilki po formule: %d\n\n", (3*(n*n - n))/4);
	
	printf("Prakticheskaia trudoemkost': %d\nTeoreticheskaia trudoemkost': %d\nRaznica mejdu teoriei i praktikoi: %d\n\n", C+M, abs(((n*n - n)/2) + ((3*(n*n - n))/4)), abs((((n*n - n)/2) + ((3*(n*n - n))/4)) - (C+M)));
}

void ShakerSort(int A[], int n)
{
	int i, j, k = n, temp;
	int C = 0, M = 0;
	int L = 0, R = n-1;
	
	while (L < R)
	{
		for (j = R; j > L; j--)
		{
			C++;
			if (A[j] < A[j - 1])
			{
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
				M = M + 3;
				k = j;
			}
		}
		
		L = k;
		
		for (j = L; j < R; j++)
		{
			C++;
			if (A[j] > A[j + 1])
			{
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
				M = M + 3;
				k = j;
			}
		}
		
		R = k;
	}
		
	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n\n", M);
	
	printf("Sravnenia po formule: %d\n", (n*n - n)/2);
	printf("Peresilki po formule: %d\n\n", (3*(n*n - n))/4);
	
	printf("Prakticheskaia trudoemkost': %d\nTeoreticheskaia trudoemkost': %d\nRaznica mejdu teoriei i praktikoi: %d\n\n", C+M, abs(((n*n - n)/2) + ((3*(n*n - n))/4)), abs((((n*n - n)/2) + ((3*(n*n - n))/4)) - (C+M)));
}


void InsertSort(int A[], int n)
{
	int i = 0, temp, j, M = 0, C = 0;

	for (i = 1; i < n; i++)
	{
		temp = A[i];
		M++;
		j = i - 1;
		while ((j >= 0) && (temp < A[j]))
		{
			C++;
			A[j+1] = A[j];
			M++;
			j = j-1;
		}
		A[j+1] = temp;
		M++;
	}
		
	printf("\nSravnenia: %d\n", C);
	printf("Peresilki: %d\n\n", M);
	
	printf("Sravnenia po formule: %d\n", (n*n - n)/2);
	printf("Peresilki po formule: %d\n\n", (((n*n - n)/2) + 2*n - 2));
	
	printf("Prakticheskaia trudoemkost': %d\nTeoreticheskaia trudoemkost': %d\nRaznica mejdu teoriei i praktikoi: %d\n\n", C+M, (((n*n - n)/2) + (((n*n - n)/2) + 2*n - 2)), abs((((n*n - n)/2) + (((n*n - n)/2) + 2*n - 2) - (C+M))));
}
