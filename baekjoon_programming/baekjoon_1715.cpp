#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N , temp , sum = 0;

    priority_queue<int, vector<int> , greater<int> > pq;

    cin >> N;


    for(int i = 0 ; i < N ; ++i){
        cin >> temp;
        pq.push(temp);
    }

    for(int i = 0 ; i < N-1; ++i){
        
        temp = pq.top();
        pq.pop();
        temp += pq.top();
        pq.pop();
        
        sum += temp;
        pq.push(temp);

    }

    cout << sum;

}
