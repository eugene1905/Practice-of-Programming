#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) //string Length
{	
	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s) // string d = stirng s
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2) //
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
	private:
		char str[100];
	public:
		MyString(const char* str1){
			strcpy(str,str1);
		}
		MyString(const MyString& a){
			strcpy(str,a.str);
		}
		MyString(){
			str[0] = 0;
		}
		MyString(char& a){
			str[0] = a;
		}
		MyString operator+(const MyString& a){
			char tmp[100];
			strcpy(tmp,str);
			strcat(tmp,a.str);
			return tmp;
		}
		MyString operator+(const char* a){
			char tmp[100];
			strcpy(tmp,str);
			strcat(tmp,a);
			return tmp;
		}
		friend MyString operator+(const char* a, const MyString& b){
			char tmp[100];
			strcpy(tmp,a);
			strcat(tmp,b.str);
			return tmp;	
		}
		MyString& operator=(const MyString& a){
			strcpy(str,a.str);
			return *this;
		}
		MyString& operator+=(const char* a){
			strcat(str,a);
			return *this;
		}
		friend ostream& operator<<(ostream& o, MyString a){
			o << a.str;
			return o;
		}
		
				
		char& operator[](int i){
			return this->str[i];
		}
		MyString operator()(int i,int j){
			MyString tmp;
			int k = 0;
			tmp.str[j] = 0;
			for(;j> 0;j--,i++){
				tmp.str[k] = str[i];
				k++;
			}
			return tmp;
		}
		bool operator>(MyString a){
			return str[0] > a.str[0];
		}
		bool operator==(MyString a){
			return str[0] == a.str[0];
		}
		bool operator<(MyString a){
			return str[0] < a.str[0];
		}
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( *s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	cout << s1(0,4) << endl;
	cout << s1(5,10) << endl;
	return 0;
}

