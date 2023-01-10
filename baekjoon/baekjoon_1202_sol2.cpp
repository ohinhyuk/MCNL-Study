#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

bool comp(pair<int,int> p1 , pair<int,int> p2){
    if(p1.second == p2.second) return p1.first < p2.first;

    return p1.second > p2.second;
}

int main(int argc, char** argv){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    priority_queue<int> most_value;

    int N , K;
    int mass, value;
    long long sum = 0;

    vector<pair<int,int> >jewel;
    vector<int> bag;
    
    cin >> N >> K;

    for(int i = 0 ; i < N ; ++i){
        cin >> mass >> value;

        jewel.push_back(make_pair(mass,value));
    }

    for(int i = 0 ; i < K ; ++i){
        cin >> mass;

        bag.push_back(mass);
    }

    sort(bag.begin(),bag.end());
    sort(jewel.begin(),jewel.end());
    
    int j = 0;

    for(int i = 0 ; i < K; ++i){

        while(j < N && bag[i] >= jewel[j].first){
            most_value.push(jewel[j++].second);
        }

        if(!most_value.empty()){

            sum += (long long)most_value.top();
            most_value.pop();
    
        }
    }

    cout << sum;
}