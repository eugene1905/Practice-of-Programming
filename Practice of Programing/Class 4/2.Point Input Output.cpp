#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
	friend istream & operator>>(istream & i, Point& a){
		i >> a.x >> a.y;
		return i;
	}
	friend ostream & operator<<(ostream & o, const Point& a){
		o << a.x << "," << a.y;
		return o;
	}	
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}
