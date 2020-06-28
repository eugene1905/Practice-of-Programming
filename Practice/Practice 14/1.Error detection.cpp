#include <iostream>
#include <cstring>
using namespace std;
int main(){
    int n;
    while(cin >> n){
        int a[105][105],r[105],c[105];
        memset(a,0,sizeof(a)),memset(r,0,sizeof(r)),memset(c,0,sizeof(c));
        bool flag = false;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> a[i][j];
                if(a[i][j]){
                    r[i]++,c[j]++;
                }
            }
        } 
        int x = 0,y = 0;
        for(int i = 1; i <= n; i++){
            if(r[i] % 2 != 0){
                if(x != 0){
                    flag = true;
                    break;
                }
                x = i;
            }
            if(c[i] % 2 != 0){
                if(y != 0){
                    flag = true;
                    break;
                }
                y = i;
            }
        }
        if(x == 0 && y != 0)flag = true;
        if(y == 0 && x != 0)flag = true;
        if(flag)cout << "Corrupt" << endl;
        else if(x == 0 && y == 0)cout << "OK" << endl;
        else cout << x << " " << y << endl;
    }
}