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
    int Bal;
    vertex* left;
    vertex* right;
} *root_1;

bool Rost, Umen = false;

void AVL(int D, vertex *&p);
void BYPASS_LEFT_RIGHT(vertex *p);
int size(vertex *p);
int control_summa(vertex *p);
int height(vertex *p);
int middle_height(vertex *p, int l);
void search(vertex *Root, int D);

void RL(vertex *&p);
void LR(vertex *&p);
void LL1(vertex *&p);
void RR1(vertex *&p);

void BL(vertex *&p);
void BR(vertex *&p);
vertex* Delete_AVL(int D, vertex *&p);
void Del(vertex *&q, vertex *&r);


int main()
{
    int B[size_array+1];
    int count = 0, sum = 0, flag, temp, number;
    
    srand(time(0));
    
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
	
	for(int i = 1; i <= size_array; i++){
		cout << B[i] << " ";
	}
	
	cout << endl;
	
    root_1 = NULL; 
	
	
    for (int u = 1; u <= size_array; u++) {
        AVL(B[u], root_1);
    }

    cout << "________________________________________________________________________________________________________________________";
    cout << "Bypass_Left_Right(AVL):" << endl;
    BYPASS_LEFT_RIGHT(root_1);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;

    int size_vertex_avl = size(root_1);
    int summa_avl = control_summa(root_1);
    int h_avl = height(root_1);
    float middle_h_avl = middle_height(root_1, 1) / float(size_vertex_avl);


    cout << "|-------|------|---------------|--------|---------------|" << endl;
    cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;
    cout << "|  AVL  | " << size_vertex_avl << "  | " << summa_avl << "         |    " << h_avl << "   |   " << middle_h_avl << "       |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;

	
	for (int q = 0; q < 10;){
		cout << endl << endl << "-----------------------------------------------------------------------------------";
		cout <<  endl << "Write down the number: ";
		cin >> number;
		search(root_1, number);
		root_1 = Delete_AVL(number, root_1);
		cout << endl;
		cout << "Deleted..." << endl;
		search(root_1, number);
		cout << endl;
		BYPASS_LEFT_RIGHT(root_1);
		if(size(root_1) == size_vertex_avl - (q+1)) q++;
		
	}
	
    return 0;
}

void LL1(vertex *&p){
	vertex *q;
	q = p->left;
	if(q->Bal == 0){
		q->Bal = 1;
		p->Bal = -1;
		Umen = false;
	}
	else{
		q->Bal = 0;
		p->Bal = 0;
	}
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR1(vertex *&p){
	vertex *q;
	q = p->right;
	if(q->Bal == 0){
		q->Bal = -1;
		p->Bal = 1;
		Umen = false;
	}
	else{
		q->Bal = 0;
		p->Bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}


void RL(vertex *&p)
{
    vertex *q, *r;
	q = p->right;
	r = q->left;
    if (r->Bal > 0)
    {
        p->Bal = -1;
    }
    else
    {
        p->Bal = 0;
    }
    if (r->Bal < 0)
    {
        q->Bal = 1;
    }
    else
    {
        q->Bal = 0;
    }
    r->Bal = 0;
    q->left = r->right;
    p->right = r->left;
    r->left = p;
    r->right = q;
    p = r;
}

void LR(vertex *&p)
{
    vertex *q, *r;
	q = p->left;
	r = q->right;
    if (r->Bal < 0)
    {
        p->Bal = 1;
    }
    else
    {
        p->Bal = 0;
    }
    if (r->Bal > 0)
    {
        q->Bal = -1;
    }
    else
    {
        q->Bal = 0;
    }
    r->Bal = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void AVL(int D, vertex *&p)
{
    if (p == NULL)
    {
        p = (struct vertex*)malloc(sizeof(struct vertex));
        p->data = D;
        p->left = NULL;
        p->right = NULL;
        p->Bal = 0;
        Rost = true;
    }
    else if (p->data > D)
    {
        AVL(D, p->left);
        if (Rost == true)
        {
            if (p->Bal > 0)
            {
                p->Bal = 0;
                Rost = false;
            }
            else if (p->Bal == 0) {
                p->Bal = -1;
                Rost = true;
            }
            else
            {
                if (p->left->Bal < 0)
                {
                    LL1(p);
                    Rost = false;
                }
                else
                {
                    LR(p);
                    Rost = false;
                }
            }
        }
    }
    else if (p->data < D)
    {
        AVL(D, p->right);
        if (Rost == true)
        {
            if (p->Bal < 0)
            {
                p->Bal = 0;
                Rost = false;
            }
            else if (p->Bal == 0)
            {
                p->Bal = 1;
                Rost = true;
            }
            else
            {
                if (p->right->Bal > 0)
                {
                    RR1(p);
                    Rost = false;
                }
                else
                {
                    RL(p);
                    Rost = false;
                }
            }
        }
    }
    else {
        cout << "Vertex is alredy in the tree!" << endl;
    }
}


void BL(vertex *&p){
	if(p->Bal == -1){
		p->Bal = 0;
	}
	else if(p->Bal == 0){
		p->Bal = 1;
		Umen = false;
	}
	else if(p->Bal == 1){
		if(p->right->Bal >= 0){
			RR1(p);
		}
		else{
			RL(p);
		}
	}
}

void BR(vertex *&p){
	if(p->Bal == 1){
		p->Bal = 0;
	}
	else if(p->Bal == 0){
		p->Bal = -1;
		Umen = false;
	}
	else if(p->Bal == -1){
		if(p->left->Bal <= 0){
			LL1(p);
		}
		else{
			LR(p);
		}
	}
}

vertex* Delete_AVL(int D, vertex *&p){
	vertex *q, *r;
	if(p == NULL){
		cout << "There is no this vertex in the tree!" << endl;
	}
	if(D < p->data){
		Delete_AVL(D, p->left);
		if(Umen == true){
			BL(p);
		}
	}
	else if(D > p->data){
		Delete_AVL(D, p->right);
		if(Umen == true){
			BR(p);
		}
	}
	else{
		q = p;
		if(q->left == NULL){
			p = q->right;
			Umen = true;
		}
		else if(q->right == NULL){
			p = q->left;
			Umen = true;
		}
		else{
			r = q;
			Del(q, r->left);
			if(Umen == true){
				BL(p);
			}
		}
	free(q);	
	}
	return p;
}

void Del(vertex *&q, vertex *&r){
	if(r->right != NULL){
		Del(q, r->right);
		if(Umen == true){
			BR(r);
		}
	}
	else{
		q->data = r->data;
		q = r;
		r = r->left;
		Umen = true;
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
    else n = 1 + max(height(p->left), height(p->right));
    return n;
}

int middle_height(vertex* p, int l)
{
    int s;
    if (p == NULL) s = 0;
    else s = l + middle_height(p->left, l + 1) + middle_height(p->right, l + 1);
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
    if (p != NULL) cout << "Vertex found: " << p << "  | with value - " << p->data << endl;
    else cout << "Vertex not found" << endl;
}
