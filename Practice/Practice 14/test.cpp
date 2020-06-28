#include<bits/stdc++.h>
using namespace std;
int dp[1005][2];
int n,a[1005];
int ans=0;
int main(){
	cin>>n;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++) cin>>a[i],dp[i][0]=dp[i][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++) 
            if(a[j]>=a[i]) 
                dp[i][0]=max(dp[i][0],dp[j][0]+1);
	}
	for(int i=n;i>=1;i--){
		for(int j=n;j>i;j--) 
            if(a[i]>=a[j]) 
                dp[i][1]=max(dp[i][1],dp[j][1]+1);
	} 
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n+1;j++)ans=max(ans,dp[i][0]+dp[j][1]);
	cout<<ans<<endl;
	return 0;
}
