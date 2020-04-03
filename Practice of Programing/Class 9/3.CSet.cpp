#include <iostream>
#include <set>
#include <cstring>
using namespace std;
int main(){
	int n;
	cin >> n;
	string cmd;
	multiset<int> s;
	set<int> rec;
	while(n--){
		cin >> cmd;
		if(cmd == "add"){
			int a;
			cin >> a;
			s.insert(a);
			rec.insert(a);
			cout << s.count(a) << endl;
		}	
		else if(cmd == "del"){
			int a;
			cin >> a;
			cout << s.count(a) << endl;
			s.erase(s.lower_bound(a),s.upper_bound(a));
		}
		
		
		else if (cmd == "ask"){
			int a;
			cin >> a;
			cout << (rec.find(a) != rec.end()?1:0) << " " << s.count(a) << endl;
		}
	}
}
