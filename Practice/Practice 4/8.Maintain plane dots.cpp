#include <set>
#include <iostream>
#include <string>
using namespace std;
class myComp{
public:
    myComp(){}
    typedef pair<int,int> T;
    bool operator()(const T& a,const T& b)const{
        int x1 = a.first, x2 = b.first, y1 = a.second, y2 = b.second;
        if(x1 == -1 || x2 == -1)return y1 > y2;
        else return x1 < x2;
    }
};
int main() {
	string cmd;
	set<pair<int, int>, myComp> S;
	while (cin >> cmd) {
		if (cmd == "A") {
			int x, y;
			cin >> x >> y;
			S.insert(make_pair(x, y));
		} else if (cmd == "Qx") {
			int x;
			cin >> x;
			cout << S.lower_bound(make_pair(x, -1))->second << endl;
		} else if (cmd == "Qy") {
			int y;
			cin >> y;
			cout << S.lower_bound(make_pair(-1, y))->first << endl;
		} else {
			int x, y;
			cin >> x >> y;
			S.erase(make_pair(x, y));
		}
	}
	return 0;
}