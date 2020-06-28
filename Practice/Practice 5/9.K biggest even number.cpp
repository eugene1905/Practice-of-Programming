#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
// 在此处补充你的代码
public:
    int k;
    multiset<int> s;
    MyQueue(int a):k(a){}
    friend istream& operator>>(istream& i, MyQueue& a){
        int x;
        i >> x;
        if(x%2==0)a.s.insert(x);
        return i;
    }
    friend ostream& operator<<(ostream& o, MyQueue& a){
        int b = a.k;
        for(auto i = a.s.rbegin(); b > 0; b--,i++){
            o << *i << " ";
        }
        return o;
    }
};

int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		MyQueue q(k);
		for (int i = 0; i < n; ++i)
			cin >> q;
		cout<<q;
		cout << endl;
	}
	return 0; 
}