#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int L ,P , V ,cnt;
    int case_num = 0;
    while(1){
        cin >> L >> P >> V;

        if(L== 0 && P ==0 && V ==0) break;
        
        cnt = 0;

        while(V > P){
            V -= P;
            cnt += L;
        }

        if(V >= L){
            cnt += L;
        }else{
            cnt += V;
        }

        cout << "Case " <<++case_num <<": "<< cnt << endl;
    }
}