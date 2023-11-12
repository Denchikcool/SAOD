#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

const int size_array = 10;

struct vertex
{
	int data;
	vertex* left;
	vertex* right;
} *root, *root_1; 

vertex* ISDP(int L, int R, int* A);
vertex* SDP_1 (int D, vertex *&p);
void BYPASS_LEFT_RIGHT(vertex *p);
int size(vertex *p);
int control_summa(vertex *p);
int height(vertex *p);
int middle_height(vertex *p, int l);
void search(vertex* Root, int D);
vertex* delete_vertex(int D, vertex *Root); 

int main()
{
	int A[size_array], B[size_array];
	int size_vertex, summa, h, count = 0, flag = 0, temp, sum = 0;
	float middle_h;
	
	srand(time(0));
	
	
	for (int i = 1; i <= size_array; i++){
		A[i] = i;
	}

//	for(int j = 1; j <= size_array; j++){
//		B[j] = 1 + rand() % 200;
//	}
	
	//рандом чисел без повторений, чтоб удаление нормально работало
	for (int j = 1; j <= size_array;){
		flag = 0;
		temp = 1 + rand() % 200;
		if (j == 1){
			B[j] = temp;
			j++;
		}
		else{
			for (int k = 1; k < j; k++){
				if (temp != B[k]) flag = 0;
				else if (temp == B[k]){
					flag = 1;
					break;
				}
			}
			if (flag == 1) continue;
			else if (flag == 0){
				B[j] = temp;
				j++;
			}
		}
	}
	
		
	int L = A[1];
	int R = A[size_array];
	
	root = (struct vertex*)malloc(sizeof(struct vertex));
	root_1 = (struct vertex*)malloc(sizeof(struct vertex));
	root_1 = NULL;
	
	for (int u = 1; u <= size_array; u++){
		SDP_1(B[u], root_1);
	}

	
	root = ISDP(L, R, A);
	size_vertex = size(root);
	summa = control_summa(root);
	h = height(root);
	middle_h = middle_height(root, 1) / float(size_vertex);
	
	
	cout << "________________________________________________________________________________________________________________________";
	cout << "Bypass_Left_Right(Rekurcia):" << endl;
	BYPASS_LEFT_RIGHT(root_1);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
	
	int size_vertex_sdp_1 = size(root_1);
	int summa_sdp_1 = control_summa(root_1);
	int h_sdp_1 = height(root_1);
	float middle_h_sdp_1 = middle_height(root_1, 1) / float(size_vertex_sdp_1);
	
	
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
	cout << "|_______|______|_______________|________|_______________|" << endl;
	cout << "| ISDP  | " << size_vertex << "   |     " << summa << "        |    " << h << "   |      " << middle_h << "      |" << endl;
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| SDP(r)| " << size_vertex_sdp_1 << "   |     " << summa_sdp_1 << "       |    " << h_sdp_1 << "   |      " << middle_h_sdp_1 << "      |" << endl; 
	cout << "|_______|______|_______________|________|_______________|" << endl;
	
	int number;
	for (int q = 0; q < 10;){
		cout << endl << endl << "----------------------------------------------------------------------";
		cout <<  endl << "Write down the number: ";
		cin >> number;
		//функция поиска, которая показывает, что введённый элемент реально есть в дереве 
		search(root_1, number);
		root_1 = delete_vertex(number, root_1);
		cout << endl;
		cout << "Deleted..." << endl;
		//поиск после удаления, чтоб подтвердить, что элемент реально удалился
		search(root_1, number);
		cout << endl;
		cout << endl << "Rekurcia" << endl;
		//ну и вывод обходов после удаления, чтоб опять же это видеть
		BYPASS_LEFT_RIGHT(root_1);
		if(size(root_1) == size_vertex_sdp_1 - (q+1)) q++;
	}
	
	
	return 0;
}

vertex* SDP_1 (int D, vertex *&p){
	if (p == NULL){ 
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data){
		SDP_1(D, p->left);
	}
	else if (D > p->data){  
		SDP_1(D, p->right);
	}
	else{
		cout << "Vertex already in the tree!" << endl;
	}
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

vertex* delete_vertex(int D, vertex *Root){
	vertex** p; //адрес адреса удаляемой вершины
	p = &Root;
	vertex *q, *r, *s; //q - адрес удаляемой вершины, r - наибольший элемент левого поддерева, не имеющий правого поддерева, s - элемент, который стоит на один уровень выше, чем r
	//тут обычный поиск элемента в дереве 
	while (*p != NULL){
		if (D < (*p)->data){
			p = &((*p)->left);
		} 
		else if (D > (*p)->data){
			p = &((*p)->right);
		} 
		else{
			break;
		} 
	}
	if (*p != NULL){
		q = *p;
		//вот это условие и следующие проверяет: является ли вершина листовой/есть ли у неё не более одного поддерева
		if (q->left == NULL){
			*p = q->right;
		} 
		else if (q->right == NULL){
			*p = q->left;
		} 
		//если у вершины 2 поддерева
		else
		{
			r = q->left;
			s = q;
			//если у нас найдена большая вершина, то мы переприсваеваем двойной указатель на эту вершину
			if (r->right == NULL){
				r->right = q->right;
				*p = r;
			}
			else{
				//ищется наибольший элемент в левом поддереве (s играет роль сохранения, чтоб не потерять указатель r)
				while(r->right != NULL){
					s = r;
					r = r->right;
				}
				//здесь обычное переприсваивание (на её рисунках можешь посмотреть что там происходит)
				s->right = r->left;
				r->left = q->left;
				r->right = q->right;
				*p = r;
			}
		}		
		//удаление самой вершины
		free(q);
	}
	return Root;
}

