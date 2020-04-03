#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;
string monster_name[5] = {"dragon","ninja","iceman","lion","wolf"};
int monster_red_order[5]= {2,3,4,1,0}; 
int monster_blue_order[5] = {3,0,1,2,4};
int monster_hp[5]; //Standard hp of dragon, ninja, iceman, lion, wolf
int monster_ad[5];
string weapon_list[3] = {"sword","bomb","arrow"};
int lion_decrease = 0;
int t = 0;
int n = 0;
bool redTaken = false;
bool blueTaken = false;
class Weapon{
	public:
		int id;
		virtual int damage(int ad)=0;
		int durability;
		bool flag;
		virtual bool broken() = 0;
};
class sword:public Weapon{
	public:
		sword(){
			id = 0;
			flag = false;
		}
		int damage(int ad){
			return ad*2/10;
		}
		bool broken(){
			return flag;
		};
};
class bomb:public Weapon{
	public:
		bomb(){
			id = 1;
			durability = 1;
			flag = false;
		}
		int damage(int ad){
			return ad*4/10;
		}
		bool broken(){
			durability--;
			flag = true;
			return flag;
		}
};
class arrow:public Weapon{
	public:
		arrow(){
			id=2;
			durability = 2;
			flag = false;
		}
		int damage(int ad){
			return ad*3/10;
		}
		bool broken(){
			durability --;
			if (durability == 0)
				flag = true;
			return flag;
		}
};

class monster{
	public:
		string name;
		int id;
		int hp;
		int ad;
		int current_position;
		int camp;
		int total_weapon;
		int current_weapon;
		int loyalty;
		bool isAlive;
		Weapon* weapon[10];	
		void printStat(){
			int weapon0 = 0;
			int weapon1 = 0;
			int weapon2 = 0;
			sortWeapon();
			for (int i = 0; i < 10; i++){
				if(weapon[i] == NULL)
					break;
				if(weapon[i]->id == 0)
					weapon0++;
				else if(weapon[i]->id == 1)
					weapon1++;
				else if(weapon[i]->id == 2)
					weapon2++;
			}
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red ":" blue ");
			printNameAndID();
			cout << " has " << weapon0 << " sword";
			cout << " " << weapon1 << " bomb";
			cout << " " << weapon2 << " arrow and ";
			cout << hp << " elements" << endl;
			
		}
		virtual void printYell() = 0;	
		void spawnWeapon(int total_weapon,int weapon_id){
			switch(weapon_id){
				case 0:
					weapon[total_weapon] = new sword();
					break;
				case 1:
					weapon[total_weapon] = new bomb();
					break;
				case 2:
					weapon[total_weapon] = new arrow();
					break;
			}
		}
		virtual void stealWeapon(monster* a) = 0;
		virtual void printEscape() = 0;
		virtual void spawnMob(int a,int b,int c)=0;
		virtual void printSpawn(string a, int b)=0;
		virtual void moveForward(int camp) = 0;
		virtual void attackEnemy(monster* a)=0;
		void printNameAndID(){
			cout << name << " " << id;
		}
		void sortWeapon(){
			for(int i = 0; i < 10; i++){
				for (int j = i+1 ; j < 10; j++){
					if(weapon[j] == NULL)
						continue;
					if(weapon[i] == NULL && weapon[j] != NULL){
						swap(weapon[i],weapon[j]);
						continue;
					}
					if (weapon[i]->id > weapon[j]->id){
						swap(weapon[i],weapon[j]);
					}
					if (weapon[i]->id == 2 && weapon[j]->id == 2 && weapon[i]->durability > weapon[j]->durability){
						swap(weapon[i],weapon[j]);
					}
				}
			}
			current_weapon = 0;
		}
		void sortWeapon2(){
			for(int i = 0; i < 10; i++){
				for (int j = i+1 ; j < 10; j++){
					if(weapon[j] == NULL)
						continue;
					if(weapon[i] == NULL && weapon[j] != NULL){
						swap(weapon[i],weapon[j]);
						continue;
					}
					if (weapon[i]->id > weapon[j]->id){
						swap(weapon[i],weapon[j]);
					}
					if (weapon[i]->id == 2 && weapon[j]->id == 2 && weapon[i]->durability < weapon[j]->durability){
						swap(weapon[i],weapon[j]);
					}
				}
			}
			current_weapon = 0;
		}
		int minWeaponId(){
			sortWeapon2();
			if (weapon[0] == NULL)
				return 3;
			return weapon[0]->id;			
		}
		void hurted(int a){
			hp -= a;
			if (hp <= 0)
				isAlive = false;
		}	 
		void takeWeapon(monster* a){
			sortWeapon();
			while(true){
				if(total_weapon == 10 || a->noWeapon())
					break;
				a->sortWeapon2();
				weapon[total_weapon] = a->weapon[0];
				a->weapon[0]=NULL;
				a->total_weapon--;
				total_weapon++;
			}
		}
		bool noWeapon(){
			if(total_weapon == 0)
				return true;
			return false;
		}	
		friend class Headquarter;
		friend class weapon;
};
class City{
	public:
		int id;
		monster* blue;
		monster* red;
		City():blue(NULL),red(NULL){}
		void setInfo(int a){
			blue = NULL;
			red = NULL;
			id = a;
		}
		void red_march(){
			red->moveForward(0);			
		}
		void blue_march(){
			blue->moveForward(1);
		}
		void scanRedBlue(){
			if(red != NULL && red->hp <= 0)
				red = NULL;
			if (blue != NULL && blue->hp <= 0)
				blue = NULL;
		}		
};
City city[21];
class dragon:public monster{
	private:
		double morale;
	public:
		void stealWeapon(monster* a){};
		void printEscape(){};		
		void spawnMob(int total_mob, int gem,int pos){
			for(int i = 0; i < 10; i++){
				weapon[i] = NULL;
			}
			isAlive = true;
			total_weapon = 0;
			name = "dragon";
			camp = (pos == 0? 0:1);
			current_position = pos;
			id = total_mob;
			hp = monster_hp[0];
			ad = monster_ad[0];
			morale = double(gem) / double(monster_hp[0]);
			spawnWeapon(0,id%3);			
			total_weapon++;
		}
		void printSpawn(string Headquarter_name, int type_amount){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << Headquarter_name << " dragon " << id << " born" << endl;			 
		}
		void moveForward(int camp){
			if(camp)
				current_position--;
			else
				current_position++;
			if(camp == 0){
				if(current_position == n+1){
					blueTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " dragon " << id << " reached blue headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return;
				}
			}

			else{
				if(current_position == 0){
					redTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " dragon " << id << " reached red headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return; 					
				}			
			}

			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " dragon " << id << " marched to city " << current_position;
			cout << " with " << hp << " elements and force " << ad << endl; 		
		}
		void attackEnemy(monster* a){
			if (!isAlive)
				return;
			if(total_weapon > 0){
				a->hurted(weapon[current_weapon]->damage(ad));
				if (weapon[current_weapon]->id == 1)
					this->hurted(weapon[current_weapon]->damage(ad)/2);
				if(weapon[current_weapon]->broken()){
					weapon[current_weapon] = NULL;
					total_weapon--;
				}
				current_weapon++;
				if(current_weapon == 10)
					current_weapon = 0;
				while(weapon[current_weapon] == NULL){
					if(total_weapon == 0)
						break;
					current_weapon++;
					if(current_weapon == 10)
						current_weapon = 0;
				}
			}
		}
		void printYell(){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " dragon " << id << " yelled in city " << current_position << endl;
		}
};
class ninja:public monster{
	public:
		void stealWeapon(monster* a){};
		void printEscape(){};		
		void spawnMob(int total_mob, int gem, int pos){
			for(int i = 0; i < 10; i++){
				weapon[i] = NULL;
			}
			isAlive = true;
			total_weapon = 0;
			name = "ninja";
			camp = (pos == 0? 0:1);
			current_position = pos;			
			id = total_mob;
			hp = monster_hp[1];
			ad = monster_ad[1];
			spawnWeapon(0,id%3);
			spawnWeapon(1,(id+1)%3);		
			total_weapon+=2;	
		}
		void printYell(){};
		void printSpawn(string Headquarter_name, int type_amount){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << Headquarter_name << " ninja " << id << " born" << endl;	 
		}				
		void moveForward(int camp){
			if(camp)
				current_position--;
			else
				current_position++;
			if(camp == 0){
				if(current_position == n+1){
					blueTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " ninja " << id << " reached blue headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return;
				}
			}

			else{
				if(current_position == 0){
					redTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " ninja " << id << " reached red headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return; 					
				}			
			}
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " ninja " << id << " marched to city " << current_position;
			cout << " with " << hp << " elements and force " << ad << endl; 	
		}
		void attackEnemy(monster* a){
			if (!isAlive)
				return;
			if(total_weapon > 0){
				a->hurted(weapon[current_weapon]->damage(ad));
				if(weapon[current_weapon]->broken()){
					weapon[current_weapon] = NULL;
					total_weapon--;
				}
				current_weapon++;
				if(current_weapon == 10)
					current_weapon = 0;
				while(weapon[current_weapon] == NULL){
					if(total_weapon == 0)
						break;
					current_weapon++;
					if(current_weapon == 10)
						current_weapon = 0;
				}
			}
		}
};
class iceman:public monster{
	public:
		void stealWeapon(monster* a){};
		void printEscape(){};
		void spawnMob(int total_mob, int gem,int pos){
			for(int i = 0; i < 10; i++){
				weapon[i] = NULL;
			}
			isAlive = true;
			total_weapon = 0;
			name = "iceman";
			camp = (pos == 0? 0:1);
			current_position = pos;			
			id = total_mob;
			hp = monster_hp[2];
			ad = monster_ad[2];
			spawnWeapon(0,id%3);
			total_weapon++;		
		}
		void printYell(){};
		void printSpawn(string Headquarter_name, int type_amount){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << Headquarter_name << " iceman " << id << " born" << endl;	 
		}		
		void moveForward(int camp){
			if(camp)
				current_position--;
			else
				current_position++;
			hp -= hp / 10;
			if (hp == 0){
				isAlive = false;
				if(camp)
					city[current_position].blue = NULL;
				else
					city[current_position].red = NULL;			
			}
			if(camp == 0){
				if(current_position == n+1){
					blueTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " iceman " << id << " reached blue headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return;
				}
			}

			else{
				if(current_position == 0){
					redTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " iceman " << id << " reached red headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return; 					
				}			
			}
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " iceman " << id << " marched to city " << current_position;
			cout << " with " << hp << " elements and force " << ad << endl; 	
		}
		void attackEnemy(monster* a){
			if (!isAlive)
				return;			
			if(total_weapon > 0){
				a->hurted(weapon[current_weapon]->damage(ad));
				if (weapon[current_weapon]->id == 1)
					this->hurted(weapon[current_weapon]->damage(ad)/2);
				if(weapon[current_weapon]->broken()){
					weapon[current_weapon] = NULL;
					total_weapon--;
				}
				current_weapon++;
				if(current_weapon == 10)
					current_weapon = 0;
				while(weapon[current_weapon] == NULL){
					if(total_weapon == 0)
						break;
					current_weapon++;
					if(current_weapon == 10)
						current_weapon = 0;
				}
			}
		}		
};
class lion:public monster{
	public:
		void stealWeapon(monster* a){};
		void spawnMob(int total_mob, int gem,int pos){
			for(int i = 0; i < 10; i++){
				weapon[i] = NULL;
			}
			isAlive = true;
			total_weapon = 0;
			name = "lion";
			camp = (pos == 0? 0:1);
			current_position = pos;
			id = total_mob;
			ad = monster_ad[3];
			hp = monster_hp[3];
			loyalty = gem;
			spawnWeapon(total_weapon,id%3);
			total_weapon++;			
		}
		void printYell(){};
		void printSpawn(string Headquarter_name, int type_amount){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << Headquarter_name << " lion " << id << " born" << endl;
			cout << "Its loyalty is " << loyalty << endl;			 
		}
		void printEscape(){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " lion " << id << " ran away" << endl;
			hp = 0;
			isAlive = false;
		}
		void moveForward(int camp){
			if(camp == 1)
				current_position--;
			else
				current_position++;
			if(camp == 0){
				if(current_position == n+1){
					blueTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " lion " << id << " reached blue headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return;
				}
			}

			else{
				if(current_position == 0){
					redTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " lion " << id << " reached red headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return; 					
				}			
			}	
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " lion " << id << " marched to city " << current_position;
			cout << " with " << hp << " elements and force " << ad << endl; 	
			loyalty -= lion_decrease;
		}	
		void attackEnemy(monster* a){
			if (!isAlive)
				return;
			if(total_weapon > 0){
				a->hurted(weapon[current_weapon]->damage(ad));
				if (weapon[current_weapon]->id == 1)
					this->hurted(weapon[current_weapon]->damage(ad)/2);
				if(weapon[current_weapon]->broken()){
					weapon[current_weapon] = NULL;
					total_weapon--;
				}
				current_weapon++;
				if(current_weapon == 10)
					current_weapon = 0;
				while(weapon[current_weapon] == NULL){
					if(total_weapon == 0)
						break;
					current_weapon++;
					if(current_weapon == 10)
						current_weapon = 0;
				}
			}
		}		
};
class wolf: public monster{
	public:
		void printEscape(){};
		void spawnMob(int total_mob, int gem, int pos){
			for(int i = 0; i < 10; i++){
				weapon[i] = NULL;
			}
			isAlive = true;
			total_weapon = 0;
			name = "wolf";
			camp = (pos == 0? 0:1);
			current_position = pos;
			id = total_mob;
			hp = monster_hp[4];	
			ad = monster_ad[4];	
		}
		void printSpawn(string Headquarter_name, int type_amount){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << Headquarter_name << " wolf " << id << " born" << endl;		 
		}
		void printYell(){};
		void stealWeapon(monster * a){
			int weaponID = a->minWeaponId();
			int weaponSteal = 0;
			if(weaponID == 3){
				return;
			}
			sortWeapon();
			while(true){
				a->sortWeapon2();
				if(a->weapon[0] == NULL || a->weapon[0]->id != weaponID)
					break;
				weapon[total_weapon] = a->weapon[0];
				a->weapon[0] = NULL;
				a->total_weapon--;
				weaponSteal++;
				total_weapon++;
				if(weapon[total_weapon-1] == NULL || total_weapon == 10)
					break;
			}
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " wolf " << id << " took " << weaponSteal;
			cout << " " << weapon_list[weaponID] << " from" << (camp==0?" blue ":" red ");
			a->printNameAndID(); 
			cout << " in city " << current_position << endl;			
		}	
		void moveForward(int camp){
			if(camp)
				current_position--;
			else
				current_position++;
			if(camp == 0){
				if(current_position == n+1){
					blueTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " wolf " << id << " reached blue headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return;
				}
			}

			else{
				if(current_position == 0){
					redTaken = true;
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << (camp==0?" red":" blue") << " wolf " << id << " reached red headquarter";
					cout << " with " << hp << " elements and force " << ad << endl;
					return; 					
				}			
			}
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << (camp==0?" red":" blue") << " wolf " << id << " marched to city " << current_position;
			cout << " with " << hp << " elements and force " << ad << endl; 	
		}
		void attackEnemy(monster* a){
			if (!isAlive)
				return;
			if(total_weapon > 0){
				a->hurted(weapon[current_weapon]->damage(ad));
				if (weapon[current_weapon]->id == 1){
					this->hurted(weapon[current_weapon]->damage(ad)/2);					
				}

				if(weapon[current_weapon]->broken()){
					weapon[current_weapon] = NULL;
					total_weapon--;
				}
				current_weapon++;
				if(current_weapon == 10)
					current_weapon = 0;
				while(weapon[current_weapon] == NULL){
					if(total_weapon == 0)
						break;
					current_weapon++;
					if(current_weapon == 10)
						current_weapon = 0;
				}
			}
		}		
};

class Headquarter:public City{
	public:
		string name;
		int gem;
		int monster_order[5];
		int each_monster_amount[5];
		int total_monster_amount;
		int current_monster_type;
		monster* monster_team[5000];
		bool flag;
		void scanHp(){
			for (int i = 0; i < total_monster_amount; i++){
				if(monster_team[i] == NULL)
					continue;
				if(monster_team[i]->hp <= 0){
					monster_team[i] = NULL;
				}
				
			}
		}
		void scanRedPos(){
			for (int i = 0; i < total_monster_amount; i++){
				if(monster_team[i] == NULL)
					continue;
				city[monster_team[i]->current_position].red = monster_team[i];
			}
		}
		void scanBluePos(){
			for (int i = 0; i < total_monster_amount; i++){
				if(monster_team[i] == NULL)
					continue;
				city[monster_team[i]->current_position].blue = monster_team[i];
			}
		} 		 
		void printGem(){
			cout << setw(3) << setfill('0') << t/60 << ":"; 
			cout << setw(2) << setfill('0') << t%60;
			cout << " " << gem << " elements in " << name << " headquarter" << endl;			
		}
		void setRed(int m){
			id = 0;
			name = "red";
			memcpy(monster_order,monster_red_order,sizeof(monster_order));
			memset(each_monster_amount,0,sizeof(each_monster_amount));
			total_monster_amount = 0;
			current_monster_type = 0;
			gem = m;
			flag = false;
		}
		void setBlue(int m){
			id = n + 1;
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
			if (gem < monster_hp[monster_order[current_monster_type]]){
				flag = true;
				return;
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
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem,id);
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
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem,id);
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
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem,id);
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
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem,id);
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
					monster_team[total_monster_amount-1]->spawnMob(total_monster_amount,gem,id);
					monster_team[total_monster_amount-1]->printSpawn(name,each_monster_amount[4]);
					break;																	
			}
			if(name == "red")
				red = monster_team[total_monster_amount-1];
			else
				blue = monster_team[total_monster_amount-1];
		}
		void checkEscape(){
			for (int i = 0; i < total_monster_amount; i++){
				if(monster_team[i] == NULL)
					continue;
				if(monster_team[i]->name == "lion" && monster_team[i]->loyalty <= 0){
					monster_team[i]->printEscape();
					monster_team[i] = NULL;
				}
			}
		}
};

int main(){
	int z;
	cin >> z;
	for (int i = 0; i < z; i++){
		cout << "Case " << i+1 << ":" << endl;
		Headquarter red,blue;
		blueTaken = false;
		redTaken = false;
		int m;
		int T;
		cin >> m >> n >> lion_decrease >> T;
		for (int j = 1; j <= n; j++){
			city[j].setInfo(j);
		}
		for (int j = 0; j < 5; j++){
			cin >> monster_hp[j];
		}
		for (int j = 0; j < 5; j++){
			cin >> monster_ad[j];
		}		
		red.setRed(m);
		blue.setBlue(m);
		t = 0;
		while (true){
			//cout << t << endl;
			if (t > T)
				break;			
			red.scanHp();
			blue.scanHp();
			for (int j = 1; j <= n; j++){
				city[j].scanRedBlue();
			}

			if (t % 60 == 0){
				red.spawnMonster();
				blue.spawnMonster();
			}
			if (t % 60 == 5){
				red.checkEscape();
				blue.checkEscape();
			}
			if (t % 60 == 10){
				if(city[1].blue!= NULL){
					city[1].blue_march();
					cout << setw(3) << setfill('0') << t/60 << ":"; 
					cout << setw(2) << setfill('0') << t%60;
					cout << " red headquarter was taken" << endl;
					city[1].blue = NULL;
				}
				if(red.red!= NULL){
					red.red_march();
					red.red = NULL;
				}
				for(int j = 1; j <= n; j++){
					if(j+1 <= n && city[j+1].blue != NULL){
						city[j+1].blue_march();
						city[j+1].blue = NULL; 
					}
					if(j == n && blue.blue!= NULL){
						blue.blue_march();
						blue.blue = NULL;
					}					
					if(city[j].red != NULL){
						city[j].red_march();
						city[j].red = NULL; 
						if(j == n){
							cout << setw(3) << setfill('0') << t/60 << ":"; 
							cout << setw(2) << setfill('0') << t%60;
							cout << " blue headquarter was taken" << endl;	
						}
					}
				}

				red.scanRedPos();								
				blue.scanBluePos();
			}
			if (t % 60 == 35){
				for (int j = 1; j <= n; j++ ){
					if (city[j].red != NULL && city[j].blue!= NULL && !(city[j].red->name == "wolf" && city[j].blue->name == "wolf")){
						if (city[j].red->name == "wolf"){
							city[j].red->stealWeapon(city[j].blue);
						}
						else if (city[j].blue->name == "wolf"){
							city[j].blue->stealWeapon(city[j].red);
						}
					}
				}
			}
			if (t % 60 == 40){
				for (int j = 1; j <= n; j++){
					if (city[j].red != NULL && city[j].blue!= NULL){
						city[j].red->sortWeapon();
						city[j].blue->sortWeapon();
						int hp_of_red = city[j].red->hp;
						int hp_of_blue = city[j].blue->hp;
						int flag = 0;
						while(city[j].red->isAlive && city[j].blue->isAlive){
							//cout << j << " " << city[j].blue->hp << " " << city[j].red->hp << endl;
							//cout << j << " " << city[j].blue->total_weapon << " " << city[j].red->total_weapon << endl;
							if(j% 2 == 0){
								city[j].blue->attackEnemy(city[j].red);
								city[j].red->attackEnemy(city[j].blue);
							}
							else{
								city[j].red->attackEnemy(city[j].blue);
								city[j].blue->attackEnemy(city[j].red);
							}
							if(hp_of_red == city[j].red->hp && hp_of_blue == city[j].blue->hp )
								flag++;
							if(city[j].red->isAlive && !city[j].blue->isAlive){
								cout << setw(3) << setfill('0') << t/60 << ":"; 
								cout << setw(2) << setfill('0') << t%60;
								cout << " red ";
								city[j].red->printNameAndID();
								cout << " killed blue ";
								city[j].blue->printNameAndID();
								cout << " in city " << j << " remaining " << city[j].red->hp;
								cout << " elements" << endl;
								if (city[j].red->name == "dragon")
									city[j].red->printYell();
								city[j].red->takeWeapon(city[j].blue);
								break;
							}
							else if(!city[j].red->isAlive && city[j].blue->isAlive){
								cout << setw(3) << setfill('0') << t/60 << ":"; 
								cout << setw(2) << setfill('0') << t%60;
								cout << " blue ";
								city[j].blue->printNameAndID();
								cout << " killed red ";
								city[j].red->printNameAndID();
								cout << " in city " << j << " remaining " << city[j].blue->hp;
								cout << " elements" << endl;
								if (city[j].blue->name == "dragon")
									city[j].blue->printYell();
								city[j].blue->takeWeapon(city[j].red);
								break;
							}
							else if(!city[j].red->isAlive && !city[j].blue->isAlive){
								cout << setw(3) << setfill('0') << t/60 << ":"; 
								cout << setw(2) << setfill('0') << t%60;
								cout << " both red ";
								city[j].red->printNameAndID();
								cout << " and blue ";
								city[j].blue->printNameAndID();
								cout << " died in city " << j << endl;
								break;
							}
							else if(flag == 10 ||(city[j].red->total_weapon <= 0 && city[j].blue->total_weapon <= 0)){
								cout << setw(3) << setfill('0') << t/60 << ":"; 
								cout << setw(2) << setfill('0') << t%60;
								cout << " both red ";
								city[j].red->printNameAndID();
								cout << " and blue ";
								city[j].blue->printNameAndID();
								cout << " were alive in city " << j << endl;
								if (city[j].red->name == "dragon")
									city[j].red->printYell();
								if (city[j].blue->name == "dragon")
									city[j].blue->printYell();	
								break;
							}
						}
					}	
				}
			}
			if (t % 60 == 50){
				red.printGem();
				blue.printGem();
			}
			if (t % 60 == 55){
				if(red.red!= NULL){
					red.red->printStat();
				}
				for(int j = 1; j <= n; j++){
					if(city[j].red != NULL){
						city[j].red->printStat();
					}
					if(city[j].blue != NULL){
						city[j].blue->printStat();
					}
				}
				if(blue.blue!= NULL){
					blue.blue->printStat();
				}				
			}
			if (redTaken || blueTaken)
				break;

			t+= 5;		
		}
	}
}


