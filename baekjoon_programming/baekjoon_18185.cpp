#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    int N;
    int cnt = 0;
    cin >> N;

    vector<int> A(N);

    for(int i = 0 ; i < N ; ++i){
        cin >> A[i];
    }

    for(int i = 0 ; i < N-2 ; ++i){
        while(A[i] > 0){
            if(A[i+1] > A[i+2] && A[i+1] > 0 && A[i+2] > 0){
                cnt += 5;
                A[i]-=1;
                A[i+1]-=1;
            }
            else if(A[i] >= 1 && A[i+1] >= 1 && A[i+2] >= 1){
                cnt += 7;
                A[i]-=1;
                A[i+1]-=1;
                A[i+2]-=1;
            }
            else if(A[i] >= 1 && A[i+1] >= 1){
                cnt += 5;
                A[i]-=1;
                A[i+1]-=1;
            }
            else{
                A[i]-=1;
                cnt += 3;
            }
        }
    }
    
    while(A[N-2] > 0){
        if(A[N-2] >= 1 && A[N-1] >= 1){
                cnt += 5;
                A[N-2]-=1;
                A[N-1]-=1;
            }
        else{
            A[N-2]-=1;
            cnt += 3;
        }
    }
    while(A[N-1] > 0){
        A[N-1]-=1;
        cnt+=3;
    }

    cout << cnt << endl;

}