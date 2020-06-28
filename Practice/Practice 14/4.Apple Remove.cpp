#include<iostream>
#include<algorithm>
using namespace std;
int n, m, b[110] = { 0 };
int main(){
	int t;
	cin >> t;
	while (t--){
		cin >> n >> m;
		b[0] = 0, b[n+1] = 101;
		for (int i = 1; i <= n; ++i)
			cin >> b[i];
		int r = min(n,m);
        int ans = 0;
        for(int i = 0; i <= n; i++){
            ans = max(ans, b[min(n,i+r)+1] - b[i] - 1);
        }
        cout << ans << endl;
	}
	return 0;
}