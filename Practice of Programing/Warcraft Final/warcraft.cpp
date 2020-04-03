#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;
string monster_name[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int monster_red_order[5] = {2, 3, 4, 1, 0};
int monster_blue_order[5] = {3, 0, 1, 2, 4};
int monster_hp[5]; //Standard hp of dragon, ninja, iceman, lion, wolf
int monster_ad[5];
bool fightOccured[22];
string weapon_list[3] = {"sword", "bomb", "arrow"};
int lion_decrease = 0;
int arrow_damage = 0;
int t = 0;
int n = 0;
bool redTaken, blueTaken, redReach, blueReach;
void printTime()
{
	cout << setw(3) << setfill('0') << t / 60 << ":";
	cout << setw(2) << setfill('0') << t % 60 << " ";
}
class Weapon
{
public:
	int id;
	int damage;
	int durability;
};
class sword : public Weapon
{
public:
	sword(int ad)
	{
		damage = damage * 2 / 10;
		id = 0;
	}
};
class bomb : public Weapon
{
public:
	bomb()
	{
		id = 1;
		durability = 1;
	}
};
class arrow : public Weapon
{
public:
	arrow()
	{
		id = 2;
		durability = 3;
		damage = arrow_damage;
	}
};

class monster
{
public:
	bool isAlive;
	string name;
	string colour;
	string info;
	int id;
	int hp;
	int ad;
	int current_position;
	int camp;	// 0:red, 1:blue
	int morale;  // for dragon
	int loyalty; // for lion
	int step;	// for iceman
	int total_weapon;
	Weapon *Arrow;
	Weapon *Bomb;
	Weapon *Sword;

	virtual void spawnMob(int a, int b, int c) = 0;
	virtual void takeWeapon(monster *a) = 0;
	virtual void printEscape() = 0;
	virtual void printYell() = 0;
	void printSpawn()
	{
		printTime();
		cout << info << " born" << endl;
		if (name == "dragon")
			cout << fixed << setprecision(2) << "Its morale is " << morale << endl;
		if (name == "lion")
			cout << "Its loyalty is " << loyalty << endl;
	}
	void printWeaponStat()
	{
		printTime();
		cout << info << " has ";
		if (Arrow == NULL && Bomb == NULL && Sword == NULL)
			cout << "no weapon" << endl;
		else
		{
			if (Arrow != NULL)
				cout << "arrow(" << Arrow->durability << ")";
			if (Bomb != NULL)
			{
				if (Arrow != NULL)
					cout << ",";
				cout << "bomb";
			}
			if (Sword != NULL)
			{
				if (Bomb != NULL || Arrow != NULL)
					cout << ",";
				cout << "sword(" << Sword->damage << ")";
			}
			cout << endl;
		}
	}
	void spawnWeapon(int total_weapon, int weapon_id)
	{
		switch (weapon_id)
		{
		case 0:
			Sword = new sword(ad);
			break;
		case 1:
			Bomb = new bomb();
			break;
		case 2:
			Arrow = new arrow();
			break;
		}
	}
	void moveForward()
	{
		if (colour == "blue")
			current_position--;
		else
			current_position++;
		if (name == "iceman")
		{
			step++;
			if (step == 2)
			{
				hp -= 9;
				step = 0;
			}
			if (hp <= 0)
				hp = 1;
		}
		if (colour == "red")
		{
			if (current_position == n + 1)
			{
				if (blueReach)
					blueTaken = true;
				blueReach = true;
				printTime();
				cout << info << " reached blue headquarter";
				cout << " with " << hp << " elements and force " << ad << endl;
				if (blueTaken)
				{
					printTime();
					cout << "blue headquarter is taken" << endl;
				}
				return;
			}
		}

		else
		{
			if (current_position == 0)
			{
				if (redReach)
					redTaken = true;
				redReach = true;
				printTime();
				cout << info << " reached red headquarter";
				cout << " with " << hp << " elements and force " << ad << endl;
				if (redReach)
				{
					printTime();
					cout << "red headquarter is taken" << endl;
				}
				return;
			}
		}

		printTime();
		cout << info << " marched to city " << current_position;
		cout << " with " << hp << " elements and force " << ad << endl;
	}
	void attackArrow(monster *a)
	{
		a->hurted(Arrow->damage, 2);
		printTime();
		cout << info << " shot";
		if (!a->isAlive)
			cout << " and killed " << a->info;
		cout << endl;
		Arrow->durability--;
		if (Arrow->durability == 0)
			Arrow = NULL;
	}
	void attackBomb(monster *a)
	{
		hp = 0;
		isAlive = false;
		a->hp = 0;
		a->isAlive = false;
		Bomb->durability--;
		Bomb = NULL;
		printTime();
		cout << info << " used a bomb and killed " << a->info << endl;
	}
	void attackSword(monster *a)
	{
		if (!isAlive || !a->isAlive)
			return;
		fightOccured[current_position] = true;
		printTime();
		cout << info << " in city " << current_position << " attacked ";
		cout << a->info << " with ";
		cout << hp << " elements and force " << ad << endl;
		if (Sword != NULL)
		{
			a->hurted(ad + Sword->damage, 0);
			Sword->damage = Sword->damage * 8 / 10;
			if (Sword->damage == 0)
				Sword = NULL;
		}
		
		if (a->name != "ninja" && a->hp > 0)
		{
			a->fightBack(this);
		}
	}
	void fightBack(monster *a)
	{
		if (!isAlive)
			return;
		cout << info << " fought back against ";
		cout << a->info << " in city " << current_position << endl;
		if (Sword != NULL)
		{
			a->hurted(ad / 2 + Sword->damage, 0);
			Sword->damage = Sword->damage * 8 / 10;
			if (Sword->damage == 0)
				Sword = NULL;
		}
	}
	void hurted(int a, int weapon_type)
	{
		hp -= a;
		if (hp <= 0)
		{
			isAlive = false;
		}
	}
	bool simulateAttack(monster *a)
	{
		int myHP = hp;
		int theirHP = a->hp;
		if (Sword != NULL)
		{
			theirHP -= ad + Sword->damage;
		}
		if (theirHP > 0)
		{
			if (a->Sword != NULL)
			{
				myHP -= a->ad / 2 + a->Sword->damage;
			}
		}
		return myHP < 0;
	}
	bool simulateHurted(monster *a)
	{
		if (a->hp <= 0)
			return false;
		int myHP = hp;
		if (a->Sword != NULL)
		{
			myHP -= a->ad + a->Sword->damage;
		}
		return myHP < 0;
	}
	friend class Headquarter;
	friend class weapon;
};
class City
{
public:
	int id;
	string name;
	int flag; // 1:Blue, -1:Red, 0:None
	int gem;
	int redWon;
	int blueWon;
	monster *red;
	monster *blue;
	City() {}
	void setInfo(int a)
	{
		id = a;
		name = "city" + char('0' + a);
		blue = NULL;
		red = NULL;
		gem = 0;
		redWon = 0;
		blueWon = 0;
		flag = 0;
	}
	bool redAttackFirst()
	{ //if true then red attack first
		if (flag == -1)
			return true;
		else if (flag == 1)
			return false;
		else
			return id % 2 != 0;
	}
};
City city[22];
class dragon : public monster
{
public:
	void spawnMob(int total_mob, int gem, int pos)
	{
		isAlive = true;
		name = "dragon";
		colour = (!pos ? "red" : "blue");
		current_position = pos;
		id = total_mob;
		info = colour + " " + name + " " + char('0' + id);
		hp = monster_hp[0];
		ad = monster_ad[0];
		morale = double(gem) / double(monster_hp[0]);
		total_weapon = 0;
		spawnWeapon(0, id % 3);
		total_weapon++;
	}
	void printYell()
	{
		printTime();
		cout << info << " yelled in city " << current_position << endl;
	}
	void takeWeapon(monster *a){}
	void printEscape(){}
};
class ninja : public monster
{
public:
	void spawnMob(int total_mob, int gem, int pos)
	{
		isAlive = true;
		total_weapon = 0;
		name = "ninja";
		colour = (!pos ? "red" : "blue");
		current_position = pos;
		id = total_mob;
		info = colour + " " + name + " " + char('0' + id);
		hp = monster_hp[1];
		ad = monster_ad[1];
		spawnWeapon(0, id % 3);
		spawnWeapon(1, (id + 1) % 3);
		total_weapon += 2;
	}
	void takeWeapon(monster *a){};
	void printEscape(){};	
	void printYell(){};
};
class iceman : public monster
{
public:
	void stealWeapon(monster *a){};
	void spawnMob(int total_mob, int gem, int pos)
	{
		isAlive = true;
		name = "iceman";
		colour = (!pos ? "red" : "blue");
		current_position = pos;
		id = total_mob;
		info = colour + " " + name + " " + char('0' + id);
		hp = monster_hp[2];
		ad = monster_ad[2];
		step = 0;
		total_weapon = 0;
		spawnWeapon(0, id % 3);
		total_weapon++;
	}
	void printEscape(){}
	void takeWeapon(monster* a){}
	void printYell(){}
};
class lion : public monster
{
public:
	void spawnMob(int total_mob, int gem, int pos)
	{
		isAlive = true;
		name = "lion";
		colour = (!pos ? "red" : "blue");
		current_position = pos;
		id = total_mob;
		info = colour + " " + name + " " + char('0' + id);
		ad = monster_ad[3];
		hp = monster_hp[3];
		loyalty = gem;
		total_weapon = 0;
		spawnWeapon(total_weapon, id % 3);
		total_weapon++;
	}
	void printEscape()
	{
		printTime();
		cout << info << " ran away" << endl;
		hp = 0;
		isAlive = false;
	}
	void takeWeapon(monster* a){}
	void printYell(){}	
};
class wolf : public monster
{
public:
	void spawnMob(int total_mob, int gem, int pos)
	{
		isAlive = true;
		name = "wolf";
		colour = (!pos ? "red" : "blue");
		current_position = pos;
		id = total_mob;
		info = colour + " " + name + " " + char('0' + id);
		hp = monster_hp[4];
		ad = monster_ad[4];
		total_weapon = 0;
	}
	void takeWeapon(monster *a)
	{
		if (Sword == NULL && a->Sword != NULL)
		{
			Sword = a->Sword;
			a->Sword = NULL;
			total_weapon++;
		}
		if (Arrow == NULL && a->Arrow != NULL)
		{
			Arrow = a->Arrow;
			a->Arrow = NULL;
			total_weapon++;
		}
		if (Bomb == NULL && a->Bomb != NULL)
		{
			Bomb = a->Bomb;
			a->Bomb = NULL;
			total_weapon++;
		}
	}
	void printEscape(){};
	void printYell(){};	
};

class Headquarter : public City
{
public:
	int monster_order[5];
	int each_monster_amount[5];
	int total_monster_amount;
	int current_monster_type;
	monster *monster_team[5000];
	bool flag;
	void scanHp()
	{
		for (int i = 0; i < total_monster_amount; i++)
		{
			if (monster_team[i] == NULL)
				continue;
			if (monster_team[i]->hp <= 0)
			{
				monster_team[i] = NULL;
			}
		}
	}
	void scanPos()
	{
		for (int i = 0; i < total_monster_amount; i++)
		{
			if (monster_team[i] == NULL)
				continue;
			if (name == "red headquarter")
				city[monster_team[i]->current_position].red = monster_team[i];
			else if (name == "blue headquarter")
				city[monster_team[i]->current_position].blue = monster_team[i];
		}
	}
	void printGem()
	{
		printTime();
		cout << gem << " elements in " << name << endl;
	}
	void setRed(int m)
	{
		id = 0;
		name = "red headquarter";
		memcpy(monster_order, monster_red_order, sizeof(monster_order));
		memset(each_monster_amount, 0, sizeof(each_monster_amount));
		total_monster_amount = 0;
		current_monster_type = 0;
		gem = m;
	}
	void setBlue(int m)
	{
		id = n + 1;
		name = "blue headquarter";
		memcpy(monster_order, monster_blue_order, sizeof(monster_order));
		memset(each_monster_amount, 0, sizeof(each_monster_amount));
		total_monster_amount = 0;
		current_monster_type = 0;
		gem = m;
	}
	void spawnMonster()
	{
		if (gem < monster_hp[monster_order[current_monster_type]])
		{
			return;
		}
		else
		{
			gem -= monster_hp[current_monster_type];
			total_monster_amount++;
			current_monster_type++;
			if (current_monster_type == 5)
				current_monster_type = 0;
			switch (monster_order[current_monster_type])
			{
			case 0:
				monster_team[total_monster_amount] = new dragon();
				break;
			case 1:
				monster_team[total_monster_amount] = new ninja();
				break;
			case 2:
				monster_team[total_monster_amount] = new iceman();
				break;
			case 3:
				monster_team[total_monster_amount] = new lion();
				break;
			case 4:
				monster_team[total_monster_amount] = new wolf();
				break;
			}
			monster_team[total_monster_amount]->spawnMob(total_monster_amount, gem, id);
			monster_team[total_monster_amount]->printSpawn();
			if (name == "red headquarter")
				red = monster_team[total_monster_amount - 1];
			else if (name == "blue headquarter")
				blue = monster_team[total_monster_amount - 1];
		}
	}
	void checkEscape()
	{
		for (int i = 0; i < total_monster_amount; i++)
		{
			if (monster_team[i] == NULL)
				continue;
			if (monster_team[i]->name == "lion" && monster_team[i]->loyalty <= 0)
			{
				monster_team[i]->printEscape();
				monster_team[i] = NULL;
			}
		}
	}
};

int main()
{
	int total;
	cin >> total;
	for (int i = 0; i < total; i++)
	{
		cout << "Case " << i + 1 << ":" << endl;
		//***Initialization**********************************
		t = 0;
		Headquarter red, blue;
		blueReach = redReach = blueTaken = redTaken = false;
		int m, T;
		cin >> m >> n >> arrow_damage >> lion_decrease >> T;
		for (int j = 1; j <= n; j++)
			city[j].setInfo(j);
		red.setRed(m), blue.setBlue(m);
		for (int j = 0; j < 5; j++)
			cin >> monster_hp[j];
		for (int j = 0; j < 5; j++)
			cin >> monster_ad[j];

		//****************************************************

		while (t < T)
		{
			//cout << t << endl;
			if(redTaken || blueTaken)
				break;
			int remain = t % 60;
			if(remain == 41){
				red.scanHp(), blue.scanHp();
			}
			red.scanPos(), blue.scanPos();
			if(remain == 41)
			//***Events***************************************
			if (remain == 0)
			{
				red.spawnMonster();
				blue.spawnMonster();
			}
			else if (remain == 5)
			{
				red.checkEscape();
				blue.checkEscape();
			}
			else if (remain == 10)
			{
				if(red.red != NULL)
					red.red->moveForward();
				for (int j = 1; j <= n; j++)
				{
					if (city[j].red != NULL)
						city[j].red->moveForward();
					if (city[j].blue != NULL)
						city[j].blue->moveForward();
				}
				if(blue.blue != NULL)
					blue.blue->moveForward();
			}
			else if (remain == 20)
			{
				for (int j = 1; j <= n; j++)
				{
					city[j].gem += 10;
				}
			}
			else if (remain == 30)
			{
				for (int j = 1; j <= n; j++)
				{
					if (city[j].red == NULL && city[j].blue == NULL)
						continue;
					if (city[j].blue == NULL)
					{
						red.gem += city[j].gem;
						city[j].gem = 0;
					}
					else if (city[j].red == NULL)
					{
						blue.gem += city[j].gem;
						city[j].gem = 0;
					}
				}
			}
			else if (remain == 35)
			{
				if (red.red->Arrow != NULL && city[1].blue != NULL)
					red.red->attackArrow(city[1].blue);
				for (int j = 1; j <= n; j++)
				{
					if (city[j].red->Arrow != NULL && city[j + 1].blue != NULL)
					{
						city[j].red->attackArrow(city[j + 1].blue);
					}
					if (city[j].blue->Arrow != NULL && city[j - 1].red != NULL)
					{
						city[j].blue->attackArrow(city[j - 1].red);
					}
				}
				if (blue.blue->Arrow != NULL && city[n].red != NULL)
					blue.blue->attackArrow(city[n].red);
			}
			else if (remain == 38)
			{
				for (int j = 1; j <= n; j++)
				{
					if (city[j].blue != NULL && city[j].red != NULL)
					{
						if (city[j].red->Bomb != NULL)
						{
							if (city[j].redAttackFirst())
							{
								if (city[j].red->simulateAttack(city[j].blue))
								{
									city[j].red->attackBomb(city[j].blue);
									city[j].red = city[j].blue = NULL;
								}
							}
							else
							{
								if (city[j].red->simulateHurted(city[j].blue))
								{
									city[j].red->attackBomb(city[j].blue);
									city[j].red = city[j].blue = NULL;
								}
							}
						}
						if (city[j].blue->Bomb != NULL)
						{
							if (city[j].redAttackFirst())
							{
								if (city[j].blue->simulateHurted(city[j].red))
								{
									city[j].blue->attackBomb(city[j].red);
									city[j].red = city[j].blue = NULL;
								}
							}
							else
							{
								if (city[j].blue->simulateAttack(city[j].red))
								{
									city[j].blue->attackBomb(city[j].red);
									city[j].red = city[j].blue = NULL;
								}
							}
						}
					}
				}
			}
			else if (remain == 40)
			{
				int redClaim = 0;
				int blueClaim = 0;
				for (int j = 1; j <= n; j++)
				{
					if (city[j].blue != NULL && city[j].red != NULL)
					{
						fightOccured[j] = false;
						int redHP = city[j].red->hp;
						int blueHP = city[j].blue->hp;
						if (city[j].redAttackFirst())
						{
							city[j].red->attackSword(city[j].blue);
						}
						else
						{
							city[j].blue->attackSword(city[j].red);
						}
						if (fightOccured[j])
						{
							if (!city[j].red->isAlive)
							{
								if(city[j].blue->name == "dragon"){
									city[j].blue->morale += 0.2;
								}
								if(blue.gem >= 8){
									blue.gem-=8;
									city[j].blue->hp+=8;
								}
								else{
									city[j].blue+=blue.gem;
									blue.gem = 0;
								}
								printTime();
								cout << city[j].red->info << " was killed in city " << j << endl;
							}
							else
							{
								if(city[j].blue->name == "dragon"){
									city[j].blue->morale -= 0.2;
								}
								if(city[j].blue->name == "lion"){
									city[j].blue->morale -= lion_decrease;
								}
								city[j].redWon++;
								city[j].blueWon = 0;
								if (city[j].red->name == "dragon" && city[j].redAttackFirst() && city[j].red->morale > 0.8)
								{
									city[j].red->printYell();
								}
							}
							if (!city[j].blue->isAlive)
							{
								if(city[j].red->name == "dragon"){
									city[j].red->morale += 0.2;
								}
								if(red.gem >= 8){
									red.gem-=8;
									city[j].red->hp+=8;
								}
								else{
									city[j].red+=red.gem;
									red.gem = 0;
								}
								printTime();
								cout << city[j].blue->info << " was killed in city " << j << endl;
							}
							else
							{
								if(city[j].red->name == "dragon"){
									city[j].red->morale -= 0.2;
								}
								if(city[j].red->name == "lion"){
									city[j].red->morale -= lion_decrease;
								}
								city[j].redWon = 0;
								city[j].blueWon++;
								if (city[j].blue->name == "dragon" && !city[j].redAttackFirst() && city[j].blue->morale > 0.8)
								{
									city[j].blue->printYell();
								}
								else if (city[j].blue->name == "wolf")
								{
									city[j].blue->takeWeapon(city[j].red);
								}
							}
						}
						if (city[j].red->isAlive && !city[j].blue->isAlive)
						{
							printTime();
							cout << city[j].red->info << " earned " << city[j].gem << " for his headquarter " << endl;
							redClaim += city[j].gem;
							city[j].gem = 0;
							if (city[j].red->name == "wolf")
							{
								city[j].red->takeWeapon(city[j].blue);
							}
							if(city[j].redWon == 2 && city[j].flag != -1){
								city[j].flag = -1;
								printTime();
								cout << "red flag raised in city " << j << endl;
							}
						}
						else if (city[j].blue->isAlive && !city[j].red->isAlive)
						{
							printTime();
							cout << city[j].blue->info << " earned " << city[j].gem << " for his headquarter " << endl;
							blueClaim += city[j].gem;
							city[j].gem = 0;
							if (city[j].blue->name == "wolf")
							{
								city[j].blue->takeWeapon(city[j].red);
							}
							if(city[j].blueWon == 2 && city[j].flag != 1){
								city[j].flag = 1;
								printTime();
								cout << "blue flag raised in city " << j << endl;
							}
						}
						red.gem+=redClaim;
						blue.gem+=blueClaim;
					}
				}
			}
			else if (remain == 50)
			{
				red.printGem();
				blue.printGem();
			}
			if (remain == 55)
			{
				if(red.red != NULL)
					red.red->printWeaponStat();
				if(red.blue != NULL)
					red.blue->printWeaponStat();
				for (int j = 0; j <= n+1; j++)
				{
					if(city[j].red != NULL)
					{
						city[j].red->printWeaponStat();
					}
					if(city[j].blue != NULL)
					{
						city[j].blue->printWeaponStat();
					}
				}
				if(blue.red != NULL)
					blue.red->printWeaponStat();
				if(blue.blue != NULL)
					blue.blue->printWeaponStat();
			}
			t++;
		}
	}
}
