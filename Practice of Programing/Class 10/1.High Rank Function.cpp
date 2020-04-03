#include <iostream>
using namespace std;
#include <functional>
template <class T1, class T2>
function<T2(T2)> f(T1 a) {
    return [=](T2 b) -> T2 { return b + a; };
}
int main() {
    cout << f<int, int>(7)(9) << endl;                      // 16
    cout << f<string, string>(" hello!")("world") << endl;  // world hello!
    cout << f<char, string>('!')("world") << endl;

    return 0;  // world!
}