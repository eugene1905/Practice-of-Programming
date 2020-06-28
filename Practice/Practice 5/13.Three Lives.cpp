#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama{
	public:
	char name[100];
	int actor;
	int story;
	int acting_skill;
    TV_Drama(char* a, int b, int c, int d):actor(b),story(c),acting_skill(d){
		for(int i = 0; i < 100; i++)
			name[i] = a[i];
	}
	bool operator<(TV_Drama x){
		return actor > x.actor;
	}
};

void Printer(TV_Drama i){
    cout << i.name << ";";
}
bool comparator_1(TV_Drama x, TV_Drama y){
	return x.story > y.story;
}
class comparator_2{
	public:
		comparator_2(){}
		bool operator()(TV_Drama x, TV_Drama y){
			return x.acting_skill > y.acting_skill;
		}
};

int main(){
	list<TV_Drama> lst;
	int n;
	
	cin>>n;
	char  _name[100];
	int _actor, _story, _acting_skill;
	for (int i=0; i<n; i++){
        cin.ignore();
        cin.getline(_name,100);
        cin>>_actor>>_story>>_acting_skill;
		lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
	}

	lst.sort();
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_1);
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_2());
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	return 0;
}