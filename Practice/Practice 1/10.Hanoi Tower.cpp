#include <iostream>
using namespace std;
void move(int n, char s, char e, char m){
    if(n == 1){
        cout << s << "->" << n << "->" << e << endl;
        return;
    }
    move(n-1,s,m,e);
    cout << s << "->" << n << "->" << e << endl;
    move(n-1,m,e,s);
}
int main(){
    int n;
    char a,b,c;
    cin >> n >> a >> b >> c;
    move(n,a,b,c);
}
