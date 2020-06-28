#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
char a[105][105];
int visit[105][105][12]={};
struct Node{
    int x,y,s;
    Node(int x,int y,int s=0):x(x),y(y),s(s){}
};
queue <Node> q;
int main(){
    int t;
    cin >> t;
    while(t--){
        while(!q.empty())q.pop();
        int R,C,K,res=-1,sx,sy,ex,ey;
        memset(visit,0,sizeof(visit));
        cin>>R>>C>>K;
        for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                cin >> a[i][j];
                if(a[i][j]=='S'){
                    sx=i,sy=j;
                }
                else if(a[i][j]=='E'){
                    ex=i,ey=j;
                }
            }
        }
        q.push(Node(sx,sy,0));
        visit[sx][sy][0]=1;
        while(!q.empty()){
            Node nx = q.front();
            q.pop();
            if(nx.x==ex&&nx.y==ey){
                res=nx.s;
                break;
            }  
            for(int i=0;i<4;i++){
                int x=nx.x+dx[i],y=nx.y+dy[i],s=nx.s+1,mods=s%K;
                if(a[x][y]=='#'&&mods!=0)continue;
                if(x<1||x>R||y<1||y>C)continue;
                if(visit[x][y][mods])continue;
                visit[x][y][mods]=1;                   
                q.push(Node(x,y,s));
            }
        }
        if(res==-1)cout<<"Oop!"<<endl;
        else cout << res << endl;
    }
    
}