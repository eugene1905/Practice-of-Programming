#include <iostream>
#include <algorithm>
#define inf 1<<30
using namespace std;
int N,C;
int stall[100005];
bool valid(int a){
    int res = 1;
    int t = stall[0];
    for(int i = 1; i < N; i++){
        if(stall[i] - t >= a){
            res++;
            t = stall[i];
        }
        if(res >= C)return true;       
    }
    return false;
}
int bs(){
    int l = 1, r = stall[N-1] - stall[0];
    int res;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(valid(mid)){
            res = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return res;
}
int main(){
    cin >> N >> C;
    int minx = inf,maxx = 0;
    for(int i = 0; i < N; i++){
        cin >> stall[i];
    }
    sort(stall,stall+N);
    cout << bs() << endl;
}