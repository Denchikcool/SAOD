#include <iostream>
#include <iomanip>
#include <windows.h>
#include <math.h>
using namespace std;


string binary(unsigned char num) {
	string answer = "";
	for (int i = sizeof(num) * 8; i > 0; i--) {
		if ((num & (1 << (i - 1))) != 0) {
			answer += '1';
		}
		else {
			answer += '0';
		}
	}
	return answer;
}

string fixedVariable(unsigned char num) {
	short int size = 8 * sizeof(num);
	unsigned char order = 0;
	string answer = "";

	for (int i = size; i > 0; i--) {
		if ((num & (1 << (i - 1))) != 0) {
			order = i;
			break;
		}
	}

	int temp = 0;
	while (pow(2, temp) <= size)
		temp++;

	for (int i = temp; i > 0; i--) {
		if ((order & (1 << (i - 1))) != 0) {
			answer += '1';
		}
		else {
			answer += '0';
		}
	}
	answer += ' ';

	for (int i = (order - 1); i > 0; i--) {
		if ((num & (1 << (i - 1))) != 0) {
			answer += '1';
		}
		else {
			answer += '0';
		}
	}
	return answer;
}

string gammaCodeElias(unsigned char num) {

	short int size = 8 * sizeof(num);
	unsigned char order = 0;
	string answer = "";

	for (int i = size; i > 0; i--) {
		if ((num & (1 << (i - 1))) != 0) {
			order = i;
			break;
		}
	}

	for (int i = (order - 1); i > 0; i--)
		answer += '0';

	answer += ' ';

	for (int i = order; i > 0; i--) {
		if ((num & (1 << (i - 1))) != 0) {
			answer += '1';
		}
		else {
			answer += '0';
		}
	}
	return answer;
}

string omegaCodeElias(unsigned char num) {
	if (num == 0)
		return "";

	short int size = 8 * sizeof(num);
	unsigned char order = 0;
	string temp = "";
	string answer = "0";

	while (num != 1) {
		temp = "";

		for (int i = size; i > 0; i--) {
			if ((num & (1 << (i - 1))) != 0) {
				order = i;
				break;
			}
		}

		for (int i = order; i > 0; i--) {
			if ((num & (1 << (i - 1))) != 0) {
				temp += '1';
			}
			else {
				temp += '0';
			}
		}
		temp += " " + answer;
		answer = temp;
		num = order - 1;

	}

	return answer;
}

int main(int argc, const char** argv) {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	unsigned char number = 0;

	cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "|" << setw(15) << "";
	cout << "|                           |                                              Code word                                          |" << "\n";

	cout << "|" << setw(15) << "  Number    ";
	cout << "|     Binary code           |-------------------------------------------------------------------------------------------------|" << "\n";

	cout << "|" << setw(15) << "";
	cout << "|                           |          Fixed + Variable     |            gamma-kod Ellias          |            omega-kod Ellias      |" << "\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << "\n";

	do
	{
		cout << "|";
		cout << left << setw(15) << (int)number;
		cout << "|";
		cout << left << setw(27) << binary(number);
		cout << "|";
		cout << left << setw(31) << fixedVariable(number);
		cout << "|";
		cout << left << setw(34) << gammaCodeElias(number);
		cout << "|";
		cout << left << setw(30) << omegaCodeElias(number);
		cout << "|";
		cout << "\n";

		number++;
	} while (number != 0);


	return 0;
}
