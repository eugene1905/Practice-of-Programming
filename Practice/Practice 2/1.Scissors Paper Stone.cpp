#include <iostream>
using namespace std;
int Awin(int a, int b){
    int n = a - b;
    if(n == 0)return 0;
    else if(n == 5 || n == -3 || n == -2)return 1;
    else return -1;
}
int main(){
    int N,NA,NB;
    int A[100],B[100];
    cin >> N >> NA >> NB;
    for(int i = 0; i < NA; i++){
        cin >> A[i];
    }
    for(int i = 0; i < NB; i++){
        cin >> B[i];
    }
    int p1 = 0, p2 = 0;
    int res = 0;
    for(int i = 0; i < N; i++){
        if(p1 == NA)p1 = 0;
        if(p2 == NB)p2 = 0;
        res += Awin(A[p1++],B[p2++]);
    }
    if(res == 0)cout << "draw" << endl;
    else if (res > 0)cout << "A" << endl;
    else cout << "B" << endl;

}