#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int T , N;

    cin >> T;

    long long dp[101];

    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;

    for(int i = 4 ; i <= 100 ; ++i){
        dp[i] = dp[i-3] + dp[i-2];
    }

    for(int i = 0 ; i < T ; ++i){
        cin >> N;
        cout << dp[N] << endl;
    }
    
}