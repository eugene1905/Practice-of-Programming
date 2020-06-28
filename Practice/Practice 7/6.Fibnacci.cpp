#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
class Fib{
public:
    int v1,v2;
    int id;
    Fib(int a):v1(1),v2(1),id(a){}
    Fib& operator++(){
        id++;
        if(id != 2){
            int tmp = v2;
            v2 = v1 + v2;
            v1 = tmp;
        } 
        return *this;
    }
    bool operator!=(const Fib& a){
        return id != a.id;
    }
    int operator*(){
        return v2;
    }

};
// 在此处补充你的代码
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}