#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A{
public:
    int id;
    A(int k):id(k){}
    virtual void get_name(){
        cout << "A";
    }
    virtual void get_ID(){
        cout << id;
    }
    A(){};
};
class B:public A{
    public:
        B(int k):A(k){}
        virtual void get_name(){
            cout << "B";
        }
        virtual void get_ID(){
            cout << id;
        }

};
class Comp{
public:
    bool operator()(const A* x, const A* y)const{
        return x->id < y->id;
    }
};

void Print(A* a){
    a->get_name();
    cout << " ";
    a->get_ID();
    cout << endl;
}
int main()
{

	int t;
	cin >> t;
	set<A*,Comp> ct;
	while( t -- ) {
		int n;
		cin >> n;
		ct.clear();
		for( int i = 0;i < n; ++i)	{
			char c; int k;
			cin >> c >> k;
			
			if( c == 'A')
				ct.insert(new A(k));
			else
				ct.insert(new B(k));
		}	
		for_each(ct.begin(),ct.end(),Print);
		cout << "****" << endl;
	}
}