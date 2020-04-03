#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
string monster_name[5] = {"dragon","ninja","iceman","lion","wolf"};
int monster_red_order[5]= {2,3,4,1,0}; 
int monster_blue_order[5] = {3,0,1,2,4};
int monster_hp[5]; //Standard hp of dragon, ninja, iceman, lion, wolf
string weapon_list[3] = {"sword","bomb","arrow"};
int t = 0;


class monster{
	public:
		virtual void spawnMob(int a,int b)=0;
		virtual void printSpawn(string a, int b)=0;
		friend class city;
};
class dragon:public monster{
	private:
		int id;
		int hp;
		string weapon;
		double morale;
	public:
		void spawnMob(int total_mob, int gem){
			id = total_mob;
			hp = monster_hp[0];
			weapon = weapon_list[id%3];
			morale = double(gem) / double(monster_hp[0]);
		}	
		void printSpawn(string city_name, int type_amount){
			cout << setw(3) << setfill('0') << t; 
			cout << " " << city_name << " dragon " << id;
			cout << " born with strength " << hp;
			cout << "," << type_amount << " dragon in " ;
			cout << city_name << " headquarter" << endl;
			cout << fixed << setprecision(2) << "It has a " << weapon << ",and it's morale is " << morale << endl;			 
		}
};
class ninja:public monster{
	private:
		int id;
		int hp;
		string weapon1;
		string weapon2;
	public:
		void spawnMob(int total_mob, int gem){
			id = total_mob;
			hp = monster_hp[1];
			weapon1 = weapon_list[id%3];
			weapon2 = weapon_list[(id+1)%3];			
		}
		void printSpawn(string city_name, int type_amount){
			cout << setw(3) << setfill('0') << t; 
			cout << " " << city_name << " ninja " << id;
			cout << " born with strength " << hp;
			cout << "," << type_amount << " ninja in " ;
			cout << city_name << " headquarter" << endl;
			cout << "It has a " << weapon1 << " and a " << weapon2 << endl;			 
		}				
};
class iceman:public monster{
	private:
		int id;
		int hp;
		string weapon;
	public:
		void spawnMob(int total_mob, int gem){
			id = total_mob;
			hp = monster_hp[2];
			weapon = weapon_list[id%3];		
		}
		void printSpawn(string city_name, int type_amount){
			cout << setw(3) << setfill('0') << t; 
			cout << " " << city_name << " iceman " << id;
			cout << " born with strength " << hp;
			cout << "," << type_amount << " iceman in " ;
			cout << city_name << " headquarter" << endl;
			cout << "It has a " << weapon << endl;				 
		}		
};
class lion:public monster{
	private:
		int id;
		int hp;
		int loyalty;
	public:
		void spawnMob(int total_mob, int gem){
			id = total_mob;
			hp = monster_hp[3];
			loyalty = gem;			
		}
		void printSpawn(string city_name, int type_amount){
			cout << setw(3) << setfill('0') << t; 
			cout << " " << city_name << " lion " << id;
			cout << " born with strength " << hp;
			cout << "," << type_amount << " lion in " ;
			cout << city_name << " headquarter" << endl;
			cout << "It's loyalty is " << loyalty << endl;			 
		}
};
class wolf: public monster{
	private:
		int id;
		int hp;
	public:
		void spawnMob(int total_mob, int gem){
			id = total_mob;
			hp = monster_hp[4];		
		}
		void printSpawn(string city_name, int type_amount){
			cout << setw(3) << setfill('0') << t; 
			cout << " " << city_name << " wolf " << id;
			cout << " born with strength " << hp;
			cout << "," << type_amount << " wolf in " ;
			cout << city_name << " headquarter" << endl;			 
		}	
};

class city{
	private:
		string name;
		int gem;
		int monster_order[5];
		int each_monster_amount[5];
		int total_monster_amount;
		int current_monster_type;
		monster* monster_team[5000];
	public:
		bool flag;
		void setRed(int m){
			name = "red";
			memcpy(monster_order,monster_red_order,sizeof(monster_order));
			memset(each_monster_amount,0,sizeof(each_monster_amount));
			total_monster_amount = 0;
			current_monster_type = 0;
			gem = m;
			flag = false;
		}
		void setBlue(int m){
			name = "blue";
			memcpy(monster_order,monster_blue_order,sizeof(monster_order));
			memset(each_monster_amount,0,sizeof(each_monster_amount));
			total_monster_amount = 0;
			current_monster_type = 0;
			gem = m;
			flag = false;
		}
		void spawnMonster(){
			if (flag)return;
			for (int i = 0; i < 5; i++){
				if (gem >= monster_hp[monster_order[current_monster_type]])break;
				else{//Skip Turns
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;
					if (i == 4){
						flag = true;
						cout << setw(3) << setfill('0') << t; 
						cout << " " << name << " headquarter stops making warriors " << endl;
						return;
					}
					continue;
				}
			}
			switch (monster_order[current_monster_type]){
				case 0:
					gem -= monster_hp[0];
					total_monster_amount++;
					each_monster_amount[0]++;
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;					
					monster_team[total_monster_amount-1] = new dragon();
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[0]);
					break;
				case 1:
					gem -= monster_hp[1];
					total_monster_amount++;
					each_monster_amount[1]++;
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;					
					monster_team[total_monster_amount-1] = new ninja();
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[1]);
					break;
				case 2:
					gem -= monster_hp[2];
					total_monster_amount++;
					each_monster_amount[2]++;
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;				
					monster_team[total_monster_amount-1] = new iceman();
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[2]);
					break;
				case 3:
					gem -= monster_hp[3];
					total_monster_amount++;
					each_monster_amount[3]++;
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;
					monster_team[total_monster_amount-1] = new lion();
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[3]);
					break;					
				case 4:	
					gem -= monster_hp[4];
					total_monster_amount++;
					each_monster_amount[4]++;
					current_monster_type++;
					if (current_monster_type == 5)
						current_monster_type = 0;					
					monster_team[total_monster_amount-1] = new wolf();
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[4]);
					break;																	
			}
		}
};
int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cout << "Case:" << i+1 << endl;
		city red,blue;
		int m;
		cin >> m;
		for (int j = 0; j < 5; j++)
		{
			cin >> monster_hp[j];
		}
		red.setRed(m);
		blue.setBlue(m);
		t = 0;
		while(true)
		{
			if (red.flag && blue.flag)break;
			red.spawnMonster();
			blue.spawnMonster();
			t++;
		}
		
	}
}
