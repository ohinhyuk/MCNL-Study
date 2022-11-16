#include <iostream>

using namespace std;

int main(int argc , char** argv){
    
    int n;
    
    cin >> n;

    if(n == 1){
        cout << 1;
        return 0;
    }
    else if(n ==2){
        cout << 2;
        return 0;
    }


    long long int  tile_case[n+1];

    tile_case[1] = 1;
    tile_case[2] = 2;

    for(int i = 3 ; i < n+1; ++i){
        tile_case[i] = tile_case[i-1] + tile_case[i-2];
    }

    cout << tile_case[n] % 10007;


}