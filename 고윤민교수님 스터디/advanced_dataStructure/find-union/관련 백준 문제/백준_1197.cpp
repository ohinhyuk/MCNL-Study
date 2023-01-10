#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

int root[100001];

int find(int num){

    if(root[num]==num) return num;

    return find(root[num]);
}

void union_(int a , int b){
    
    a = find(a);
    b = find(b);

    root[b] = a;

}

static bool CmpWeight(tuple<int,int,int> &t1 , tuple<int,int,int> &t2 ){
    return get<2>(t1) < get<2>(t2);
}

int main(int argc , char** argv){

    vector<tuple<int , int , int>> v;

    for(int i = 0 ; i < 100001; ++i) root[i] = i;

    cin.tie(NULL);cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int V , E;

    cin >> V >> E;

    int A , B , C;
    int total = 0;


    for(int i = 0 ;i < E ; ++i){
        cin >> A >> B >> C;

        v.push_back(make_tuple(A,B,C));

    }

    sort(v.begin(),v.end(), CmpWeight);

    for(int i = 0 ; i <v.size() ; ++i){
        
        A = get<0>(v[i]);
        B = get<1>(v[i]);
        C = get<2>(v[i]);
        
        if(find(A) != find(B)){
            union_(A,B);
            total += C;
        }

    }

    cout << total;

}