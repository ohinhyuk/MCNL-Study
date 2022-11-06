#include <iostream>
#include <vector>

int original[8][8];
int laboratory[8][8];
int N, M;
int cnt;
int max_cnt = -1;

using namespace std;

vector<pair<int,int> >two;

void copy_ori_2_lab(){
    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < M ; ++j){
            laboratory[i][j] = original[i][j];
        }
    }
}

void DFS(int i , int j){
    laboratory[i][j] = 2;

    if(i-1 >= 0 && laboratory[i-1][j] ==0) DFS(i-1,j);
    if(i+1 < N && laboratory[i+1][j] ==0) DFS(i+1,j);
    if(j-1 >= 0 && laboratory[i][j-1] ==0) DFS(i,j-1);
    if(j+1 < M && laboratory[i][j+1] ==0) DFS(i,j+1);

}

void spread(){
    
    copy_ori_2_lab();

    for(int k = 0 ; k < two.size(); ++k){
        DFS(two[k].first , two[k].second);
    }

    cnt = 0;

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < M ;++j){
            if(laboratory[i][j]==0) cnt++;
        }
    }

    if(max_cnt < cnt) max_cnt = cnt;

}


void wall(int i , int j ,int wall_num){
    if(wall_num == 3){
        spread();
        return ;
    }
    else{
        for(int i = 0 ; i < N ; ++i){
            for(int j = 0 ; j < M ; ++j){
                if(original[i][j] == 0){
                    original[i][j] =1;
                    wall_num++;
                    wall(i,j,wall_num);
                    wall_num--;
                    original[i][j]=0;
                }
            }
        }   
    }
    
    
}

int main(int argc , char** argv){

    cin >> N >> M;

    for(int i = 0 ; i < N ; ++i ){
        for(int j = 0 ; j < M ; ++j){
            cin >> original[i][j];

            if(original[i][j]==2) two.push_back(make_pair(i,j));

        }
    }

    wall(0,0,0);

    cout << max_cnt;

}