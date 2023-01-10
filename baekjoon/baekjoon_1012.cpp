#include <iostream>
#include <string.h>

using namespace std;

#define MAXLEN 50

bool baechu[MAXLEN][MAXLEN] = {false,};

void DFS(int i , int j){

    baechu[i][j] = false;

    if( i > 0 && baechu[i-1][j] == true){
        DFS(i-1, j);
    }
    if (i < MAXLEN-1 && baechu[i+1][j] == true){
        DFS(i+1,j);
    }
    if(j > 0 && baechu[i][j-1] == true){
        DFS(i,j-1);
    }
    if(j< MAXLEN-1 && baechu[i][j+1]==true){
        DFS(i,j+1);
    }
}

int main(int argc, char** argv){
    int T,M,N,K , x,y , cnt;
    cin >> T;

    for(int l = 0 ; l < T ; l++){

        cin >> M >> N >> K;

        cnt = 0;
        memset(baechu,false,sizeof(baechu));
        for(int p = 0 ; p < K ; ++p){
            cin >> x >> y;

            baechu[x][y] = true;
        }

        for(int i = 0 ; i < M ; ++i){
            for(int j = 0 ;j < N ; ++j){
                if(baechu[i][j]== true){
                    DFS(i,j);
                    cnt++;
                }
            }
        }

        cout << cnt << endl;
    }
}