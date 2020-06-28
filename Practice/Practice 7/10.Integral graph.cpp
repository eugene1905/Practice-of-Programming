#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class IntegralImage{
// 在此处补充你的代码
public:
    int w,h;
    int** v;
    IntegralImage(int a, int b):h(0),w(b){
        v = new int*[a];
        for(int i = 0; i < a; i++){
            v[i] = new int[w];
        }
     }
    IntegralImage& operator()(int* a){
        int x = 0;
        for(int i = 0; i < w; i++){
            v[h][i] = x + a[i];
            x += a[i];
            if(h != 0)v[h][i] += v[h-1][i];
        }
        h++;
        return *this;
    } 
    int* operator[](int a){
        return v[a];
    }
};
int main(){
    int H, W;
    cin >> H >> W;
    int ** image = new int*[H];
    for(int i=0;i<H;++i){
        image[i]=new int[W];
    }
    for(int i=0;i<H;++i)
        for(int j=0;j<W;++j)
         cin >> image[i][j];
    IntegralImage it(H,W);
    for_each(image, image+H, it);
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j)
            cout<<it[i][j]<<" ";
        cout<<endl;
    }
   
}