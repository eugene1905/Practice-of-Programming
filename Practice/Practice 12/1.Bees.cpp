#include <iostream>
using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int a,b;
        cin >> a >> b;
        long long dp[100] = {};
        dp[a] = 1,dp[a+1] = 1;
        for(int i = a + 2; i <= b; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        cout << dp[b] << endl;
    }
}