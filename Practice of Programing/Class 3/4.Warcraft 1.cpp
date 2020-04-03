#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
string samurai_name[5] = {"dragon","ninja","iceman","lion","wolf"};
int samurai_red_order[5]= {2,3,4,1,0};
int samurai_blue_order[5] = {3,0,1,2,4};
int samurai_hp[5];
int t = 0;

class city{
	private:
		string name;
		int gem;
		int samurai_order[5];
		int samurai_amount[5];
		int cur_samurai;
		int cur_id;
	public:
		bool flag;
		void setRed(int m)
		{
			name = "red";
			memcpy(samurai_order,samurai_red_order,sizeof(samurai_order));
			memset(samurai_amount,0,sizeof(samurai_amount));
			cur_samurai = 0;
			cur_id = 0;
			gem = m;
			flag = false;
		}
		void setBlue(int m)
		{
			name = "blue";
			memcpy(samurai_order,samurai_blue_order,sizeof(samurai_order));
			memset(samurai_amount,0,sizeof(samurai_amount));
			cur_samurai = 0;
			cur_id = 0;
			gem = m;
			flag = false;
		}
		void spawnSamurai()
		{
			for (int i = 0; i < 5; i++)
			{
				if (flag)break;
				if(i != 0)cur_samurai++;
				if(cur_samurai == 5)cur_samurai = 0;
				if(gem >= samurai_hp[samurai_order[cur_samurai]])
				{					
					cout << setw(3) << setfill('0') << t; 
					cout << " " << name << " " << samurai_name[samurai_order[cur_samurai]] << " " << cur_id + 1;
					cout << " born with strength " << samurai_hp[samurai_order[cur_samurai]] ;
					cout << "," << samurai_amount[samurai_order[cur_samurai]] + 1 << " " ;
					cout << samurai_name[samurai_order[cur_samurai]];
					cout << " in " << name << " headquarter" << endl;
					gem -= samurai_hp[samurai_order[cur_samurai]];
					samurai_amount[samurai_order[cur_samurai]]++;
					cur_samurai++;
					if(cur_samurai == 5)cur_samurai = 0;
					cur_id++;
					break;
				}
				if (i == 4)
				{
					cout << setw(3) << setfill('0') << t << " " << name << " headquarter stops making warriors" << endl;
					flag = true;
				}
			}

			
		}
};


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Case:" << i+1 << endl;
		city red,blue;
		int m;
		cin >> m;
		for (int i = 0; i < 5;i++)
		{
			cin >> samurai_hp[i];
		}
		red.setRed(m);
		blue.setBlue(m);
		
		t = 0;
		while(true)
		{
			if (red.flag && blue.flag)break;
			red.spawnSamurai();
			blue.spawnSamurai();
			t++;
		}
		
	}
}


