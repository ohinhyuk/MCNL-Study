#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


bool comp(pair<int,int> &p1 , pair<int,int> &p2){
    if(p1.second == p2.second){
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

int main(int argc , char** argv){

    vector<pair<int,int> > v;

    int N , start , end , cnt;
    

    cin >> N;

    for(int i = 0 ; i < N ; ++i){
        
        cin >> start >> end;

        v.push_back(make_pair(start,end));
    }

    sort(v.begin() , v.end() , comp);

    // start = v[0].first;
    end = v[0].second;
    cnt = 1;

    for(int i = 1 ; i< N ; ++i){
        if(end <= v[i].first ){
            cnt++;
            // start = v[i].first;
            end = v[i].second;
        }
    }

    cout << cnt;

}
