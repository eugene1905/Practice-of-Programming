#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int keys[10005],room[101][101],visited[101][101];
int dx[4] = {1,0,-1,0},dy[4] = {0,-1,0,1};
struct Node{
    int x,y,k,s;
    Node(int x,int y,int k,int s):x(x),y(y),k(k),s(s){}
};

int main(){
    int t;
    cin >> t;
    while(t--){
        queue <Node> q;
        int row,col,kt = 0;
        cin >> row >> col;
        memset(visited,0xff,sizeof(visited));
        for(int i = 1; i <= row; i++){
            for(int j = 1; j <= col; j++){
                cin >> room[i][j];
                if(room[i][j] > 1)
                    keys[kt++] = room[i][j];
            }
        }
        sort(keys,keys+kt);
        if(room[1][1] == keys[0])q.push(Node(1,1,1,0));
        else q.push(Node(1,1,0,0));
        int res = -1;
        while(!q.empty()){
            Node c = q.front();
            q.pop();
            if(c.k == kt){
                res = c.s;
                break;
            }
            for(int i = 0; i < 4; i++){
                int x = c.x + dx[i], y = c.y + dy[i], k = c.k;
                if(x >= 1 && x <= row && y >= 1 && y <= col){
                    if(room[x][y] != 0 && c.k > visited[x][y]){
                        if(keys[k] == room[x][y])
                            k++;
                        visited[x][y] = k;
                        q.push(Node(x,y,k,c.s+1));
                    }
                }
            }
        }
        cout << res << endl;
    }
}