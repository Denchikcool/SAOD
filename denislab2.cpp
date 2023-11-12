#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

const int size_array = 100;

struct vertex
{
	int data;
	vertex* left;
	vertex* right;
} *root, *root_1, *root_2; //делаю сразу три указателя на три разных корня (изначально у меня было три одинаковых структуры только с разными названиями и корями, но она сказала можно/нужно сделать именно так)

vertex* ISDP(int L, int R, int* A);
vertex* SDP_1 (int D, vertex *&p);
vertex* SDP_2 (int *B, vertex *Root_2);
void BYPASS_LEFT_RIGHT(vertex *p);
int size(vertex *p);
int control_summa(vertex *p);
int height(vertex *p);
int middle_height(vertex *p, int l);
void search(vertex* Root, int D); //функция поиска

int main()
{
	int A[size_array], B[size_array];
	int size_vertex, summa, h, count = 0, flag = 0, temp, sum = 0;
	float middle_h;
	
	srand(time(0));
	
	//массив для исдп, просто от 1 до 100 заполняется
	for (int i = 1; i <= size_array; i++){
		A[i] = i;
	}
	//это массив для сдп, можешь диапазон другой поставить, если хочешь, чисто рандомные числа
	for(int j = 1; j <= size_array; j++){
		B[j] = 1 + rand() % 200;
	}
		
	int L = A[1];
	int R = A[size_array];
	
	//выделение памяти для корней деревьев
	root = (struct vertex*)malloc(sizeof(struct vertex));
	root_1 = (struct vertex*)malloc(sizeof(struct vertex));
	root_1 = NULL;
	root_2 = (struct vertex*)malloc(sizeof(struct vertex));
	root_2 = NULL;
	
	//здесь мы отправляем каждый элемент массива в рекурсивную функцию сдп
	for (int u = 1; u <= size_array; u++){
		SDP_1(B[u], root_1);
	}
	
	//здесь же сразу массив передается, ибо такой алгоритм, как в первом случае не получится сделать
	root_2 = SDP_2(B, root_2);

	
	root = ISDP(L, R, A);
	size_vertex = size(root);
	summa = control_summa(root);
	h = height(root);
	middle_h = middle_height(root, 1) / float(size_vertex);
	
	//тут обычные обходы
	cout << "________________________________________________________________________________________________________________________";
	cout << "Bypass_Left_Right(Rekurcia):" << endl;
	BYPASS_LEFT_RIGHT(root_1);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	cout << "________________________________________________________________________________________________________________________";
	cout << "Bypass_Left_Right(Dv Kosvenost):" << endl;
	BYPASS_LEFT_RIGHT(root_2);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	//переменные для таблицы с передаваемыми значениями функций
	int size_vertex_sdp_1 = size(root_1);
	int summa_sdp_1 = control_summa(root_1);
	int h_sdp_1 = height(root_1);
	float middle_h_sdp_1 = middle_height(root_1, 1) / float(size_vertex_sdp_1);
	
	int size_vertex_sdp_2 = size(root_2);
	int summa_sdp_2 = control_summa(root_2);
	int h_sdp_2 = height(root_2);
	float middle_h_sdp_2 = middle_height(root_2, 1) / float(size_vertex_sdp_2);
	
	//вызов поиска; т.к. делали на паре то просто взяли значения, чтоб проверить функцию, но вообще ищет она
	search(root, 25);
	search(root_1, 200);
	search(root_2, 200);
	
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
	cout << "|_______|______|_______________|________|_______________|" << endl;
	cout << "| ISDP  | " << size_vertex << "  |     " << summa << "      |    " << h << "   |      " << middle_h << "      |" << endl;
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| SDP(r)| " << size_vertex_sdp_1 << "  |     " << summa_sdp_1 << "      |    " << h_sdp_1 << "   |    " << middle_h_sdp_1 << "     |" << endl; 
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| SDP(k)| " << size_vertex_sdp_2 << "  |     " << summa_sdp_2 << "      |    " << h_sdp_2 << "   |    " << middle_h_sdp_2 << "     |" << endl; 
	cout << "|_______|______|_______________|________|_______________|" << endl;

	return 0;
}

vertex* SDP_1 (int D, vertex *&p){
	if (p == NULL){ //выделение памяти под вершину, обнуление правого и левого указателей, запись данных в ячейку
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data){
		SDP_1(D, p->left);
	}
	else if (D >= p->data){  //здесь стоит >= потому что она на лекции говорила, если элементы одинаковые, то вправо убираем (и если ты этого не напишешь, то тогда 1. будет меньше элементов чем 100; 2. тебе придется делать проверку в main чтоб рандомились всегда разные числа
		SDP_1(D, p->right);
	}
	else{
		cout << "Vertex already in the tree!" << endl;
	}
}


vertex* SDP_2 (int *B, vertex *Root_2){
	int i;
	//тк мы передали сюда целый массив, то поэтому будем по элементами идти и строить дерево
	for(i = 1; i <= size_array; i++){
		vertex** p; //создание двойного указателя
		p = &Root_2; //принимает адрес корня
		while (*p != NULL){
			if (B[i] < (*p)->data) p = &((*p)->left);
			else if (B[i] >= (*p)->data) p = &((*p)->right);
			else {
				cout << "Data is already in the tree!" << endl;
				break;
			}
		}
		if (*p == NULL){
			*p = (struct vertex*)malloc(sizeof(struct vertex));
			(*p)->data = B[i];
			(*p)->left = NULL;
			(*p)->right = NULL;
		}
	}
	return Root_2; //возвращаем корень на наше дерево
	//вообще как я понял, дерево строится обособлено от корня (из-за этого тут (*p) и &(*p), а уже в конце построенное дерево принимает адрес корня, и тогда &Root_2 хранит в себе полное дерево
}


vertex* ISDP(int L, int R, int* A)
{
	int m;
	vertex* p;
	if (L > R) return NULL;
	else
	{
		m = ceil((L+R)/(float)2);
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = A[m];
		p->left = ISDP(L, m - 1, A);
		p->right = ISDP(m + 1, R, A);
		return p;
	}
}

void BYPASS_LEFT_RIGHT(vertex *p)
{
	if (p != NULL)
	{
		BYPASS_LEFT_RIGHT(p->left);
		cout << p->data << " ";
		BYPASS_LEFT_RIGHT(p->right);
	}
}

int size(vertex *p)
{
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int control_summa(vertex *p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + control_summa(p->left) + control_summa(p->right);
	return n;
}

int height(vertex *p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left),height(p->right));
	return n;
}

int middle_height(vertex *p, int l)
{
	int s;
	if (p == NULL) s = 0;
	else s = l + middle_height(p->left, l+1) + middle_height(p->right, l+1);
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
	if (p != NULL) cout << "Vertex found: " << p <<  "  | with value - " << p->data << endl;
	else cout << "Vertex not found" << endl; 
}
