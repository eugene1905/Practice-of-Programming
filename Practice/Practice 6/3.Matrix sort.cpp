#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat{
	int h,w;
public:
	Mat(int height,int width):h(height),w(width){id = cnt++,sum = 0;}
// 在此处补充你的代码
    int id;
    static int cnt;
    int arr[4][4];
    int sum;
    friend istream& operator>>(istream& is, Mat& A){
        for(int i = 0; i < A.h; i++){
            for(int j = 0; j < A.w; j++){
                is >> A.arr[i][j];
                A.sum += A.arr[i][j];
            }
        }
        return is;
    }
    friend ostream& operator<<(ostream& o, Mat& A){
        for(int i = 0; i < A.h; i++){
            for(int j = 0; j < A.w; j++){
                o << A.arr[i][j] << " ";
            }
            o << endl;
        }
        return o;
    }
    bool operator<(const Mat& y){
        int a1 = w*h;
        int a2 = y.w*y.h;
        return (a1 == a2?id > y.id : a1 < a2);
    }
};
int Mat::cnt = 0;
bool comparator_1(const Mat& x, const Mat& y){
    return (x.sum == y.sum? x.id > y.id : x.sum < y.sum);
}
class comparator_2{
public:
    comparator_2(){}
    bool operator()(Mat& x,Mat& y){
        return x.id < y.id;
    }
};
int main()
{
	vector<Mat> m;
	m.push_back(Mat(2,2));
	m.push_back(Mat(3,4));
	m.push_back(Mat(2,2));
	cin >> m[0] >> m[1] >> m[2];
	sort(m.begin(),m.end());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_1);
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_2());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	return 0;
}