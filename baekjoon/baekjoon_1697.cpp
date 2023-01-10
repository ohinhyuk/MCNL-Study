#include <iostream>
#include <queue>

using namespace std;

bool visited[100001] = {false};

int main(int argc, char** argv){
    
    queue<pair<int, int> >q;
    
    int N , K;
    int second = 0;

    cin >> N >>K;
    q.push( make_pair(N,second));
    
    visited[N] = true;

    if(N == K ){
        cout << 0;
        return 0;
    }

    while(!q.empty()){

        if(N == K) break;
        
        N = q.front().first;
        second = q.front().second + 1;
        q.pop();

        if(N-1 >= 0 && N-1 <= 100000 && !visited[N-1] ){
            q.push( make_pair(N-1,second) );
            visited[N-1] = true;
        }
        if(N+1 >= 0 && N+1 <= 100000 && !visited[N+1]){
            q.push( make_pair(N+1,second) );
            visited[N+1] = true;
        }
        if(N *2 <= 100000){
            q.push(make_pair(N*2,second));
            visited[N*2] = true;
        }
        
    }

    cout << second - 1;
}