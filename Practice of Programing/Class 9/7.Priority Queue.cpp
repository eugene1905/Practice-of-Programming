#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
class sumOfPF{
	public:
		bool isPrime(int a){
			for (int i = 2; i <= sqrt(a); i++){
				if(a % i == 0)
					return false;
			}	
			return true;
		}
		bool operator()(int a, int b){
			int sumA = 0;
			int sumB = 0;
			for (int i = 2; i <= sqrt(a); i++){
				if(a % i == 0){
					int j = a / i;					
					if(isPrime(i))				
						sumA++;
					if(isPrime(j) && j != a)
						sumA++;
				}
			}
			for (int i = 2; i <= sqrt(b); i++){
				if(b % i == 0){
					int j = b / i;					
					if(isPrime(i))
						sumB++;
					if(isPrime(j) && j != b)
						sumB++;
				}
			}			
			if(sumA == sumB)
				return a < b;
			return sumA < sumB;		
		}
};

int main(){
	set<int,sumOfPF> s;
	int n;
	scanf("%d",&n);
	while(n--){
		for(int i = 0; i < 10; i++){
			int tmp;
			scanf("%d",&tmp);
			s.insert(tmp);
		}
		int min = *s.begin();
		int max = *s.rbegin();
		printf("%d %d\n",max, min);
		s.erase(min);
		s.erase(max);
	}
}
