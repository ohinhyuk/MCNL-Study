#include <iostream>

using namespace std;

int main(int argc , char** argv){

    int dp[11];

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    int n, T;

    cin >> T ;

    for(int i = 4 ; i < 11 ; ++i){
        dp[i] = dp[i-3] + dp[i-2] + dp[i-1];
    }

    for(int i = 0 ; i < T ; ++i){
        cin >> n;
        cout << dp[n] << "\n";
    }


}