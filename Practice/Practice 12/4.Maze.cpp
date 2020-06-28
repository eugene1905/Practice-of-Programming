#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
char board[300][300]={},visited[300][300]={};
int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
struct Node{
    int x,y,s,h;
    Node(int x, int y, int h, int s = 0):x(x),y(y),h(h),s(s){}
};
int main(){
    int t;
    cin >> t;
    while(t--){
        int m,n,h;
        cin>>m>>n>>h;
        memset(visited,0,sizeof(visited));
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                cin>>board[i][j];
            }
        }
        queue <Node> q;
        q.push(Node(1,1,h));
        visited[1][1] = 1<<30;
        while(!q.empty()){
            Node nx = q.front();
            q.pop();
            if(nx.h==0)continue;
            if(nx.x==m&&nx.y==n){
                cout<<nx.s<<endl;
                break;
            }
            for(int i=0;i<4;i++){
                int x=nx.x+dx[i],y=nx.y+dy[i];
                if(x>=1&&x<=m&&y>=1&&y<=n &&board[x][y]!='#'&&nx.h>visited[x][y]){                 
                    if(board[x][y]=='*'&&nx.h>1){
                        visited[x][y]=nx.h-1;
                        q.push(Node(x,y,nx.h-1,nx.s+1));
                    }
                    else if(board[x][y]=='.'){
                        visited[x][y]=nx.h;
                        q.push(Node(x,y,nx.h,nx.s+1));
                    }
                }
            }
        }
    }
}
