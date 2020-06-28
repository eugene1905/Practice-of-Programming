#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
// 在此处补充你的代码
    string s = "0000000000000000000000000000000";
    int y = 1<<30;
    for(int i = 0; i < 31; i++){
        if(x / y){
            x -= y;
            s[i] = '1';
        }
        y = y >> 1;
    }
    return s;
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}
