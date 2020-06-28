#include <iostream>
#include <cstring>
using namespace std;
int solve(int n){
    int res = 0;
    if(n == 0)return 1;
    if(n == 1)return 0;
    if(n == 2)return 3;
    res = 3 * solve(n-2);
    for(int i = 4; i <= n; i+=2){
        res += 2*solve(n-i);
    }
    return res;
}
int main(){
    int n;
    while(cin >> n){
        if(n == -1)return 0;
        cout << solve(n) << endl;
    }
}