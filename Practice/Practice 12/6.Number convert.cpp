#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
int dis[100000][5][5] = {0};
void num2array(int x, int *a){
    for (int i = 0; i < 5; i ++){
        a[i] = x%10;
        x /= 10;
    }
}
int array2num(int *a){
    int x = 0;
    for (int i = 4; i >= 0; i --){
        x = x*10 + a[i];
    }
    return x;
}
struct node{
    int num;
    int n2, n3, t;
    node(int _n, int _n2, int _n3, int _t){
        num = _n;
        n2 = _n2;
        n3 = _n3;
        t = _t;
    }
    node(){

    }
};
void prepare(){
    memset(dis, -1, sizeof(dis));
    dis[12345][0][0] = 0;
    queue<node> q;
    q.push(node(12345, 0, 0, 0));
    while (!q.empty()){
        node tmp = q.front();
        q.pop();
        int a[5] = {0};
        int n2 = tmp.n2;
        int n3 = tmp.n3;
        for (int i = 0; i < 4; i ++){
            num2array(tmp.num, a);
            swap(a[i], a[i+1]);
            int b = array2num(a);
            if (dis[b][n2][n3] == -1){
                dis[b][n2][n3] = tmp.t + 1;
                q.push(node(b, n2, n3, tmp.t+1));
            }
        }
        if (n2 < 3)
        for (int i = 0; i < 5; i ++){
            num2array(tmp.num, a);
            a[i] = (a[i]+1)%10;
            int b = array2num(a);
            if (dis[b][n2+1][n3] == -1){
                dis[b][n2+1][n3] = tmp.t + 1;
                q.push(node(b, n2+1, n3, tmp.t+1));
            }
        }
        if (n3 < 2)
        for (int i = 0; i < 5; i ++){
            num2array(tmp.num, a);
            a[i] = (a[i]*2)%10;
            int b = array2num(a);
            if (dis[b][n2][n3+1] == -1){
                dis[b][n2][n3+1] = tmp.t + 1;
                q.push(node(b, n2, n3+1, tmp.t+1));
            }
        }
    }
}

int main(){
    prepare();
    int n;
    while (cin >> n){
        int ans = 1e+9;
        for (int i = 0; i <= 3; i ++)
        for (int j = 0; j <= 2; j ++)
        {
            if (dis[n][i][j] != -1){
                ans = min(ans, dis[n][i][j]);
            }
        }
        if (ans != 1e+9)
        printf("%d\n", ans);
        else 
        printf("-1\n");
    }
    return 0;
}