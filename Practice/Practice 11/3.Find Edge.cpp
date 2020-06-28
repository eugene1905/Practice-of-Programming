#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
int r,c;
char a[505][505];
int visit[505][505];
void spread(int x,int y){
    visit[x][y]=1;
    for(int i=0;i<4;i++){
        int x1=x+dx[i],y1=y+dy[i];
        if(x1<1||x1>r||y1<1||y1>c)continue;
        if(visit[x1][y1])continue;
        if(a[x1][y1]!='O')continue;
        spread(x1,y1);
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        cin>>r>>c;
        memset(visit,0,sizeof(visit));
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                cin>>a[i][j];
            }
        }
        for(int i=1;i<=r;i++){
            if(!visit[i][1]&&a[i][1]=='O')
                spread(i,0);
            if(!visit[i][c]&&a[i][c]=='O')
                spread(i,c);
        }
        for(int i=1;i<=c;i++){
            if(!visit[1][i]&&a[1][i]=='O')
                spread(0,i);
            if(!visit[r][i]&&a[r][i]=='O')
                spread(r,i);
        }
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                if(a[i][j]=='O'&&!visit[i][j])cout<<"X";
                else cout << a[i][j];
            }
            cout << endl;
        }
        cout<<endl;
    }
}