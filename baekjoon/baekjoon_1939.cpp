#include <iostream>
#include <vector>

using namespace std;

vector<pair<int , int> > temp;
vector<vector> v;

vector<vector<int> > visit;

void DFS(int start){
    for(int i = 0 ; i < v[start-1].size() ; ++i){
        DFS(v[start-1][i])
    }
}

int main(int argc, char** argv){
    
    

    int N , M , num;
    int start , end , weight;

    cin >> N >> M ;
    
    for(int i = 0 ; i < M ; ++i){
        temp.clear();
        
        cin >> start >> end >> weight;

        v[start-1].push_back(make_pair(end , weight));
        v[end-1].push_back(make_pair(start , weight)); 

        
    }

    cin >> start >> end;

}