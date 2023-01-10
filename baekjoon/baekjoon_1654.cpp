#include <iostream>

using namespace std;

int main(int argc, char** argv){
    
    int K , N , N_num;
    unsigned int len;
    unsigned int left = 1;
    unsigned int right = 0;
    unsigned int ans = 0;
    
    cin >> K >> N;
    
    unsigned int lens[K];

    for(int i = 0 ; i < K ; ++i){
        cin >> lens[i];
        right = max(right , lens[i]);
    }

    while(left <= right){
        
        N_num = 0;
        len = (left + right) /2;
        
        for(int i = 0 ; i < K ; ++i) N_num += lens[i]/len;

        if(N_num >= N){
            left = len+1;
            ans = max(ans,len);
        } 
        else{
            right = len - 1;
        }

    }

    cout << ans << endl;

}