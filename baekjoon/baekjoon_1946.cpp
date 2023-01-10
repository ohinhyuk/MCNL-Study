#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc , char** argv){
    int T, N;

    int temp1, temp2 , cnt ,max ;

    cin >> T;

    vector< pair<int ,int> > v;

    for(int i = 0 ; i < T; ++i ){
        
        
        cin >> N;

        for(int j = 0 ; j < N ; ++j){

            cin >> temp1 >> temp2;

            v.push_back( make_pair(temp1, temp2) );


        }

        sort(v.begin() , v.end());

        cnt = 1;
        max = v[0].second;

        for(int k = 1 ; k < v.size() ;k++){
            
            if(max >= v[k].second) {cnt++; max = v[k].second;}
            
            
            
        }

        cout << cnt << endl;

        v.clear();

    }


}