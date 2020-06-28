#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x){
    return pow(x,5) - 15 * pow(x,4) + 85 * pow(x,3) - 225 * pow(x,2) + 274 * x - 121;
}
int main(){
    double l = 1.5, r = 2.4;
    double eps = 1e-15, res;
    while(l <= r){
        double mid = l + (r - l) / 2;
        double y = f(mid);
        if(y < 0){
            r = mid - eps;
        }
        else
            l = mid + eps;
    }
    cout << fixed << setprecision(6) << l << endl;
}