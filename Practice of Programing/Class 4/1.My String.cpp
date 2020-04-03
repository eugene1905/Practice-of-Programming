#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if(s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
	MyString(const MyString& a)	{
		if (a.p){
			p = new char[strlen(a.p) + 1];
			strcpy(p,a.p);
		}	
	}
	MyString & operator=(const MyString& a){
		p = new char [strlen(a.p)+1];
		strcpy(p,a.p);
		return *this;
	}
	MyString & operator=(const char* a){
		p = new char [strlen(a)+1];
		strcpy(p,a);
		return *this;
	}	
	void Copy(const char * s){
		if(s){
			p = new char[strlen(s)+1];
			strcpy(p,s);
		}
		else
			p = NULL;
	}
	friend ostream & operator<<(ostream& o, const MyString& a){
		o << a.p;
		return o;
	}

};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;
		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
	}
}
