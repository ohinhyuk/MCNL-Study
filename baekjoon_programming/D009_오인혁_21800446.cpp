#include <iostream>

using namespace std;

int bamboo[500][500];
int dp[500][500];
int n;
int max_eat = 0;
int dx[] = { 1 , -1 , 0 , 0};
int dy[] = { 0 , 0 , 1 , -1};

void init(){
    for(int i = 0 ; i < n ;++i){
        for(int j = 0 ; j < n ; ++j){
            dp[i][j] = 0;
        }
    }

}

int DFS(int x , int y){

    if(dp[x][y]) return dp[x][y];

    dp[x][y] = 1;

    for(int i = 0; i < 4 ; ++i){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx >= 0 && nx <n && ny >=0 && ny < n){
            if(bamboo[nx][ny] > bamboo[x][y]) dp[x][y] = max( dp[x][y] , DFS(nx,ny) + 1);
        }

    }

    return dp[x][y];
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int eat;
    cin >> n;
    
    for(int i = 0 ; i < n ; ++i){
        for(int j = 0 ; j < n ; ++j){
            cin >> bamboo[i][j];
        }
    }

    for(int i = 0 ; i < n ; ++i){
        for(int j = 0 ; j < n ; ++j){
            max_eat = max(max_eat , DFS(i,j));
        }
    }

    cout << max_eat << "\n";


}
