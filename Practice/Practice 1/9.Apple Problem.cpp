#include <iostream>
using namespace std;
int solve(int m, int n){
    if(m < 0)return 0;
    if(m == 1 || n == 1)return 1;
    return solve(m,n-1) + solve(m-n,n);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int m,n;
        cin >> m >> n;
        cout << solve(m,n) << endl;
    }
}