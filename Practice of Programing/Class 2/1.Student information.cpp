#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
	private:
		char name[20] = {' '};
		int result[4] = {0};
		int age = 0;
		int id = 0;
		double average = 0;
	public:
		void input()
		{
			char tmp;
			int i = 0;
			while(true)
			{
				cin.get(tmp);
				if (tmp == ',')break;
				name[i] = tmp;
				i++;
			}
			cin >> age >> tmp >> id >> tmp >> result[0] >> tmp >> result[1] >> tmp >> result[2] >> tmp >> result[3];
		}
		int sum()
		{
			return result[0] + result[1] + result[2] + result[3];
		}
		void calculate()
		{
			average = sum() / 4.0;
		}
		void output()
		{
			cout << name << "," << age << "," << id << "," << average << endl;
		}
		
};

int main() {
	Student student;        
	student.input();        
	student.calculate();    
	student.output();       
}
