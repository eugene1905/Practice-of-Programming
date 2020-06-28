#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int res;
void fill(char a[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(a[i][j] == '?'){
                a[i][j] = 'W';
                a[j][i] = 'L';
                fill(a);
                a[i][j] = 'L';
                a[j][i] = 'W';
                fill(a);
                a[i][j] = '?';
                a[j][i] = '?';
                return;
            }
        }
    }
    int tmp = 4,score[4] = {};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(a[i][j] == 'W')
                score[i]++;
        }
    }
    for(int i = 1; i < 4; i++){
        if(score[0] >= score[i])tmp--;
    }
    res = min(res,tmp);
}
int main(){
    int n;
    cin >> n;
    while(n--){
        res = 4;
        char board[4][4];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                cin >> board[i][j];
                if(i == 0 && board[i][j] == '?'){
                    board[i][j] = 'W', board[j][i] = 'L';
                }
            }
        }
        fill(board);
        cout << res << endl;
    }
}