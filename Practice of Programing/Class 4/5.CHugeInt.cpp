#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
	private:
		char num[210];
	public:
		void reverse(char* p){
			int i = 0; int j = strlen(p) - 1;
			while (i < j){
				swap(p[i],p[j]);
				++i,--j;
			}
		}
		
		CHugeInt(char* s){
			memset(num,0,sizeof(num));
			strcpy(num,s);
			reverse(num);
		}
		
		CHugeInt(int n){
			int i = 0;
			memset(num,0,sizeof(num));
			while(n){
				num[i++] = (n % 10) + '0';
				n /= 10;
			}
		}
		
		CHugeInt operator+(const CHugeInt& a){
			CHugeInt tmp(0);
			int i = 0;
			while (true){
				if (a.num[i] == '\0' && num[i] == '\0'){
					if (tmp.num[i] != '\0'){
						tmp.num[i] += '0';
					}
					break;
				}
				else if (a.num[i] == '\0'){
					tmp.num[i] += num[i];
				}
				else if (num[i] == '\0'){
					tmp.num[i] += a.num[i];
				}
				else{
					tmp.num[i] += (a.num[i] + num[i] - '0');
				}
				if (tmp.num[i] - '9' > 0){
					++tmp.num[i+1];
					tmp.num[i] -= 10;
				}
				i++;
			}
			return tmp;
		}
		
		friend CHugeInt operator+(int n, const CHugeInt& a){
			return CHugeInt(n) + a;
		}
		
		CHugeInt operator+(int n){
			return CHugeInt(n) + *this;
		}
		
		friend ostream & operator<<(ostream &o, const CHugeInt &a){
			for (int i = strlen(a.num) - 1; i >= 0; i--){
				o << a.num[i];
			}
			return o;
		}
		
		CHugeInt operator+=(int n){
			*this = *this + n;
			return *this;
		}
		
		CHugeInt& operator++(){
			*this = *this + 1;
			return *this;
		}
		
		CHugeInt operator++(int){
			CHugeInt tmp(*this);
			*this = *this + 1;
			return tmp;
		}
		
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);
		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
