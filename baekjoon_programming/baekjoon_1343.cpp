#include <iostream>

using namespace std;

int main(int argc , char** argv){
    string s;
    cin >> s;

    int stk = 0;
    
    string result = "";

    for(int i = 0 ; i < s.size() ; ++i){
        if(s[i]=='X') stk++;
        
        if(stk ==2 && i == s.size()-1 || stk == 2 && s[i+1]=='.'){
            result += "BB";
            stk = 0;
        }
        else if(stk == 4){
            result += "AAAA";
            stk = 0;
        }
        else if(s[i]=='.'){
            result += ".";
            stk = 0;
        }
    }
    if(result.size() != s.size()) cout << -1;
    else cout << result ;
}
