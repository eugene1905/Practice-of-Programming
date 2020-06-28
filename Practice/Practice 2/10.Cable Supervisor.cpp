#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
double cable[10005];
int N,K;
bool valid(int a){
    int res = 0;
    for(int i = 0; i < N; i++){
        res += cable[i] / a;
        if(res >= K)return true;
    }
    return false;
}
int bs(){
    int res = 0;
    int l = 1, r = cable[N-1];
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
    cin >> N >> K;
    double s;
    for(int i = 0; i < N; i++){
        cin >> s;
        cable[i] = s * 100;
    }
    sort(cable,cable+N);
    cout << fixed << setprecision(2) << bs() / 100.00 << endl;
}