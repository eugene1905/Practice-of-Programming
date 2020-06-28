#include <iostream>
#include <string>
using namespace std;
template<class T,int n = 1000>
class A{
public:
    T arr[n];
    int l;
    A():l(n){}
    A(T *b){
		l = n;
        for(int i = 0; i < l; i++)
            arr[i] = b[i];
    }
	A(const A &a){
		l = a.l;
		for(int i = 0; i < l; i++)
			arr[i] = a.arr[i];
	}
	T operator[](int a){
		return arr[a];
	}
	T sum(){
		T x = arr[0];
		for(int i = 1; i < l; i++){
			x += arr[i];
		}
		return x;
	}

};
int main() {
	
	int t;
	cin >> t;
	while( t -- ) { 
	    int b1[10];
	    for(int i = 0;i < 10; ++i) 	
	    	cin >> b1[i];
	    A<int, 10> a1 = b1;
	    cout << a1[2] << endl;
	    
	
	    double b2[5] ;
	    for(int i = 0;i < 5; ++i) 	
	    	cin >> b2[i];
	    
	    A<double, 5> a2 = b2;
	    cout << a2.sum() << endl;
	
		
	    string b3[4] ;
	    for(int i = 0;i < 4; ++i) 	
	    	cin >> b3[i];
	    
	    A<string, 4> a3 = b3;
	    cout << a3.sum() << endl;
	}
	return 0;
}