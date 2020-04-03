#include <iostream>
#include <list>
#include <cstring>
using namespace std;
int main(){
	int n;
	cin >> n;
	string cmd;
	list<int>* s[10005];
	while(n--){
		cin >> cmd;
		if (cmd == "new"){
			int a;
			cin >> a;
			s[a] = new list<int>;
		}
		
		else if(cmd == "add"){
			int a, b;
			cin >> a >> b;
			s[a]->push_back(b);
		}	
		
		else if (cmd == "merge"){
			int a, b;
			cin >> a >> b;
			s[a]->merge(*s[b]);
			
		}
		
		else if (cmd == "unique"){
			int a;
			cin >> a;
			s[a]->sort();
			s[a]->unique();
		}
		
		else if (cmd == "out"){
			int a;
			cin >> a;
			s[a]->sort();
			for(list<int>::const_iterator ii = s[a]->begin(); ii != s[a]->end(); ++ii){
				cout << *ii << " ";
			}
			cout << endl;
		}
	}
}
