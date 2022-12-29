#include <iostream>

using namespace std;

int arr[20];
int N , S;
int cnt = 0;
void recur(int i, int sum){
    if(i == N){
        if(S == sum) cnt++;
        return ;
    }
    recur(i+1,sum + arr[i]);
    recur(i+1,sum);

    
} 

int main(int argc , char** argv){
    

    cin >> N >> S;

    for(int i = 0 ; i < N ; ++i) cin >> arr[i];

    recur(0,0);

    if(S ==0) cnt--;
    cout << cnt << endl;
}