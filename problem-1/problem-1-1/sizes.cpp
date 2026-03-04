//Henrik Sam Eyde, NMBU
#include <iostream>
using namespace std;

int main () {
	cout << "På denne maskinen er de fundamentale datatypene følgelig store:\n";	
	cout << "type:\t\tsize:\n";
	cout << "char\t\t" << sizeof(char) << "\n";
	cout << "bool\t\t" << sizeof(bool) << "\n";
	cout << "short\t\t" << sizeof(short) << "\n";
	cout << "int\t\t" << sizeof(int) << "\n";
	cout << "long\t\t" << sizeof(long) << "\n";
	cout << "long long\t" << sizeof(long long) << "\n";
	cout << "unsigned\t" << sizeof(unsigned) << "\n";
	cout << "double\t\t" << sizeof(double) << "\n";
	cout << "Eksempel med short:\n";
	short* p;
	cout << "p før inkrementering:\t" << p << "\n";
	p++;
	cout << "p etter inkrementering:\t" << p << "\n";
	return 0;
}
