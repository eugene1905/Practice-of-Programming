#include <iostream>
using namespace std;
// 在此处补充你的代码
int sqr(int n) {
    return n * n;
}
template <class T>
int sum(int a[], int b, T p){
    int res = 0;
    for(int i = 0; i < b ; i++)
        res += p(a[i]);
    return res;
}
int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << sum(a, n, sqr) << endl;
    }
    return 0;
}