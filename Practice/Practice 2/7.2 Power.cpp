#include <iostream>
#include <cmath>
using namespace std;
void solve(int a){
    bool flag = false;
    if(a == 0){
        cout << 0;
        return;
    }
    for(int i = 14; i >= 0; i--){
        int y = pow(2,i);
        if(a >= y){
            if(flag)cout << "+";
            if(i == 1)cout << 2;
            else{
                cout << "2(";
                solve(i);
                cout << ")";
            }   
            a -= y;
            if(a == 0)return;
            flag = true;
        }
    }
}
int main(){
    int a;
    cin >> a;
    solve(a);
}