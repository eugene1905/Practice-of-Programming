#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType{
public:
    int v1;
    int v2;
    CType(){}
    void setvalue(int n){
        v1 = n;
        v2 = n * n;
    }
    int operator++(int){
        return v1;
    }
    operator int(){
        return v2;
    }
};
int main(int argc, char* argv[]) {
	CType obj;
	int   n;		
	cin>>n;
	while ( n ) {
		obj.setvalue(n);
		cout<<obj++<<" "<<obj<<endl;
		cin>>n;
	}
	return 0;
}