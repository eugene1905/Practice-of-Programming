#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int main(){
    int n;
    cin >> n;
    int h[1005],p[1005],q[1005];
    memset(p,0,sizeof(p)),memset(q,0,sizeof(q));
    for(int i = 1; i <= n; i++){
        cin >> h[i];
        p[i] = 1, q[i] = 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            if(h[i] >= h[j]){
                p[j] = max(p[j],p[i] + 1);
            }
        }
    }
    for(int i = n; i >= 1; i--){
        for(int j = i - 1; j >= 1; j--){
            if(h[i] <= h[j]){
                q[j] = max(q[j],q[i] + 1);
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            res = max(res,p[i] + q[j]);
        }
    }
    cout << res << endl;
}   