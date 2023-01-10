#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){

    int N , C ,cnt;
    int prev, left,right , mid;
    int ans = -1;
    
    cin >> N >> C;
    
    int house[N];

    for(int i = 0 ; i < N ; ++i) cin >> house[i];
    
    sort(house , house + N);

    left = 1;
    right = house[N-1];

    while(left <= right){

        mid = (left+right)/2;

        prev = house[0];
        cnt = 1;

        for(int i = 1 ; i < N; ++i){
            if(house[i] - prev >= mid){
                cnt++;
                prev = house[i];
            }
        }

        if(cnt >= C){
            left = mid + 1;
            ans = max(ans , mid);
        } 
        else right = mid - 1;

    }
    
    cout << ans << "\n";
    
    
}