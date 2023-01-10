#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

bool comp(pair<int,int> p1 , pair<int,int> p2){
    // if(p1.second == p2.second) return p1.first < p2.first;

    return p1.second > p2.second;
}

int main(int argc, char** argv){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N , K;
    int mass, value;
    long long sum = 0;

    vector<pair<int,int> >jewel;
    // vector<int> bag;
    multiset<int> bag;

    multiset<int> ::iterator iter;
    
    cin >> N >> K;

    for(int i = 0 ; i < N ; ++i){
        cin >> mass >> value;

        jewel.push_back(make_pair(mass,value));
    }

    for(int i = 0 ; i < K ; ++i){
        cin >> mass;

        // bag.push_back(mass);
        bag.insert(mass);
    }

    // sort(bag.begin(),bag.end());
    sort(jewel.begin(),jewel.end(),comp);
    
    for(int i = 0 ; i < N; ++i){
        
        if(bag.size()== 0) break;

        // for(iter = bag.begin(); iter != bag.end() ; ++iter){
        //     if((*iter)>= jewel[i].first){
        
        // iter= lower_bound(bag.begin(),bag.end(),jewel[i].first);
        iter =bag.lower_bound(jewel[i].first);
        if(iter != bag.end()){
            sum += jewel[i].second;
            bag.erase(iter);
        }
                // break;
        //     }
        // }
    }

    cout << sum;
}