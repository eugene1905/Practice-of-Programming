#include <iostream>
#include <set>
using namespace std;
class Rectangle{
    public:
        int l;
        int w;
        int perimeter;
        int area;
        Rectangle(int a, int b):l(a),w(b){
            perimeter = 2 *(l + w);
            area = l * w;
        }
        bool operator<(const Rectangle& a)const{
            return(area == a.area?perimeter > a.perimeter:area > a.area);
        }
        friend ostream& operator<<(ostream& o,const Rectangle& a){
            o << a.area << " " << a.perimeter;
            return o;
        }
};

class Comp{
    public: 
        Comp(){}
        bool operator()(const Rectangle& a,const Rectangle& b)const{
            return(a.perimeter == b.perimeter?a.area < b.area:a.perimeter < b.perimeter);
        }
};
int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
	return 0;
}