#include <iostream>
// #include <vector>
// #include <algorithm>
using namespace std;

int main(int argc , char** argv){

    int N,M , temp1, temp2 ;
    // vector<int> line6;
    // vector<int> line1;
    int six = 1000 , one = 1000 , total = 0;
    
    cin >> N >> M;

    for(int i= 0 ; i < M ; ++i){
        cin >> temp1 >> temp2;

        if(six > temp1) six = temp1;
        if(one > temp2) one = temp2;
        
    }

    if(six > one * 6) six = one * 6;

    while(N >= 6){
        total += six;
        N -= 6;
    }

    if(one * N > six) total += six;
    else total += N * one;
    
    cout << total;
}