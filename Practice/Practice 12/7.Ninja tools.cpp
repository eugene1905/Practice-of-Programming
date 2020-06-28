#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int w[25]={},packs[25]={},N,W,res=1<<30;
void dfs(int d,int cnt){
    if(d==N){
        res=min(res,cnt+1);
        return;
    }
    if(cnt+1>=res)return;
    for(int i=0;i<=cnt;i++){
        if(packs[i]>=w[d]){
            packs[i]-=w[d];
            dfs(d+1,cnt);
            packs[i]+=w[d];
        }
    }
    packs[cnt+1]=W-w[d];
    dfs(d+1,cnt+1);
}
int main(){
    cin >> N >> W;
    for(int i=0;i<N;i++)
        scanf("%d",&w[i]);
    sort(w,w+N,greater<int>());
    packs[0]=W-w[0];
    dfs(1,0);
    cout << res << endl;
}
