#include <iostream>
using namespace std;
#include <functional>
template<typename T1, typename T2, typename v>
function<v(v)> combine(T1 f1, T2 f2){
    return [=](v v1) ->v {return f1(f1(v1) + f2(v1));};
}
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;
    return 0;
}