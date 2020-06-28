#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int dx[] = {1,-1,0,0}, dy[] = {0,0,-1,1};
struct Node{
    int x,y,s;
    Node(int x, int y, int s = 0):x(x),y(y),s(s){}
};
int main(){
    int n;
    cin >> n;
    while(n--){
        int m,t;
        bool flag = false;
        cin >> m >> t;
        char maze[15][15];
        int visited[15][15] = {};
        int sx,sy,ex,ey;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= m; j++){
                cin >> maze[i][j];
                if(maze[i][j] == 'S'){
                    sx = i, sy = j;
                }
                else if(maze[i][j] == 'E'){
                    ex = i, ey = j;
                }
            }
        }
        queue <Node> q;
        q.push(Node(sx,sy,0));
        while(!q.empty()){
            Node nx = q.front();
            q.pop();
            if(nx.s > t)continue;
            if(nx.x == ex && nx.y == ey){
                flag = true;
                break;
            }
            for(int i = 0; i < 4; i++){
                int x = nx.x + dx[i], y = nx.y + dy[i];
                if(x >= 1 && x <= m && y >= 1 && y <= m && maze[x][y] != '#' && !visited[x][y]){
                    visited[x][y] = 1;
                    q.push(Node(x,y,nx.s+1));
                }
            }
        }
        cout << (flag?"YES":"NO") << endl;
    }
}