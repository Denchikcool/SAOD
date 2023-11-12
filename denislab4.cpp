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

bool Rost;

void AVL(int D, vertex*& p);
void SDP_1 (int D, vertex *&p);
void BYPASS_LEFT_RIGHT(vertex* p);
int size(vertex* p);
int control_summa(vertex* p);
int height(vertex* p);
int middle_height(vertex* p, int l);
void search(vertex* Root, int D);
void LL(vertex*& p);
void RR(vertex*& p);
void RL(vertex*& p);
void LR(vertex*& p);

int main()
{
    int B[size_array+1];
    int count = 0, sum = 0, flag, temp;
    
    srand(time(0));
    
    for (int j = 1; j <= size_array;){
		flag = 0;
		temp = 1 + rand() % 2000;
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
	
    root_1 = NULL;
	root_2 = NULL; 
	
	
    for (int u = 1; u <= size_array; u++) {
        AVL(B[u], root_1);
    }
    
    for (int k = 1; k <= size_array; k++) {
        SDP_1(B[k], root_2);
    }

    cout << "________________________________________________________________________________________________________________________";
    cout << "Bypass_Left_Right(AVL):" << endl;
    BYPASS_LEFT_RIGHT(root_1);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "________________________________________________________________________________________________________________________";
    cout << "Bypass_Left_Right(SDP):" << endl;
    BYPASS_LEFT_RIGHT(root_2);
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


    int size_vertex_avl = size(root_1);
    int summa_avl = control_summa(root_1);
    int h_avl = height(root_1);
    float middle_h_avl = middle_height(root_1, 1) / float(size_vertex_avl);
    
    int size_vertex_sdp = size(root_2);
    int summa_sdp = control_summa(root_2);
    int h_sdp = height(root_2);
    float middle_h_sdp = middle_height(root_2, 1) / float(size_vertex_sdp);


    cout << "|-------|------|---------------|--------|---------------|" << endl;
    cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;
    cout << "|  AVL  | " << size_vertex_avl << "  | " << summa_avl << "         |    " << h_avl << "   |   " << middle_h_avl << "       |" << endl;
    cout << "|-------|------|---------------|--------|---------------|" << endl;
    cout << "|  SDP  | " << size_vertex_sdp << "  | " << summa_sdp << "         |    " << h_sdp << "   |   " << middle_h_sdp << "       |" << endl;
    cout << "|_______|______|_______________|________|_______________|" << endl;

	int number;
	for (int q = 0; q < 5; q++){
		cout << endl << endl << "-----------------------------------------------------------------------------------";
		cout <<  endl << "Write down the number: ";
		cin >> number;
		search(root_1, number);
		search(root_2, number);
		cout << endl;
	}
	
    return 0;
}

void LL(vertex*& p)
{
    vertex *q;
    q = p->left;
    p->Bal = 0;
    q->Bal = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR(vertex*& p)
{
    vertex *q;
    q = p->right;
    p->Bal = 0;
    q->Bal = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void RL(vertex*& p)
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

void LR(vertex*& p)
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

void AVL(int D, vertex*& p)
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
                    LL(p);
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
                    RR(p);
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


void SDP_1 (int D, vertex *&p){
	if (p == NULL){ 
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data){
		SDP_1(D, p->left);
	}
	else if (D >= p->data){  
		SDP_1(D, p->right);
	}
	else{
		cout << "Vertex already in the tree!" << endl;
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
