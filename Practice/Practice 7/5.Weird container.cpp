#include <iostream>
#include <string>
using namespace std;
template <class T> 
class container{
// 在此处补充你的代码
public:
    T v;
    container(T a):v(a){}
    container operator+(const container& a){
        container tmp = *this;
        tmp.v += a.v + a.v;
        return tmp;
    }
    container operator+(const T& a){
        container tmp = *this;
        tmp.v += a;
        return tmp;
    }
    friend ostream& operator<<(ostream& o, container a){
        o << a.v;
        return o;
    }
};
int main(){
	int n,m;
	cin >> n >> m;
	string s1,s2;
	cin >> s1 >> s2;
    container <int> a = n;
    container <int> b = m;
    cout<<a+b<<endl;
    cout<<a+m<<endl;
    container <string> sa = string(s1);
    container <string> sb = string(s2);
    cout<<sa+sb<<endl;
    cout<< sa + s2<<endl;
}