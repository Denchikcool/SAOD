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
} *root_1, *root_2;

bool Rost, Umen = false;
int VR = 1, HR = 1;

void AVL(int D, vertex *&p);
void B_TREE(int D, vertex *&p);
void RL(vertex *&p);
void LR(vertex *&p);
//void LL(vertex*& p);
//void RR(vertex*& p);
void LL1(vertex*& p);
void RR1(vertex*& p);
void BYPASS_LEFT_RIGHT(vertex *p);
int size(vertex *p);
int control_summa(vertex *p);
int height(vertex *p);
int middle_height(vertex *p, int l);
void search(vertex *Root, int D);

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

//	for(int i = 1; i <= size_array; i++){
//		B[i] = i;
//	}
	
    root_1 = NULL;
	root_2 = NULL; 
	
	
    for (int u = 1; u <= size_array; u++) {
        AVL(B[u], root_1);
        B_TREE(B[u], root_2);
    }

    cout << "________________________________________________________________________________________________________________________";
    cout << "Bypass_Left_Right(AVL):" << endl;
    BYPASS_LEFT_RIGHT(root_1);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    
    cout << "________________________________________________________________________________________________________________________";
    cout << "Bypass_Left_Right(B-tree):" << endl;
    BYPASS_LEFT_RIGHT(root_2);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;

    int size_vertex_avl = size(root_1);
    int summa_avl = control_summa(root_1);
    int h_avl = height(root_1);
    float middle_h_avl = middle_height(root_1, 1) / float(size_vertex_avl);
    
    int size_vertex_B = size(root_2);
    int summa_B = control_summa(root_2);
    int h_B = height(root_2);
    float middle_h_B = middle_height(root_2, 1) / float(size_vertex_B);


    cout << "|-------|------|---------------|--------|---------------|" << endl;
    cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;
    cout << "|  AVL  | " << size_vertex_avl << "  | " << summa_avl << "         |    " << h_avl << "   |   " << middle_h_avl << "       |" << endl;
    cout << "=========================================================" << endl;
    cout << "|  B-TREE  | " << size_vertex_B << "  | " << summa_B << "         |    " << h_B << "   |   " << middle_h_B << "       |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;

	
	for (int q = 0; q < 10; q++){
		cout << endl << endl << "-----------------------------------------------------------------------------------";
		cout <<  endl << "Write down the number: ";
		cin >> number;
		search(root_1, number);
		search(root_2, number);
		cout << endl;
		cout << "AVL: " << endl;
		cout << "________________________________________________________________________________________________________________________";
		BYPASS_LEFT_RIGHT(root_1);
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << endl;
		cout << "B-TREE: " << endl;
		cout << "________________________________________________________________________________________________________________________";
		BYPASS_LEFT_RIGHT(root_2); 
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	}
	
    return 0;
}

//void LL(vertex*& p)
//{
//    vertex *q;
//    q = p->left;
//    p->Bal = 0;
//    q->Bal = 0;
//    p->left = q->right;
//    q->right = p;
//    p = q;
//}
//
//void RR(vertex*& p)
//{
//    vertex *q;
//    q = p->right;
//    p->Bal = 0;
//    q->Bal = 0;
//    p->right = q->left;
//    q->left = p;
//    p = q;
//}

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

void B_TREE(int D, vertex *&p){
	vertex *q;
	if(p == NULL){
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
		p->Bal = 0;
		VR = 1; 
	}
	else if(p->data > D){
		B_TREE(D, p->left);
		if(VR == 1){
			if(p->Bal == 0){
				q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->Bal = 1;
				VR = 0;
				HR = 1;
			}
			else{
				p->Bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else{
			HR = 0;
		}
	}
	else if(p->data < D){
		B_TREE(D, p->right);
		if(VR == 1){
			p->Bal = 1;
			HR = 1;
			VR = 0;
		}
		else if(HR == 1){
			if(p->Bal == 1){
				q = p->right;
				p->Bal = 0;
				q->Bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else{
				HR = 0;
			}
		}
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
