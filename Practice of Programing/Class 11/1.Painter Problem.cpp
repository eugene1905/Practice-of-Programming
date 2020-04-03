#include <iostream>
#include <algorithm>
#include <string>
#include <math>
using namespace std;
int N; //size of N;
int wall[16][18];
int paint[15][15] = {0};
int min;
int searchAns(){
    for(int i = 1; i <= N-1; i++){
        for(int j = 1; j <= N; j++){
            if((wall[i][j] + paint[i][j-1] + paint[i][j+1] + paint[i-1][j]) % 2 != 0){
                paint[i+1][j] = 1;
            }
        }
    }
    for(int i = 1; i <= N; i++){
        if((wall[i][j] + paint[i][j-1] + paint[i][j+1] + paint[i-1][j]) % 2 != 0){
            return 0;
        }
    }
    int tmp = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(paint[i][j])tmp++;
        }
    }
    return tmp;
}
int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            char tmp;
            cin >> tmp;
            if(tmp == 'y')wall[i][j] = 1;
        }
    }

    for(int i = 1; i <= pow(2,N); i++){
        int c = 1;
        paint[1][c]++;
        while(paint[1][c] > 1){
            paint[1][c] = 0;
            c++;
            paint[1][c]++;
        }
        int tmp = searchAns();
        if(tmp > max)max = tmp;
    }
    if(!max)cout << max << endl;
    else{
        cout << "inf" << endl;
    }
}