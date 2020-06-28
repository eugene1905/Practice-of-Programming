#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int main(){
    int n;
    cin >> n;
    while(n--){
        string s,s2,res = "";
        cin >> s;
        s2 = s;
        reverse(s2.begin(),s2.end());
        int len = s.length();
        for(int i = 0; i < len; i++){
            for(int j = i + 1; j <= len; j++){
                string sub = s.substr(i,j);
                if(s.find(sub) != -1 && s2.find(sub) != -1){
                    if(sub.length() > res.length())
                        res = sub;
                }
            }
        }
        cout << res << endl;
    }
}