#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int i,j,n;
int solve(){
    int t1 = 1 << j;
    int t2 = 1 << i;
    int t = 0;
    t |= (n & t2);
    t |= t1 ^ (n & t1);
    t |= t1 - 2 * t2;
    return t;
}

int main(){
    int t;
    cin >> t;
    while (t--){
        cin >> n >> i >> j;
        cout << hex << solve() << endl;
    }
}
