#include <iostream>

using namespace std;

int main(int argc,  char** argv){
    int A,B;
    int cnt = 1;

    cin >> A >> B;

    while(B > 0){
        if(B < A){
            cout << -1;
            return 0;
        }
        else if(A == B){
            cout << cnt;
            return 0;
        }
        else if(B % 10 == 1){
            B /= 10;
        }
        else if(B %2 == 0){
            B /= 2;
        }
        else{
            cout << -1;
            return 0;
        }

        cnt++;
    }

    return 0;
    
}