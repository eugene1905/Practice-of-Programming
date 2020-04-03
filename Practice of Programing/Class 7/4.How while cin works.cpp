#include <iostream>
using namespace std;
class MyCin
{
	private:
		bool flag = true;
	public:
		MyCin(){};
		MyCin& operator>>(int& a){
			cin >> a;
			if (a == -1){
				flag = false;
			}
			return *this;
		}
		operator bool(){
			return flag;
		}
		
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
