#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct vertex
{
	int data;
	int number;
	vertex* left;
	vertex* right;
} *root;

void building_tree(vertex*& root);
vertex* init_vert(int n, int number);
void Bypass_Up_Down(vertex* p);
void Bypass_Left_Right(vertex* p);
void Bypass_Down_Up(vertex* p);
int size(vertex* p);
int control_summa(vertex* p);
int height(vertex* p);
int middle_height(vertex* p, int l);

int main(){
	int size_vertex, summa, h; 
	float middle_h; 
	root = (struct vertex*)malloc(sizeof(struct vertex));
	
	building_tree(root);
	
	cout << "_______________________________________________________________________________________________________" << endl;
	cout << "Bypass_Up_Down:" << endl;
	Bypass_Up_Down(root);
	cout << endl << "Bypass_Left_Right:" << endl;
	Bypass_Left_Right(root);
	cout << endl << "Bypass_Down_Up:" << endl;
	Bypass_Down_Up(root);
	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;
	
	size_vertex = size(root);
	cout << endl << "Size of the tree = " << size_vertex << endl << endl;
	
	summa = control_summa(root);
	cout << "Control summa = " << summa << endl << endl;
	
	h = height(root);
	cout << "Height of the tree = " << h << endl << endl;
	
	//����� ������� ��� ������ ������� ��� ����, ����� ������ ������ ���� ���������� 
	middle_h = middle_height(root, 1) / float(size_vertex);
	cout << "Middle height = " << middle_h << endl << endl;
return 0;}

vertex* init_vert(int n, int number){
	vertex* p = (struct vertex*)malloc(sizeof(struct vertex));
	p->left = NULL;
	p->right = NULL;
	p->data = number; //������ � ������� ������
	p->number = n; //���������� ����� (����� ����� ���� �� ���������� ��� �������, ������ ������ ���� ������)
}

void building_tree(vertex*& root){
	vertex* p = (struct vertex*)malloc(sizeof(struct vertex));
	p = init_vert(1, 30); //������ ����� �������� �� ����� �������, � ������ - �� �� �����, ������� ����� � ���� ������
	root = p;
	//������ �������� ����������, �� ��������� �������, ������� ���������� ������� ������, �� ���� �������� (�� ���� left � right ���������� 0)
	p->left = init_vert(2, 10);
	//��� ��� ��� ������� �� ������ ��� ��������� �������, �� ������� �������� �/���������������, � ����� ������ ������� ������
	p = p->left;
	p->right = init_vert(3, 20);
	p = p->right;
	p->left = init_vert(4, 12);
	p = p->left;
	p->right = init_vert(5, 15);
	p = p->right;
	p->right = init_vert(6, 18);
}

//��������� ��������� ������, ����� ��� ��� ����������
void Bypass_Up_Down(vertex* p){
	if (p != NULL)
	{
		cout << p->data << " - " << "number is " << p->number << "| ";
		Bypass_Up_Down(p->left);
		Bypass_Up_Down(p->right);
	}
}

void Bypass_Left_Right(vertex* p){
	if (p != NULL)
	{
		Bypass_Left_Right(p->left);
		cout << p->data << " - " << "number is " << p->number << "| ";
		Bypass_Left_Right(p->right);
	}
}

void Bypass_Down_Up(vertex* p){
	if (p != NULL)
	{
		Bypass_Down_Up(p->left);
		Bypass_Down_Up(p->right);
		cout << p->data << " - " << "number is " << p->number << "| ";
	}
}

int size(vertex* p){
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int control_summa(vertex* p){
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + control_summa(p->left) + control_summa(p->right);
	return n;
}

int height(vertex* p){
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left),height(p->right));
	return n;
}

int middle_height(vertex* p, int l){
	int s;
	if (p == NULL) s = 0;
	else s = l + middle_height(p->left, l+1) + middle_height(p->right, l+1);
	return s;
}
