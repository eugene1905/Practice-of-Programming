#include <iostream>
#include <cstring>
using namespace std;
int main(){
    int n;
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        int len=s.length(),ans=1<<30;
        for(int i=0;i<len;i++){
            int cnt=0;
            for(int j=0;j<=i;j++){
                if(s[j]=='1')
                    cnt++;
                if(cnt >= ans)break;
            }
            for(int j=i+1;j<len;j++){
                if(s[j]=='0')
                    cnt++;
                if(cnt>=ans)break;
            }
            ans = min(ans,cnt);
        }
        cout << ans << endl;
    }
}
