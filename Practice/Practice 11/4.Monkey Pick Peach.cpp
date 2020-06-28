#include <iostream>
#include <algorithm>
using namespace std;
int bee[105]={},peach[105]={};

int main(){
    int hon;
    while(cin>>hon, hon!=-1){
        int n=0;
        while(cin >>peach[n]>>bee[n],bee[n]!=-1&&peach[n]!=-1){
            n++;
        }
        int ans=0;
        for(int i=0; i<n; i++){
            int cur=hon,res=0;
            for(int j=i; j < n; j++){
                cur-=bee[j];
                if(cur<0)break;
                res+=peach[j];
            }
            ans=max(ans, res);
        }
        cout << ans << endl;
    }
}