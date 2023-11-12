#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <time.h>
#include <fstream>
using namespace std;

const int N = 4000;
int order = 0;
const int max_number = 256;

struct locality
{
	char name[32];
	char street[18];
	short int house;
	short int flat;
	char date[10];
};

struct tLE
{
	tLE* next;
	locality* person;
};

struct Queue
{
	tLE* head;
	tLE* tail;
} pointers;

struct array_structs_for_tree
{
	locality* person;
	int weight;
};

struct vertex
{
	vertex* left = NULL;
	vertex* right = NULL;
	vertex* mid = NULL;
	locality* person;
	int wes;
} *root;

struct find
{
	int house;
	int flat;
};

struct Byte
{
	int ASCII_symbol;
	float probability;
};

void Print(struct locality** data);
void Application();
void HeapSort(struct locality** ind);
void CreatePyramid(struct locality** ind, int L, int R);
int Less(struct locality* X, struct locality* Y);
void BiSearch(struct locality** ind, char* x);
int Check1(char* a, char* x);
int Check2(char* a, char* x);
void completion(Queue* pointers, locality* person);
int print_sorted(Queue* pointers);
void weight(int*& weights, int N);
void create_array(int*& weights, int N, array_structs_for_tree*& array_tree, Queue* pointers);
void CreatePyramid_1(array_structs_for_tree*& array_tree, int L, int R);
void HeapSort_1(array_structs_for_tree*& array_tree, int size);
void createA2(array_structs_for_tree* array_tree, int L, int R);
void build_sdp(locality* D, vertex*& p, int W, int flag);
void obhod_left_right(vertex* p, int flag);
void search(vertex* Root, struct find D, int flag);
vertex* delete_vertex(array_structs_for_tree D, vertex* Root, int flag);
int Less_1(struct locality* X, struct locality* Y);
void Coding();
void Sort(Byte* arr, int num);
void DOWN(int num, int j);
int UP(int num, double q, Byte* P);
void Huffman(Byte* P, int num);
float AverageLengthCodeWordHUFFMAN(Byte* P, int num);
double Entropy(Byte* P, int num);

int* Length;
int** C;

int main() {
	int i, j;
	char KEY[3];

	srand(time(0));

	FILE* fl = fopen("testBase4.dat", "rb");

	root = NULL;

	struct locality* I = (struct locality*)malloc(N * sizeof(struct locality));
	struct locality** ind = (struct locality**)malloc(N * sizeof(struct locality*));

	for (j = 0; j < N; j++) {
		ind[j] = &I[j];
	}

	fread((locality*)I, sizeof(locality), N, fl);

	while (1) {
		Application();
		cin >> i;
		switch (i) {
		case 1:
			system("cls");
			Print(ind);
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			HeapSort(ind);
			Print(ind);
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "BiSearch" << endl;
			cout << endl << "Key of search: ";
			cin >> KEY;
			BiSearch(ind, KEY);
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			cout << "Coding" << endl;
			Coding();
			system("pause");
			system("cls");
			break;
		case 5:
			cout << "Goodbye!" << endl;
			exit(0);
		default:
			system("cls");
			cout << "Wrong value. Enter right number!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	delete[] I;
	delete[] ind;

	return 0;
}

void Application() {
	cout << "_______________________________________________" << endl;
	cout << "|1 |          To see the 4 data base          |" << endl;
	cout << "|--|------------------------------------------|" << endl;
	cout << "|2 | To sort data base for the name and street|" << endl;
	cout << "|--|------------------------------------------|" << endl;
	cout << "|3 |      Search and A2-tree (for flats)      |" << endl;
	cout << "|--|------------------------------------------|" << endl;
	cout << "|4 |               Coding                     |" << endl;
	cout << "---|------------------------------------------|" << endl;
	cout << "|5 |               Exit                       |" << endl;
	cout << "-----------------------------------------------" << endl;
}

void Print(struct locality** data) {

	int count = 0, ans;

	for (int i = 0; i < N; i++) {
		printf("%d) ", i + 1);
		printf("%32s", data[i]->name);
		printf("%19s", data[i]->street);
		printf("%7d", data[i]->house);
		printf("%7d", data[i]->flat);
		printf("%12s\n", data[i]->date);
		count++;
		if (count == 20) {
			count = 0;
			cout << "Do you want to see next 20 writings?(1/0)";
			cin >> ans;
			if (ans == 1) {
				continue;
			}
			else if (ans == 0) {
				break;
			}
			else {
				i = ans - 2;
			}
		}
	}
}

void CreatePyramid(struct locality** ind, int L, int R) {
	int j = 0, i;
	struct locality* a;

	a = ind[L];
	i = L;

	while (1) {
		j = 2 * i;
		if (j > R) break;
		if ((j < R) && (Less(ind[j + 1], ind[j]) >= 0)) j++;
		if ((Less(a, ind[j]) >= 0)) break;
		ind[i] = ind[j];
		i = j;
	}
	ind[i] = a;
}

void HeapSort(struct locality** ind) {
	int L, R;
	struct locality* temp;
	L = ceil(N / 2);
	while (L >= 0) {
		CreatePyramid(ind, L, N - 1);
		L--;
	}
	R = N - 1;
	while (R >= 0) {
		temp = ind[0];
		ind[0] = ind[R];
		ind[R] = temp;
		R--;
		CreatePyramid(ind, 0, R);
	}
}

int Less(struct locality* X, struct locality* Y) {
	if (strcmp(X->name, Y->name) > 0) { return 1; }
	else if (strcmp(X->name, Y->name) < 0) { return -1; }
	else if (strcmp(X->street, Y->street) > 0) { return 1; }
	else if (strcmp(X->street, Y->street) < 0) { return -1; }
	else { return 0; }
}

void BiSearch(struct locality** ind, char* x) {
	int m, L = 0, R = N - 1, count = 0, * weights;
	struct find number;
	pointers.tail = (tLE*)&pointers.head;

	while (L < R) {
		m = (L + R) / 2;
		if (Check1(ind[m]->name, x)) L = m + 1;
		else R = m;
	}
	if (Check2(ind[R]->name, x)) {
		for (int i = L; Check2(ind[R]->name, x) == 1;) {
			completion(&pointers, ind[i]);
			i++;
			R++;
			if (R + 1 > N) break;
		}
	}
	else {
		cout << "Key not found!" << endl;
		system("pause");
		system("cls");
	}
	count = print_sorted(&pointers);

	array_structs_for_tree* info = (struct array_structs_for_tree*)malloc(sizeof(struct array_structs_for_tree) * count);
	weight(weights, count);
	create_array(weights, count, info, &pointers);
	HeapSort_1(info, count);
	createA2(info, 0, count - 1);
	obhod_left_right(root, 1);
	order = 0;
	cout << "Enter the house that you want to search: ";
	cin >> number.house;
	cout << "Enter the flat that you want to search: ";
	cin >> number.flat;
	search(root, number, 0);
	for (int i = 0; i < count; i++) {
		root = delete_vertex(info[i], root, 0);
	}
}

int Check1(char* a, char* x) {
	for (int i = 0; i < 3; i++) {
		if (a[i] == x[i]) {
			continue;
		}
		else if (a[i] > x[i]) {
			return 0;
		}
		else {
			return 1;
		}
	}
	return 0;
}

int Check2(char* a, char* x) {
	for (int i = 0; i < 3; i++) {
		if (a[i] == x[i]) {
			continue;
		}
		else if (a[i] != x[i]) {
			return 0;
		}
	}
	return 1;
}

void completion(Queue* pointers, locality* person) {
	tLE* p;

	p = new tLE;
	p->next = 0;
	p->person = person;

	pointers->tail->next = p;
	pointers->tail = p;
}

int print_sorted(Queue* pointers) {
	int count = 0;
	tLE* p;
	p = pointers->head;

	while (p != NULL) {
		cout << order + 1 << ")  ";
		cout << "Name: " << p->person->name;
		cout << " Street: " << p->person->street;
		cout << "  House: " << p->person->house;
		cout << "  Flat: " << p->person->flat;
		cout << "  Date: " << p->person->date << endl;
		cout << "---------------------------------" << endl;
		order++;
		count++;
		p = p->next;
	}
	order = 0;
	cout << endl;
	return count;
}

void weight(int*& weights, int N) {
	int i;
	weights = (int*)malloc(sizeof(int) * N);

	for (i = 0; i < N; i++) {
		weights[i] = 1 + rand() % 100;
	}
}

void create_array(int*& weights, int N, array_structs_for_tree*& array_tree, Queue* pointers) {
	tLE* p = pointers->head;
	int i;
	for (i = 0; i < N; i++) {
		array_tree[i].person = p->person;
		array_tree[i].weight = weights[i];
		p = p->next;
	}
}

void CreatePyramid_1(array_structs_for_tree*& array_tree, int L, int R) {
	int j = 0, i;
	array_structs_for_tree a;

	a = array_tree[L];
	i = L;

	while (1) {
		j = 2 * i;
		if (j > R) break;
		if ((j < R) && (Less_1(array_tree[j + 1].person, array_tree[j].person) >= 0)) j++;
		if ((Less_1(a.person, array_tree[j].person) >= 0)) break;
		array_tree[i] = array_tree[j];
		i = j;
	}
	array_tree[i] = a;
}

void HeapSort_1(array_structs_for_tree*& array_tree, int size) {
	int L, R;
	array_structs_for_tree temp;
	L = ceil(size / 2);
	while (L >= 0) {
		CreatePyramid_1(array_tree, L, size - 1);
		L--;
	}
	R = size - 1;
	while (R >= 0) {
		temp = array_tree[0];
		array_tree[0] = array_tree[R];
		array_tree[R] = temp;
		R--;
		CreatePyramid_1(array_tree, 0, R);
	}
}

int Less_1(struct locality* X, struct locality* Y) {
	if (X->house > Y->house) { return 1; }
	else if (X->house < Y->house) { return -1; }
	else if (X->flat > Y->flat) { return 1; }
	else if (X->flat < Y->flat) { return -1; }
	else { return 0; }
}

void createA2(array_structs_for_tree* array_tree, int L, int R)
{
	int i, wes = 0, sum = 0;
	if (L <= R)
	{
		for (i = L; i <= R; i++) wes += array_tree[i].weight;
		for (i = L; i <= R; i++)
		{
			if ((sum < wes / (float)2) && (sum + array_tree[i].weight >= wes / (float)2)) break;
			sum += array_tree[i].weight;
		}
		build_sdp(array_tree[i].person, root, array_tree[i].weight, 0);
		createA2(array_tree, L, i - 1);
		createA2(array_tree, i + 1, R);
	}
}

void build_sdp(locality* D, vertex*& p, int W, int flag)
{
	if (p == NULL)
	{
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->person = D;
		p->wes = W;
		p->left = NULL;
		p->right = NULL;
		p->mid = NULL;
	}
	else if (flag == 0) {
		if (D->house < p->person->house)
		{
			build_sdp(D, p->left, W, 0);
		}
		else if (D->house > p->person->house)
		{
			build_sdp(D, p->right, W, 0);
		}
		else if (D->house == p->person->house) {
			build_sdp(D, p->mid, W, 1);
		}
	}
	else if (flag == 1) {
		if (D->flat < p->person->flat) build_sdp(D, p->left, W, 1);
		else if (D->flat >= p->person->flat) build_sdp(D, p->right, W, 1);
	}
	else
	{
		cout << "The vertex exists in the tree!" << endl;
	}
}

void obhod_left_right(vertex* p, int flag)
{
	if (p != NULL)
	{
		obhod_left_right(p->left, flag);
		if (p->mid != NULL)
		{
			build_sdp(p->person, p->mid, p->wes, 1);
			flag = 1;
			obhod_left_right(p->mid, flag);
			flag = 0;
		}
		if (flag == 1)
		{
			cout << order + 1 << ")  ";
			order++;
			cout << "Name: " << p->person->name;
			cout << " Street: " << p->person->street;
			cout << "  House: " << p->person->house;
			cout << "  Flat: " << p->person->flat;
			cout << "  Date: " << p->person->date << endl;
			cout << "---------------------------------" << endl;
		}
		flag = 1;
		obhod_left_right(p->right, flag);
	}
}

void search(vertex* Root, struct find D, int flag)
{
	vertex* p = (struct vertex*)malloc(sizeof(struct vertex));
	p = Root;
	while (p != NULL)
	{
		if (flag == 0)
		{
			if (D.house < p->person->house) p = p->left;
			else if (D.house > p->person->house) p = p->right;
			else if (D.house == p->person->house) p = p->mid, flag = 1;
		}
		else if (flag == 1)
		{
			if (D.flat < p->person->flat) p = p->left;
			else if (D.flat > p->person->flat)	p = p->right;
			else if (D.flat == p->person->flat) break;
		}
		else break;
	}
	if (p != NULL) {
		cout << order + 1 << ")  ";
		order++;
		cout << "Name: " << p->person->name;
		cout << " Street: " << p->person->street;
		cout << "  House: " << p->person->house;
		cout << "  Flat: " << p->person->flat;
		cout << "  Date: " << p->person->date << endl;
		cout << "---------------------------------" << endl;
		if (p->right != NULL) search(p->right, D, 1);
	}
}

vertex* delete_vertex(array_structs_for_tree D, vertex* Root, int flag)
{
	vertex** p;
	p = &Root;
	vertex* q, * r, * s;

	while (*p != NULL)
	{
		if (flag == 0)
		{
			if (D.person->house < (*p)->person->house) p = &((*p)->left);
			else if (D.person->house > (*p)->person->house) p = &((*p)->right);
			else if (D.person->house == (*p)->person->house) break;
		}
		else break;
	}
	if (*p != NULL)
	{
		q = *p;
		if (q->left == NULL) *p = q->right;
		else if (q->right == NULL) *p = q->left;
		else
		{
			r = q->left;
			s = q;
			if (r->right == NULL)
			{
				r->right = q->right;
				*p = r;
			}
			else
			{
				while (r->right != NULL)
				{
					s = r;
					r = r->right;
				}
				s->right = r->left;
				r->left = q->left;
				r->right = q->right;
				*p = r;
			}
		}
		free(q);
	}
	return Root;
}

double Entropy(Byte* P, int num)
{
	double sum = 0;
	for (int i = 0; P[i].probability != 0; i++)
	{
		sum += -P[i].probability * log2(P[i].probability);
	}
	return sum;
}

float AverageLengthCodeWordHUFFMAN(Byte* P, int num)
{
	float sum = 0;
	for (int i = 1; i <= num; i++) sum += P[i].probability * Length[i];
	return sum;
}

void Huffman(Byte* P, int num)
{
	double q;
	int j;
	if (num == 2)
	{
		C[1][1] = 0;
		Length[1] = 1;
		C[2][1] = 1;
		Length[2] = 1;
	}
	else
	{
		q = P[num - 1].probability + P[num].probability;
		j = UP(num, q, P);
		Huffman(P, num - 1);
		DOWN(num, j);
	}
}

int UP(int num, double q, Byte* P)
{
	int j = 1;
	for (int i = num - 1; i >= 2; i--)
	{
		if (P[i - 1].probability < q) P[i] = P[i - 1];
		else
		{
			j = i;
			break;
		}
	}
	P[j].probability = q;
	return j;
}

void DOWN(int num, int j)
{
	int* S = new int[1024 + 1];
	for (int k = 1; k <= 1024; k++) S[k] = -1;
	for (int k = 1; C[j][k] != -1; k++) S[k] = C[j][k];
	int length_temp = Length[j];
	for (int i = j; i <= num - 2; i++)
	{
		for (int k = 1; C[i + 1][k] != -1; k++) C[i][k] = C[i + 1][k];
		Length[i] = Length[i + 1];
	}
	for (int k = 1; S[k] != -1; k++) C[num - 1][k] = S[k];
	for (int k = 1; S[k] != -1; k++) C[num][k] = S[k];
	C[num - 1][length_temp + 1] = 0;
	C[num][length_temp + 1] = 1;
	Length[num - 1] = length_temp + 1;
	Length[num] = length_temp + 1;

	delete[] S;
}

void Sort(Byte* arr, int num)
{
	int j, k, i;
	Byte temp;

	for (i = 0; i < num - 1; i++)
	{
		k = i;

		for (j = i + 1; j < num; j++)
			if (arr[j].probability > arr[k].probability) k = j;

		temp = arr[i];
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

void Coding()
{
	Byte P[max_number];
	int bytes[max_number] = { 0 };
	int sum = 0;
	unsigned char x;
	ifstream infile;
	infile.open("testBase4.dat", ios::binary | ios::in);

	while (1)
	{
		infile.read((char*)&x, 1);

		if (infile.eof())
			break;

		bytes[x]++;
		sum++;

	}

	for (int i = 0; i < max_number; ++i)
	{
		P[i].ASCII_symbol = i;
		P[i].probability = (float)bytes[i] / (float)sum;
	}

	Sort(P, max_number);
	double entropy_text = Entropy(P, max_number);

	int num = 0;
	for (int i = 0; i < max_number; i++)
	{
		if (P[i].probability != 0) num++;
	}

	Length = new int[num + 1];
	C = new int* [num + 1];
	for (int i = 1; i < num + 1; i++)	C[i] = new int[num + 1];

	for (int i = 1; i < num + 1; i++)
	{
		for (int j = 1; j < num + 1; j++) C[i][j] = -1;
	}

	for (int i = 1; i < num + 1; ++i)
	{
		Length[i] = 0;
	}

	Byte P_Huffman_Work[max_number + 1], P_Huffman_Print[max_number + 1];
	for (int i = 1; i <= num; i++)
	{
		P_Huffman_Work[i].ASCII_symbol = P[i - 1].ASCII_symbol;
		P_Huffman_Work[i].probability = P[i - 1].probability;
	}

	for (int i = 1; i <= num; i++)
	{
		P_Huffman_Print[i].ASCII_symbol = P[i - 1].ASCII_symbol;
		P_Huffman_Print[i].probability = P[i - 1].probability;
	}

	Huffman(P_Huffman_Work, num);
	float avg_length_code_word_HUFFMAN = AverageLengthCodeWordHUFFMAN(P_Huffman_Print, num);

	cout << "HUFFMAN" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 1; i <= num; i++)
	{
		printf("|%6c - %d  | ", P_Huffman_Print[i].ASCII_symbol, P_Huffman_Print[i].ASCII_symbol);
		printf("   %5lf    |      ", P_Huffman_Print[i].probability);
		for (int j = 1; j <= Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	cout << "Entropy: " << entropy_text << endl;
	cout << "Average length of code word: " << avg_length_code_word_HUFFMAN << endl;

	for (int i = 1; i <= num; i++)	delete C[i];
	delete[] Length;
	delete[] C;
}

