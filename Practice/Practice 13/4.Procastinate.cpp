#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
    int S, w[15], s[15];
    cin >> S;
    for(int i = 0; i < 15; i++){
        cin >> w[i] >> s[i];
    }
    int res = 0;
    for(int i=0;i<1<<15;i++){
        int st=S,wt=0,p=0;
        for(int j=0;j<15;j++){
            if(i&(1<<j)){
                st-=s[j];
                wt+=w[j];
                if(j<10)p--;
                else p++;
            }
        }
        if(p<0)continue;
        if(st<0)continue;
        res = max(res,wt);
    }
    cout << res << endl;
}