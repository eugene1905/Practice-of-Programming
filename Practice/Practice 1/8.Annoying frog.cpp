#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int r,c,n;
struct Node{
    int x,y;
    bool operator<(const Node& a)const{
        return (x == a.x?y < a.y:x < a.x);
    }
};
Node rice[5100];
bool isOut(int x, int y){
    if(x < 1 || x > r || y < 1 || y > c)
        return true;
    return false;
}

int main(){
    int res = 0;
    cin >> r >> c >> n;
    for(int i = 0; i < n; i++){
        cin >> rice[i].x >> rice[i].y;
    }
    sort(rice,rice+n);
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            Node gap, nxt;
            gap.x = rice[j].x - rice[i].x, gap.y = rice[j].y - rice[i].y;
            nxt.x = rice[j].x + gap.x, nxt.y = rice[j].y + gap.y;
            int step = 2;
            if(!isOut(rice[i].x - gap.x, rice[i].y - gap.y)) //Previous rice is inside
                continue;
            if(isOut(rice[i].x + (gap.x * res),rice[i].y + (gap.y * res)))  //Cannot be the best ans
                continue;
            if(isOut(nxt.x,nxt.y)) //Cannot be answer
                continue;
            while(!isOut(nxt.x,nxt.y)){
                if(binary_search(rice,rice+n,nxt)){
                    step++;
                    nxt.x += gap.x, nxt.y += gap.y;
                }
                else{
                    step = 0;
                    break;
                }
            }
            if(step >= 2)
                res = max(res,step);
        }
    }
    cout << res << endl;
    return 0;
}