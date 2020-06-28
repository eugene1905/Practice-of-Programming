#include <iostream>
#include <algorithm>
#define inf 1<<30
using namespace std;
int main(){
    int n;
    int res = inf;
    cin >> n;
    for(int i = 1; i < n; i++){
        if(n % i == 0){
            for(int j = 1; j < (n / i); j++){
                if((n / i) % j == 0){
                    int k = n / i / j;
                    res = min(res,i*j + j*k + i*k);
                }
            }
        }
    }
    cout << 2 * res << endl;
}