#include <iostream>

using namespace std;

int main(int argc,  char** argv){

    int N , L , hole, j;
    int num = 0;
    cin >> N >> L;

    bool pipe[1001];
    
    for(int i = 0 ; i < 1001 ; ++i){
        pipe[i] = false;
    }



    for(int i = 0 ; i < N ; ++i){
        cin >> hole;
        pipe[hole] = true;
    }

    for(int i = 1; i < 1001 ; ++i){
        if(pipe[i] == true){
            num++;
            i = i - 1 + L;
        }
    }


    cout << num;

}