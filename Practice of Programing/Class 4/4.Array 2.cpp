#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
	private:
		int ** p;
		int row;
		int column;

	public:
		Array2(){}
		Array2 (int m, int n){
			row = m;
			column = n;
			p = new int*[m];
			for(int i = 0; i < m; i++){
				p[i] = new int[n];
			}
		}
		Array2& operator=(const Array2&a){
			row = a.row, column = a.column;
			p = new int*[a.row];
			for(int i = 0; i < a.row; i++){
				p[i] = new int[a.column];
			}
			for (int i = 0; i < row; i++){
				for (int j = 0; j < column; j++){
					p[i][j] = a.p[i][j];
				}
			}
			return *this;
		}
		int* operator[](int i){		
			return p[i];
		}
		int& operator()(int i,int j){
			return p[i][j];
		} 
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
