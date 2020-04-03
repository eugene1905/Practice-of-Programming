#include<cstdio>
#include<map>
#include<string>
using namespace std;
int main(){
	map<int,int> s;
	int n;
	scanf("%d",&n);
	s.insert(make_pair(100000,1));
	while(n--){
		map<int,int>::const_iterator lpos, rpos, pos;
		int id, strength;
		scanf("%d%d",&id,&strength);
		s.insert(make_pair(strength,id));
		pos = rpos = lpos = s.find(strength);
		if(pos == s.begin())
			pos++;
		else if(pos == --s.end())
			pos--;
		else{
			rpos++;
			lpos--;
			pos = rpos;
			if(strength - lpos->first <= rpos->first - strength)
				pos = lpos;	
		}
		printf("%d %d\n",id, pos->second);
	}
}
