#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int p[1030][3]; // x,y,v;
int street[1030][1030];
int main(){
    memset(street,0,sizeof(street));
    int num = 0, res = 0;
    int d,n;
    cin >> d >> n;
    int r = 2 * d + 1;
    for(int i = 0; i < n; i++){
        cin >> p[i][0] >> p[i][1] >> p[i][2];
        for(int j = 0; j < r; j++){
            for(int k = 0; k < r; k++){
                int x1 = p[i][0] - d + j;
                int y1 = p[i][1] - d + k;
                if(x1 < 0 || y1 < 0)continue;
                if(y1 > 1024 || y1 > 1024)break;
                street[x1][y1] += p[i][2];
                res = max(res,street[x1][y1]);
            }
        }
    }
    for(int i = 0; i < 1025; i++){
        for(int j = 0; j < 1025; j++){
            if(street[i][j] == res)num++;
        }
    }
    cout << num << " " << res << endl;
}