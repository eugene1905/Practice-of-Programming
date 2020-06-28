#include <iostream>
#include <cmath>
using namespace std;
int solve(int s, int a){
    int res = 1;
    for(int i = s; i * i <= a; i++){
        if(a % i == 0){
            res += solve(i, a/i);
        }
    }
    return res;
}
int main(){
    int n;
    cin >> n;
    while(n--){
        int a;
        cin >> a;
        cout << solve(2,a) << endl;
    }
}