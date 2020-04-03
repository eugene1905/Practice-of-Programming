#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8; 
		if( v ) 
			c = c | (1 << bp);
		else 
			c = c & ~(1 << bp);
	}
    class BitMemory{
        public:
            int bitPos;
            char* bytePos;
            BitMemory(int x, char* y):bitPos(x),bytePos(y){}
            operator int(){
                int c = (*bytePos & ~(1 << bitPos)) >> bitPos;
                return c;
            }
            BitMemory& operator=(int i){
                char& c = *bytePos;
                if(i) 
                    c = c | (1 << bitPos);
                else 
                    c = c & ~(1 << bitPos);
                return *this;
            }
    }
    int operator[](int i){
        return BitMemory(i%8,a+i/8);
    }
    void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}