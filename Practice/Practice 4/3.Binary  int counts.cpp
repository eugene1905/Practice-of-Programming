#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Pred{
	public:
		int pos;
		int n;
		Pred(int x):pos(x){
			n = 1 << pos;
		}
		operator int(){
			return n;
		}
};

int count_if(vector<int>::iterator s,vector<int>::iterator e, Pred p){
	int cnt = 0;
	for(auto i = s; i != e; i++){
		int k = *i;
		if((k & p) == p){
			cnt++;
		}
	}
	return cnt;
}
int main(int argc, char** argv) {	
	int n, x;
	vector<int> intVec;
	cin>>n>>x; 
	while(x) {
		intVec.push_back(x);
		cin>>x;
	}
	cout<<count_if(intVec.begin(), intVec.end(), Pred(n))<<endl;
	return 0;
}