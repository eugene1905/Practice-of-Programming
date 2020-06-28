#include <iostream>
#include <queue>
#include <string>
using namespace std;
struct Patient{
    int id;
    int priority;
    Patient(int a, int b):id(a),priority(b){}
    bool operator<(const Patient& a)const{
        return (priority == a.priority?id > a.id:priority < a.priority);
    }
};
int main(){
    int t, n;
    cin >> t;
    while(t--){
        priority_queue<Patient> q[5];
        int cnt = 0;
        cin >> n;
        while(n--){
            string tmp;
            cin >> tmp;
            if(tmp == "IN"){
                int doc, prior;
                cin >> doc >> prior;
                q[doc].push(Patient(++cnt,prior));
            }
            else if(tmp == "OUT"){
                int doc;
                cin >> doc;
                if(q[doc].empty()){
                    cout << "EMPTY" << endl;
                }
                else{
                    Patient p = q[doc].top();
                    q[doc].pop();
                    cout << p.id << endl;
                }
            }
        }
    }
}