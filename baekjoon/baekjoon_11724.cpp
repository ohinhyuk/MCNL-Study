#include <iostream>
#include <vector>

using namespace std;


vector<int> adj_li[1001];
bool check[1001];

void DFS(int k){
    check[k] = true;
    
    for(int i = 0 ; i < adj_li[k].size() ;++i){
        if(!check[adj_li[k][i]-1]){
            DFS(adj_li[k][i]-1);
        }
    }
}

int main(int argc , char** argv){
    int N , M , u , v ;
    int cnt = 0;

    cin >> N >> M;


    for(int i = 0 ; i < M ; ++i){
        
        cin >> u >> v;

        adj_li[u-1].push_back(v);
        adj_li[v-1].push_back(u);

    }

    for(int i = 0 ; i < N ; ++i){
        if(!check[i]){
            cnt++;
            DFS(i);
        }
    }

    cout << cnt;
}