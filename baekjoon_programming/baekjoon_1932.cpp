#include <iostream>

using namespace std;

int main(int argc , char** argv){
    int N ;
    
    cin >> N;
    // int arr[N][N];
    int dp[N][N] ;

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < N ; ++j){
            // arr[i][j] = 0;
            dp[i][j] = 0;
        }
    }

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j <= i ; ++j){
            // cin >> arr[i][j];
            cin >> dp[i][j];
        }
    }

    // dp[0][0] = arr[0][0];

    for(int i = 1 ; i < N ; ++i){
        for(int j = 0 ; j <= i ; ++j){
            if( j == 0 ){
                dp[i][j] = dp[i][j] + dp[i-1][j];
            }
            else if( j == i){
                dp[i][j] = dp[i][j] + dp[i-1][j-1];
            }
            else{
                dp[i][j] = dp[i][j] + max(dp[i-1][j] , dp[i-1][j-1]);
            }
        }
    }
    int max = -1;
    for(int i = 0 ; i < N ; ++i){
        if(max < dp[N-1][i]) max = dp[N-1][i];
    }   

    cout << max;
}