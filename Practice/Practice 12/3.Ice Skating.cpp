#include <iostream>
#include <cstring>
using namespace std;
int board[105][105]={},visited[105][105]={};
int dx[]={1,1,1,0,0,-1,-1,-1},dy[]={1,-1,0,1,-1,1,-1,0};
void spread(int x,int y){
    if(!board[x][y])return;
    visited[x][y] = 1;
    for(int i=0;i<8;i++){
        int x1=x+dx[i],y1=y+dy[i];
        if(!visited[x1][y1])spread(x1,y1); 
    }
}
int main(){
    int n,m;
    while(cin>>n>>m,n+m!=0){
        int res=0;
        memset(board,0,sizeof(board)),memset(visited,0,sizeof(visited));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char s;
                cin >> s;
                if(s == '@')board[i][j]=1;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(board[i][j]&&!visited[i][j]){
                    spread(i,j);
                    res++;
                }
            }
        }
        cout << res << endl;
    }
}
