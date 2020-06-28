#include <iostream>
#include <map>
#include <set>
#include <string>
#include <queue>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        map<string,set<string> > computer;
        map<string,queue<string> > backpack;
        cin >> n;
        while(n--){
            string action, name, pokemon;
            cin >> action >> name >> pokemon;
            if(action == "C"){
                backpack[name].push(pokemon);
                if(backpack[name].size() > 6){
                    computer[name].insert(backpack[name].front());
                    backpack[name].pop();
                }
            }
            else if(action == "T"){
                auto i = computer[name].find(pokemon);
                if(i != computer[name].end()){
                    cout << "Success" << endl;
                    backpack[name].push(*i);
                    if(backpack[name].size() > 6){
                        computer[name].insert(backpack[name].front());
                        backpack[name].pop();
                    }
                    computer[name].erase(i);
                }
                else{
                    cout << "Failed" << endl;
                }
            }
        }
    }
}