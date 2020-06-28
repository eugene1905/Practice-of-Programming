#include <algorithm>
#include <iostream>
using namespace std;
int hcf(int a, int b){
    int x = min(a,b);    
    int y = max(a,b);
    if(y % x == 0)return x;
    return hcf(y%x,x);
}
int main(){
    int a,b;
    cin >> a >> b;
    cout << hcf(a,b);
}