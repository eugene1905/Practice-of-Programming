#include <iostream>
using namespace std;

int bitManipulation1(int n, int m, int i) {
	return ((n | (1 << i)) & ((0xffffffff ^ (1 << i)) | m ));
}

int main() {
	int n, m, i, t;
	cin >> t;
	while (t--) { 
		cin >> n >> m >> i;
		cout << bitManipulation1(n, m, i) << endl;
	}
	return 0;
}
//n:XXXXXXXXXX1XXXXXXXX
//m:1111111111Y11111111
//n & m -> XXXXXXXXXYXXXX
