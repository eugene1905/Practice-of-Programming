#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(T* b, T* e){
	T* tmp = b;
	T a = *tmp++;
	while(tmp!=e){
		a += *tmp;
		tmp++;
	}
	return a;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //??:1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}
