#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
	private:
		istream& i;
		T content;
		
	public:
		CMyistream_iterator(istream& stream):i(stream){
			i >> content;
		}
		T operator *(){
			return content;
		}
		CMyistream_iterator& operator++(int){
			i >> content;
			return *this;
		}
};



int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //read n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //read n2
		 inputInt ++;
		 n3 = * inputInt; //read n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}
