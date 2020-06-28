#include <iostream>
using namespace std;

class A {
public:
    int v;
    A(int a):v(a){};
    operator int(){
        return v;
    }
    A& operator+=(int a){
        v += a;
        return *this;
    }
    A& operator-=(int a){
        v -= a;
        return *this;
    }
    A& getValue(){
        return *this;
    }
    
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}