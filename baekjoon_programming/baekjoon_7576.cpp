#include <iostream>
#include <queue>

using namespace std;

#define MAXLEN 1000

int tomato[MAXLEN][MAXLEN];
queue<pair<int,int> > q;
int M,N;
int dx[4] = {1 , 0 , -1 , 0};
int dy[4] = {0, 1, 0 , -1};

void BFS(int i , int j){
    
    tomato[i][j] = -1;

    for(int k = 0 ; k < 4 ; ++k){
        int nx = i + dx[k];
        int ny = j + dy[k];

        if(nx >= 0 && ny >= 0 && nx < N && ny < M && tomato[nx][ny]==0){
            tomato[nx][ny] = 1;
            q.push(make_pair(nx,ny));
        }
    }
}

int main(int argc, char** argv){
    
    int result = 0;

    cin >> M >> N ;

    // insert

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < M ; ++j){
            cin >> tomato[i][j];
            if(tomato[i][j]== 1) q.push(make_pair(i,j));
        }
    }

    // calculation

    while(!q.empty()){

        int temp_s = q.size();
        
        for(int i = 0 ; i < temp_s ; ++i){
            BFS(q.front().first,q.front().second);
            q.pop();
        }

        result++;

    }
    
    // check

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < M ; ++j){
            if(tomato[i][j]==0){
                cout << -1;
                return 0;
            }
        }
    }

    // cout result

    cout << result - 1;

}