#include <iostream>
using namespace std;
class Complex{
public:
    int r,i;
    Complex(char* a):r(a[0] - '0'),i(a[2]-'0'){}
    Complex(const Complex& A):r(A.r),i(A.i){}
    Complex():i(0),r(0){}
    Complex(int a):r(a),i(0){}
    Complex operator+(const Complex A){
        Complex tmp = *this;
        tmp.r += A.r;
        tmp.i += A.i;
        return tmp;
    }
    Complex operator-(const Complex A){
        Complex tmp = *this;
        tmp.r -= A.r;
        tmp.i -= A.i;
        return tmp;
    }
    Complex operator*(const Complex A){
        Complex tmp;
        tmp.r = r * A.r - i * A.i;
        tmp.i = r * A.i + i * A.r;
        return tmp;
    }
    Complex& operator+=(const Complex A){
        i += A.i;
        r += A.r;
        return *this;
    } 
    Complex& operator-=(const Complex A){
        i -= A.i;
        r -= A.r;
        return *this;
    } 
    Complex& operator*=(const Complex A){
        Complex tmp = *this;
        r = tmp.r * A.r - tmp.i * A.i;
        i = tmp.r *A.i + tmp.i * A.r;
        return *this;
    }   
    friend ostream& operator<<(ostream& o, const Complex A){
        if(A.i == 0)
            o << A.r;
        else if(A.i != 0 && A.r != 0)
            o << A.r <<  "+" << A.i << "i";
        else if(A.i != 0 && A.r == 0)
            o << A.i << "i";
    }

};

int main() {
	Complex c1;
	Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}