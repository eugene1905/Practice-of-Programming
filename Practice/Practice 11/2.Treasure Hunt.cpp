#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
struct Node{
    int x,y,t;
    int k[105]={};
    Node(int x,int y,int t=0):x(x),y(y),t(t){}
};
queue <Node> q;
int main(){
    int M,N,K,res=1;
    cin>>M>>N>>K;
    int a[25][25]={};
    for(int i=1;i<=M;i++){
        for(int j=1;j<=N;j++){
            cin >> a[i][j];
        }
    }
    Node tmp1(1,1,1);
    tmp1.k[a[1][1]]=1;
    q.push(tmp1);
    while(!q.empty()){
        Node nx = q.front();
        res = max(res,nx.t);
        q.pop();
        for(int i=0;i<4;i++){
            int x=nx.x+dx[i],y=nx.y+dy[i];
            if(x>=1&&x<=M&&y>=1&&y<=N&&!nx.k[a[x][y]]){
                Node tmp = nx;
                tmp.x=x,tmp.y=y,tmp.t++;
                tmp.k[a[x][y]]=1;
                q.push(tmp);
            }
        }
    }
    cout<<res<<endl;
}