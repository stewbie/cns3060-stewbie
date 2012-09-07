#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	cout << "B. Darren Olson\n";
	cout << "CNS 3060\n";
	for(int i =0; i < argc; i++) {
		cout << argv[i] << endl;
	}
	return 0;
}
