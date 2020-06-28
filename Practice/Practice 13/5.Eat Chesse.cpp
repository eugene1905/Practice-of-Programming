#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
long long dp[100005],a[100005];
int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        memset(dp,0,sizeof(dp));
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        dp[1]=max(a[1],(long long)0);
        for(int i=2;i<=n;i++){
            dp[i]=max(dp[i-1],dp[i-2]+a[i]);
        }
        cout << dp[n] << endl;
    }
}