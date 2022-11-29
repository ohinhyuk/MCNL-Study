#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int,int> p1 , pair<int,int> p2){
    return p1.first > p2.first;
}

int main(int argc, char** argv){

    vector<pair<int,int> > v;

    int N;
    int cnt;

    cin >> N ;

    int arr[N];

    cin >> arr[0];
    v.push_back(make_pair(1, arr[0]));

    for(int i = 1 ; i < N ; ++i){
        cin >> arr[i];
        cnt = 0;

        for(int j = 0; j < v.size(); ++j){
            if(v[j].second < arr[i] && v[j].first > cnt){
                cnt = v[j].first;
            }
        }
        v.push_back(make_pair(cnt+1 , arr[i]));
    
    }
    
    sort(v.begin(), v.end(), comp);
    
    cout << v[0].first;

}