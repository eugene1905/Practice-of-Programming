#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 在此处补充你的代码
template<class T,class Pred,class T2>
T FindFirstLess(T s,T e,T2 a,Pred p){
    T res = e;
    for(T i = s; i != e; i++){
        if(p(*i,a)){
            res = i;
            break;
        }
    }
    return res;
}
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n ;
		string type; 
		cin >> n >> type;
		vector<int> vi;
		vector<string> vs;
		if( type == "N") {
			int a,m;
			for(int i = 0;i < n  - 1; ++i) {
				
				cin >> a;
				vi.push_back(a);
			}
			cin >> m;
			vector<int>::iterator p = FindFirstLess(vi.begin(),vi.end(),m,less<int>());
			if( p!= vi.end())
				cout << * p << endl;
			else
				cout << "Not Found" << endl; 
				
		}
		else {
			string a,m;
			for(int i = 0;i < n - 1; ++i) {
				cin >> a;
				vs.push_back(a);
			}
			cin >> m;
			vector<string>::iterator p = FindFirstLess(vs.begin(),vs.end(),m,less<string>());
			if( p!= vs.end())
				cout << * p << endl;
			else
				cout << "Not Found" << endl; 
		
		}
	}
    return 0;
}