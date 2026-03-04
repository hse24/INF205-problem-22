//Henrik Sam Eyde, NMBU
#include <iostream>
using namespace std;

int main () {
	int j;
	unsigned char* c;
	short s = -12; // size 2
	int i = -12; // size 4
	long l = -12; // size 4
	long long ll = -12; // size 8
	cout << "-12 som short:\n";
	c = (unsigned char*)&s;
	for (j = 0; j != sizeof(short); j++) {
		cout << hex << (int)*c / 16 << "\t";
		cout << hex << (int)*c % 16 << "\n";
		c++;
	}
	cout << "-12 som int:\n";
	c = (unsigned char*)&i;
	for (j = 0; j != sizeof(int); j++) {
		cout << hex << (int)*c / 16 << "\t";
		cout << hex << (int)*c % 16 << "\n";
		c++;
	}
	cout << "-12 som long:\n";
	c = (unsigned char*)&l;
	for (j = 0; j != sizeof(long); j++) {
		cout << hex << (int)*c / 16 << "\t";
		cout << hex << (int)*c % 16 << "\n";
		c++;
	}
	cout << "-12 som long long:\n";
	c = (unsigned char*)&ll;
	for (j = 0; j != sizeof(long long); j++) {
		cout << hex << (int)*c / 16 << "\t";
		cout << hex << (int)*c % 16 << "\n";
		c++;
	}
	cout << "dette forteller oss at -12 ligger 11 plasser lavere enn den \"høyeste\" mulige verdien\n";
	return 0;
}
