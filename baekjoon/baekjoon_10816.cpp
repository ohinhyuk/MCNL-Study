// #include <iostream>
// #include <algorithm>
// #include <map>

// using namespace std;

// int main(int argc , char** argv){
    
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);

//     int N,M,temp;
//     map<int,int> m;
//     cin >> N;

//     for(int i = 0 ; i < N ; ++i){
//         cin >> temp;
//         m[temp]++;
//     }

//     cin >> M;

//     for(int i = 0 ; i < M ; ++i){
//         cin >> temp;
//         auto it = m.find(temp);
//         if(it == m.end()) cout << 0 << ' ';
//         else cout << it->second << ' ';
//     }
// }

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

vector<int> v;

int upper_b(int num){
    int left = 0;
    int right = v.size()-1;
    int mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(v[mid] > num){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return right;
}

int lower_b(int num){
    int left = 0 ;
    int right = v.size()-1;
    int mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(v[mid] >= num){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return left;
}


int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N,M,temp;
    cin >> N;
    for(int i = 0 ; i < N; ++i){
        cin >> temp;
        v.push_back(temp);
    }
    
    sort(v.begin(),v.end());

    cin >> M ;

    for(int i = 0 ; i < M ; ++i){
        cin >> temp;
        // int a = upper_b(temp);
        // int b = lower_b(temp);

        // cout << a - b + 1 << ' ';
    cout << upper_bound(v.begin(),v.end(),temp) - lower_bound(v.begin(),v.end(),temp) << ' ';
    }



}
