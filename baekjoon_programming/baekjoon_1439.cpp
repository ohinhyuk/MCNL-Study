#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int zero = 0 , one = 0;
    string N;

    cin >> N;

    if(N[0] == '0') zero++;
    else one++;

    for(int i = 1 ; i < N.size() ; ++i){
        if(N[i-1] == '1' && N[i] == '1') continue;
        else if(N[i-1] == '0' && N[i] =='0') continue;
        else if(N[i-1] == '1' && N[i]== '0') zero++;
        else if(N[i-1] == '0' && N[i]== '1') one++;
    }


    if(zero + one == 1) cout << 0;
    else cout << min(zero , one);
}