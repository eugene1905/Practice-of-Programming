#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int main(){
    int n,m;
    int p[105][2],dp[105][2];
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> p[i][0] >> p[i][1];
    }
    memset(dp,0,sizeof(dp));
    dp[1][0] = p[1][0],dp[1][1] = p[1][1];
    for(int i = 2; i <= n; i++){
        for(int j = 0; j < 2; j++){
            dp[i][j] = max(dp[i-1][j] + p[i][j],dp[i-1][!j] + p[i][j] - m);
        }
    }
    cout << max(dp[n][0],dp[n][1]) << endl;
}