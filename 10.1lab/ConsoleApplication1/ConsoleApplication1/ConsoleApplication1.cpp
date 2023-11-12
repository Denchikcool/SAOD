#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 256;

struct Byte
{
	int ASCII_symbol;
	float probability;
};

void quicksortV3(Byte* arr, int n);
void quicksortV4(Byte* arr, int num);
void Shannon(Byte* P, int num);
void Fano(Byte* P, int L, int R, int k);
int Median(Byte* P, int L, int R);
void Huffman(Byte* P, int num);
int UP(int num, double q, Byte* P);
void DOWN(int num, int j);
void Gilbert_Murr(Byte* P, int num);
float AverageLengthCodeWord(Byte* P);
float AverageLengthCodeWordHUFFMAN(Byte* P, int num);
double Entropy(Byte* P);

float* Q;
int* Length;
int** C;

int main()
{
	srand(time(0));

	Byte P[n];
	int bytes[n] = { 0 };
	int sum = 0;
	unsigned char x;
	ifstream infile;
	infile.open("1.txt", ios::binary | ios::in);

	while (1)
	{
		infile.read((char*)&x, 1);

		if (infile.eof())
			break;

		bytes[x]++;
		sum++;

	}

	for (int i = 0; i < n; ++i)
	{
		P[i].ASCII_symbol = i;
		P[i].probability = (float)bytes[i] / (float)sum;
	}

	quicksortV3(P, n);

	int num = 0;
	for (int i = 0; i < n; i++)
	{
		if (P[i].probability != 0) num++;
	}

	double entropy_text = Entropy(P);

	Q = new float[num + 1];
	Length = new int[num];
	C = new int* [num];
	for (int i = 0; i < num; i++)	C[i] = new int[num];

	Shannon(P, num);
	float avg_length_code_word_SHANNON = AverageLengthCodeWord(P);

	cout << "SHANNON" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 0; P[i].probability != 0; i++)
	{
		printf("|%6c    | ", P[i].ASCII_symbol);
		printf("   %5lf    |      ", P[i].probability);
		for (int j = 0; j < Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	for (int i = 0; i < num; ++i)	delete C[i];
	delete[] Q;
	delete[] Length;
	delete[] C;

	cout << endl << "________________________________________________________" << endl << endl;

	Length = new int[num];
	C = new int* [num];
	for (int i = 0; i < num; i++)	C[i] = new int[num];

	for (int i = 0; i < num; ++i) {
		Length[i] = 0;
	}

	Fano(P, 0, num - 1, -1);
	float avg_length_code_word_FANO = AverageLengthCodeWord(P);

	cout << "FANO" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 0; P[i].probability != 0; i++)
	{
		printf("|%6c    | ", P[i].ASCII_symbol);
		printf("   %5lf    |      ", P[i].probability);
		if (Length[i] < Length[i - 1])
		{
			Length[i]++;
			C[i][Length[i] - 1] = 0;
		}
		for (int j = 0; j < Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	for (int i = 0; i < num; ++i)	delete C[i];
	delete[] Length;
	delete[] C;

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

	Byte P_Huffman_Work[n], P_Huffman_Print[n];
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
		printf("|%6c    | ", P_Huffman_Print[i].ASCII_symbol);
		printf("   %5lf    |      ", P_Huffman_Print[i].probability);
		for (int j = 1; j <= Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	for (int i = 1; i <= num; i++)	delete C[i];
	delete[] Length;
	delete[] C;

	Q = new float[num + 1];
	Length = new int[num + 1];
	C = new int* [num + 1];
	for (int i = 1; i < num + 1; i++)	C[i] = new int[num + 1];

	Byte P_Gilbert_Murr[n];
	for (int i = 1; i <= num; i++)
	{
		P_Gilbert_Murr[i].ASCII_symbol = P[i - 1].ASCII_symbol;
		P_Gilbert_Murr[i].probability = P[i - 1].probability;
	}

	quicksortV4(P_Gilbert_Murr, num + 1);

	Gilbert_Murr(P_Gilbert_Murr, num);
	float avg_length_code_word_GILBERT_MURR = AverageLengthCodeWordHUFFMAN(P_Gilbert_Murr, num);

	cout << "GILLBERT-MURR" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 1; i <= num; i++)
	{
		//if (P_Gilbert_Murr[i].probability != 0)
		//{
		printf("|%6c    | ", P_Gilbert_Murr[i].ASCII_symbol);
		printf("   %5lf    |      ", P_Gilbert_Murr[i].probability);
		for (int j = 1; j <= Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
		//}
	}
	cout << "________________________________________________________" << endl;

	for (int i = 1; i <= num; i++)	delete C[i];
	delete[] Length;
	delete[] C;

	cout << endl << "________________________________________________________" << endl << endl;
	cout << "________________________________________________" << endl;
	cout << "|Entropy of text | Average length of code word |" << endl;
	cout << "|                |-----------------------------|" << endl;
	cout << "|                | HUFFMAN | SHANNON | FANO | GILBERT-MUR |" << endl;
	cout << "|----------------|---------|---------|---------|" << endl;
	cout << "|     " << entropy_text << "        |    " << avg_length_code_word_HUFFMAN << " | " << avg_length_code_word_SHANNON << " | " << avg_length_code_word_FANO << "  |  " << avg_length_code_word_GILBERT_MURR << " | " << endl;

	return 0;
}

void quicksortV3(Byte* arr, int num)
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

void quicksortV4(Byte* arr, int num)
{
	int j, k, i;
	Byte temp;

	for (i = 0; i < num - 1; i++)
	{
		k = i;

		for (j = i + 1; j < num; j++)
			if (arr[j].ASCII_symbol < arr[k].ASCII_symbol) k = j;

		temp = arr[i];
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

void Shannon(Byte* P, int num)
{
	Q[0] = 0;

	for (int i = 1; i <= num; i++)
	{
		Q[i] = Q[i - 1] + P[i - 1].probability;
		Length[i - 1] = -floor(log2(P[i - 1].probability));
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < Length[i]; j++)
		{
			Q[i] *= 2;
			C[i][j] = floor(Q[i]);
			if (Q[i] >= 1) Q[i] -= 1;
		}
	}
}

void Fano(Byte* P, int L, int R, int k)
{
	int m;
	if (L < R)
	{
		k++;
		m = Median(P, L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m) C[i][k] = 0, Length[i]++;
			else
			{
				C[i][k] = 1;
				Length[i]++;
			}
		}
		Fano(P, L, m, k);
		Fano(P, m + 1, R, k);
	}
}

int Median(Byte* P, int L, int R)
{
	double Sum_L = 0;
	for (int i = L; i <= R; i++) Sum_L += P[i].probability;
	double Sum_R = P[R].probability;
	int m = R;
	while (Sum_L >= Sum_R)
	{
		Sum_L -= P[m].probability;
		m--;
		Sum_R += P[m].probability;
	}
	return m;
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

void Gilbert_Murr(Byte* P, int num)
{
	double pr = 0;
	for (int i = 1; i <= num; i++)
	{
		Q[i] = pr + P[i].probability / (double)2;
		pr += P[i].probability;
		Length[i] = -ceil(log2(P[i].probability)) + 1;
	}
	for (int i = 1; i <= num; i++)
	{
		for (int j = 1; j <= Length[i]; j++)
		{
			Q[i] = Q[i] * 2;
			C[i][j] = trunc(Q[i]);
			if (Q[i] > 1) Q[i]--;
		}
	}
}

double Entropy(Byte* P)
{
	double sum = 0;
	for (int i = 0; P[i].probability != 0; i++)
	{
		sum += -P[i].probability * log2(P[i].probability);
	}
	return sum;
}

float AverageLengthCodeWord(Byte* P)
{
	float sum = 0;
	for (int i = 0; i < n; i++) sum += P[i].probability * Length[i];
	return sum;
}

float AverageLengthCodeWordHUFFMAN(Byte* P, int num)
{
	float sum = 0;
	for (int i = 1; i <= num; i++) sum += P[i].probability * Length[i];
	return sum;
}