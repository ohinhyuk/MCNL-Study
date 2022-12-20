#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


int main(int argc, char** argv){
    
    map<string,int> m;
    
    string temp;
    int num = 1;
    int N ; 

    cin >> N ;
    vector<int> v(N);
    
    for(int i = 0 ; i < N ; ++i){
        v[i] = num++;
        if(num==4) num = 1;
    }
    
    unsigned seed = chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    
    shuffle(begin(v), end(v), default_random_engine(seed));

    for(auto x : v){
        cin >> temp;
        m.insert(make_pair(temp,x));
    }

    cout << "1조" << endl;
    for(auto x : m){
        if(x.second == 1){
            cout << x.first << endl;
        }
    }

    cout << "2조" << endl;
    for(auto x : m){
        if(x.second == 2){
            cout << x.first << endl;
        }
    }

    cout << "3조" << endl;
    for(auto x : m){
        if(x.second == 3){
            cout << x.first << endl;
        }
    }
        


}