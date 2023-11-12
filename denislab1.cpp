#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int size_array = 100;

struct vertex
{
	int data;
	vertex* left;
	vertex* right;
} *root;

vertex* ISDP(int L, int R, int* A);
void BYPASS_LEFT_RIGHT(vertex* p);
int size(vertex* p);
int control_summa(vertex* p);
int height(vertex* p);
int middle_height(vertex* p, int l);

int main()
{
	int A[size_array];
	int size_vertex, summa, h;
	float middle_h;
	
	//заполнение массива 100 элементов от 1 до 100 (условие исдп, на практике при проверке она сказала что так и надо сделать)
	for (int i = 1; i <= size_array; i++){
		A[i] = i;
	}
	
	//переменные отвечающие за границы массива, чтоб само исдп правильно строилось
	int L = A[1];
	int R = A[size_array];
	
	root = (struct vertex*)malloc(sizeof(struct vertex));
	root = ISDP(L, R, A);
	
	cout << "________________________________________________________________________________________________________________________";
	cout << "Bypass_Left_Right:" << endl;
	BYPASS_LEFT_RIGHT(root);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	size_vertex = size(root);
	cout << endl << "Size of the tree = " << size_vertex << endl << endl;
	
	summa = control_summa(root);
	cout << "Control summa = " << summa << endl << endl;
	
	h = height(root);
	cout << "Height of the tree = " << h << endl << endl;
	
	middle_h = middle_height(root, 1) / float(size_vertex);
	cout << "Middle height = " << middle_h << endl << endl;
	
	return 0;
}

vertex* ISDP(int L, int R, int* A)
{
	int m;
	vertex* p; //создание указателя на дерево
	if (L > R) return NULL;
	else
	{
		//это средний элемент в нашем массиве, чисто формула из её лекции (ceil это верхняя граница, т.к. у нас дробная часть при делении получается)
		m = ceil((L+R)/(float)2);
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = A[m];
		p->left = ISDP(L, m - 1, A); //здесь идёт рекурсия на левую границу, начиная с среднего элемента (правая граница уменьшается на 1, но вообще это как при бинарном поиске массив постоянно делится на 2)
		p->right = ISDP(m + 1, R, A); //как закончится левая граница, перейдёт на правую и будет делать то же самое, что я и написал выше
		//возвращение указателя на дерево, чтобы у тебя правильно все распечаталось, начиная от корня и к листьям
		return p;
	}
}

void BYPASS_LEFT_RIGHT(vertex* p)
{
	if (p != NULL)
	{
		BYPASS_LEFT_RIGHT(p->left);
		cout << p->data << " ";
		BYPASS_LEFT_RIGHT(p->right);
	}
}

int size(vertex* p)
{
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int control_summa(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + control_summa(p->left) + control_summa(p->right);
	return n;
}

int height(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left),height(p->right));
	return n;
}

int middle_height(vertex* p, int l)
{
	int s;
	if (p == NULL) s = 0;
	else s = l + middle_height(p->left, l+1) + middle_height(p->right, l+1);
	return s;
}
