#include <iostream>
#include <cmath>
using namespace std;
int a,b,i,j;
void solve(){
    int t = ((1 << (j + 1))-1) -((1 << i) - 1);
    b = ~b & t;
    a &= ~t;
    a |= b;
    return;
}
int main(){
    cin >> a >> b >> i >> j;
    solve();
    cout << a << endl;
}

