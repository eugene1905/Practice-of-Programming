#include <iostream>
#include <algorithm>
#define inf 1<<30
using namespace std;
int main(){
    bool flag = false;
    int maxR[5] = {},minC[5] = {inf,inf,inf,inf,inf};
    int a[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> a[i][j];
            maxR[i] = max(maxR[i],a[i][j]);
            minC[j] = min(minC[j],a[i][j]);
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(a[i][j] == maxR[i] && a[i][j] == minC[j]){
                flag = true;
                cout << i + 1 << " " << j + 1 << " " << a[i][j] << endl;
                break;
            }
        }
    }
    if(!flag)cout << "not found" << endl;
}