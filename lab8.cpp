#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

const int size_array = 10;

struct array_tree
{
	int data;
	int weight;
};

struct vertex
{
	int data;
	int weight;
	vertex* left;
	vertex* right;
} *root, * root_A1, * root_A2;

void build_sdp(int D, vertex*& p, int W);
void createDOP(int L, int R, int** AR, int* B, int* W);
void createAP_AR(int** AW, int** AP, int** AR);
void createAW(int** AW, int* W);
void createA1(array_tree* arr);
void createA2(struct array_tree *arr, int L, int R);
void obhod_left_right(vertex* p);
int size(vertex* p);
int check_sum(vertex* p);
int height(vertex* p);
int SumLengthPaths_Weight(vertex* p, int l);
int treeWeight(vertex* p);
void HeapSort(struct array_tree A[], int n);
void CreatePyramid(struct array_tree A[], int L, int R);
void search(vertex* Root, int D);


int main()
{
	int B[size_array], W[size_array];
	int size_vertex, sum, h, count = 0, flag, temp, x, summa = 0, number;
	float Wavg_h;

	int** AW = new int* [size_array + 1];
	int** AP = new int* [size_array + 1];
	int** AR = new int* [size_array + 1];

	for (int i = 0; i < size_array + 1; i++)
	{
		AW[i] = new int[size_array + 1];
		AP[i] = new int[size_array + 1];
		AR[i] = new int[size_array + 1];
	}

	for (int i = 0; i < size_array + 1; i++)
		for (int j = 0; j < size_array + 1; j++)
		{
			AW[i][j] = 0;
			AP[i][j] = 0;
			AR[i][j] = 0;
		}

	for (int i = 0; i < size_array; i++)
		B[i] = i + 1;

	srand(time(0));

	for (int i = 0; i < size_array; i++) W[i] = 1 + rand() % 10;

	struct array_tree* arr = (struct array_tree*)malloc((size_array + 1) * sizeof(struct array_tree));
	for (int i = 1; i < size_array + 1; i++)
	{
		arr[i].data = B[i - 1];
		arr[i].weight = W[i - 1];
	}

	cout << "Vertex array:" << endl;
	for (int i = 0; i < size_array; i++) cout << B[i] << " ";
	cout << endl << endl << "Weight array:" << endl ;
	for (int i = 0; i < size_array; i++) cout << W[i] << " ";
	cout << endl << endl;

	root = (struct vertex*)malloc(sizeof(struct vertex));
	root = NULL;
	root_A1 = (struct vertex*)malloc(sizeof(struct vertex));
	root_A1 = NULL;
	root_A2 = (struct vertex*)malloc(sizeof(struct vertex));
	root_A2 = NULL;

	createAW(AW, W);

	createAP_AR(AW, AP, AR);

	cout << "AW:" << endl;
	for (int i = 0; i < size_array + 1; i++) cout << i << "   ";
	cout << endl << endl;
	for (int i = 0; i < size_array + 1; i++)
	{	
		cout << i << " |";
		for (int j = 0; j < size_array + 1; j++) cout << AW[i][j] << "  ";
		cout << endl;
	}
	cout << endl;


	cout << "AP:" << endl;
	for (int i = 0; i < size_array + 1; i++) cout << i << "   ";
	cout << endl << endl;
	for (int i = 0; i < size_array + 1; i++)
	{	
		cout << i << " |";
		for (int j = 0; j < size_array + 1; j++) cout << AP[i][j] << "  ";
		cout << endl;
	}
	cout << endl;

	cout << "AR:" << endl;
	for (int i = 0; i < size_array + 1; i++) cout << i << "  ";
	cout << endl << endl;
	for (int i = 0; i < size_array + 1; i++)
	{	
		cout << i << " |";
		for (int j = 0; j < size_array + 1; j++) cout << AR[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	createDOP(0, size_array, AR, B, W);

	size_vertex = size(root);
	sum = check_sum(root);
	Wavg_h = SumLengthPaths_Weight(root, 1) / (float)treeWeight(root);

	createA2(arr, 1, size_array);

	cout << "A2: " << endl;
	for (int i = 1; i < size_array + 1; i++)
		cout << arr[i].data << "(weight = " << arr[i].weight << ") ";
	cout << endl;

	int size_A2 = size(root_A2);
	int sum_A2 = check_sum(root_A2);
	float Wavg_h_A2 = SumLengthPaths_Weight(root_A2, 1) / (float)treeWeight(root_A2);

	createA1(arr);

	int size_A1 = size(root_A1);
	int sum_A1 = check_sum(root_A1);
	float Wavg_h_A1 = SumLengthPaths_Weight(root_A1, 1) / (float)treeWeight(root_A1);

	cout << "________________________________________________________________________________________________________________________";
	cout << "Obhod_Left_Right(DOP):" << endl;
	obhod_left_right(root);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Obhod_Left_Right(A1):" << endl;
	obhod_left_right(root_A1);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Obhod_Left_Right(A2):" << endl;
	obhod_left_right(root_A2);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;

	cout << " ________________________________________________________ " << endl;
	cout << "| n=100 | Size |   Check Sum   | Weighted Average Height |" << endl;
	cout << "|_______|______|_______________|_________________________|" << endl;
	cout << "|  DOP  |  " << size_vertex << "  |       " << sum << "      |            " << Wavg_h << "            |" << endl;
	cout << "|_______|______|_______________|_________________________|" << endl;
	cout << "|  A1   |  " << size_A1 << "  |       " << sum_A1 << "      |            " << Wavg_h_A1 << "            |" << endl;
	cout << "|_______|______|_______________|_________________________|" << endl;
	cout << "|  A2   |  " << size_A2 << "  |       " << sum_A2 << "      |            " << Wavg_h_A2 << "            |" << endl;
	cout << "|_______|______|_______________|_________________________|" << endl;

	for (int q = 0; q < 10; q++){
		cout << endl << endl << "-----------------------------------------------------------------------------------";
		cout <<  endl << "Write down the number: ";
		cin >> number;
		search(root, number);
		search(root_A1, number);
		search(root_A2, number);
		cout << "DOP: " << endl;
		cout << "________________________________________________________________________________________________________________________";
		obhod_left_right(root);
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << endl;
		cout << "A1: " << endl;
		cout << "________________________________________________________________________________________________________________________";
		obhod_left_right(root_A1);
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << endl;
		cout << "A2: " << endl;
		cout << "________________________________________________________________________________________________________________________";
		obhod_left_right(root_A2);
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << endl;
	}
	return 0;
}

void obhod_left_right(vertex* p)
{
	if (p != NULL)
	{
		obhod_left_right(p->left);
		cout << p->data << "(weight = " << p->weight << ") ";
		obhod_left_right(p->right);
	}
}

int size(vertex* p)
{
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int check_sum(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + check_sum(p->left) + check_sum(p->right);
	return n;
}

int treeWeight(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->weight + treeWeight(p->left) + treeWeight(p->right);
	return n;
}

int SumLengthPaths_Weight(vertex* p, int l)
{
	int s;
	if (p == NULL) s = 0;
	else s = p->weight * l + SumLengthPaths_Weight(p->left, l + 1) + SumLengthPaths_Weight(p->right, l + 1);
	return s;
}

void search(vertex* Root, int D)
{
	vertex* p = (struct vertex*)malloc(sizeof(struct vertex));
	p = Root;
	while (p != NULL)
	{
		if (D < p->data) p = p->left;
		else if (D > p->data) p = p->right;
		else break;
	}
	if (p != NULL) cout << "Vertex found: " << p << " (" << p->data << ")" << endl;
	else cout << "Vertex not found" << endl;
}

void createAW(int** AW, int* W)
{
	for (int i = 0; i < size_array + 1; i++)
		for (int j = i + 1; j < size_array + 1; j++)
			AW[i][j] = AW[i][j - 1] + W[j - 1];
}

void createAP_AR(int** AW, int** AP, int** AR)
{
	int m, min, x, j;
	for (int i = 0; i < size_array; i++)
	{
		j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (int h = 2; h <= size_array; h++)
	{
		for (int i = 0; i <= size_array - h; i++)
		{
			j = i + h;
			m = AR[i][j - 1];
			min = AP[i][m - 1] + AP[m][j];
			for (int k = m + 1; k <= AR[i + 1][j]; k++)
			{
				x = AP[i][k - 1] + AP[k][j];
				if (x < min)
				{
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void createDOP(int L, int R, int** AR, int* B, int* W)
{
	int k;
	if (L < R)
	{
		k = AR[L][R];
		build_sdp(B[k - 1], root, W[k - 1]);
		createDOP(L, k - 1, AR, B, W);
		createDOP(k, R, AR, B, W);
	}
}

void createA1(array_tree* arr)
{
	HeapSort(arr, size_array);
	for (int i = 1; i < size_array + 1; i++)
		build_sdp(arr[i].data, root_A1, arr[i].weight);
	cout << endl;
	cout << "A1: " << endl;
	for (int i = 1; i < size_array + 1; i++)
		cout << arr[i].data << "(weight = " << arr[i].weight << ") ";
	cout << endl;
}

void createA2(struct array_tree *arr, int L, int R)
{
	int i, wes = 0, sum = 0;
	if (L <= R)
	{
		for (i = L; i <= R; i++) wes += arr[i].weight;
		for (i = L; i <= R; i++)
		{
			if ((sum < wes / (float) 2) && (sum + arr[i].weight >= wes / 2)) break;
			sum += arr[i].weight;
		}
		build_sdp(arr[i].data, root_A2, arr[i].weight);
		createA2(arr, L, i - 1);
		createA2(arr, i + 1, R);
	}
}

void build_sdp(int D, vertex*& p, int W)
{
	if (p == NULL)
	{
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->weight = W;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data)
	{
		build_sdp(D, p->left, W);
	}
	else if (D >= p->data)
	{
		build_sdp(D, p->right, W);
	}
	else
	{
		cout << "The vertex exists in the tree!" << endl;
	}
}

void CreatePyramid(struct array_tree A[], int L, int R)
{
	int j, i;
	struct array_tree x;

	x = A[L];
	i = L;

	for (;;)
	{
		j = 2 * i;
		if (j > R) break;
		if ((j < R) && (A[j + 1].weight <= A[j].weight)) j++;
		if (x.weight <= A[j].weight) break;
		A[i] = A[j];
		i = j;
	}
	A[i] = x;
}

void HeapSort(struct array_tree A[], int n)
{
	int L, R;
	struct array_tree temp;
	//#1
	L = n / 2;
	while (L > 0)
	{
		CreatePyramid(A, L, n);
		L--;
	}
	//#2
	R = n;
	while (R > 1)
	{
		temp = A[1];
		A[1] = A[R];
		A[R] = temp;
		R--;
		CreatePyramid(A, 1, R);
	}
}

