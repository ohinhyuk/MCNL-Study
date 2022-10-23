#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv){

    vector<int> use;
    vector<long long int> deadline;

    long long int N, temp;

    cin >> N;

    for(int i = 0 ; i < N ; ++i){
        cin >> temp;
        deadline.push_back(temp);
    }
    for(int i = 0 ; i < N ; ++i){
        cin >> temp;
        use.push_back(temp);
    }

    long long int diff;
    long long int cnt = 0;

    for(int i = 0 ; i < N ; ++i){
        diff = use[i] - deadline[i];

        if(diff <= 0 ) continue;

        cnt += (diff / 30) + 1;
        if(diff % 30 == 0) cnt -=1; 

    }

    cout << cnt;

}