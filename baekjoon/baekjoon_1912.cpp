#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc ,char** argv){
    int N ; 
    cin >> N ;
    int dp[N];
    int max;

    for(int i = 0 ; i < N ; ++i){
        cin >> dp[i];
    }

    max = dp[0];

    for(int i = 1 ; i < N ; ++i){
        if(dp[i-1] > 0){
            dp[i] += dp[i-1];
        }
        if(max < dp[i]) max = dp[i];
    }

    // cout << *max_element(dp , dp + N) << endl;
    cout << max;

}