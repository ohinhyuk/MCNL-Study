#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
string mins = "Z";

bool isValid(string s){
    int end = s.size()-1;
    for(int i = 1 ; i <= s.size()/2; ++i){
        string a = s.substr(end,i);
        string b = s.substr(end-i ,i);
        if(a == b) return false;
        end--;
    }
    return true;
}


void DFS(string s , int i){
    if(!isValid(s)) return;
    
    if(i == N){
        mins=min(mins , s);
        cout << s;
        exit(0);
    }
    
    DFS(s+'1',i+1);
    DFS(s+'2',i+1);
    DFS(s+'3',i+1);

}

int main(int argc, char** argv){
    string s = "";

    cin >> N;
    
    DFS(s,0);

    cout << mins;
}