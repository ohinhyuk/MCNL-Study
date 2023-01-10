#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc , char** argv){

    int X;
    
    cin >> X;

    int dp[X+1];

    dp[1] = 0;

    for(int i = 2 ; i < X+1 ; ++i){
        
        dp[i] = dp[i-1];

        if(i % 3 ==0 ) dp[i] = min(dp[i] , dp[i/3]);
        if(i % 2 ==0) dp[i] = min(dp[i] ,dp[i/2]);

        dp[i]++;
    }
    
    cout << dp[X];
}