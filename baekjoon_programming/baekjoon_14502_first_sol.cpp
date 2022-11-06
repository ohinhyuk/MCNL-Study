#include <iostream>
#include <vector>

using namespace std;

int N, M ;
int laboratory[8][8];
int for_copy[8][8];
vector<pair<int,int> >two;

void DFS(int i , int j){
    laboratory[i][j] = 2;

    if(i-1 >= 0 && laboratory[i-1][j] == 0) DFS(i-1,j);
    if(i+1 < N && laboratory[i+1][j] == 0) DFS(i+1,j);
    if(j-1 >= 0 && laboratory[i][j-1] ==0) DFS(i,j-1);
    if(j+1 < M && laboratory[i][j+1] == 0) DFS(i,j+1);
    
}

void spread(){

    int i , j ;

    for(int k = 0 ; k < two.size(); ++k){
        i = two[k].first;
        j = two[k].second;

        DFS(i,j);
    }
}



int main(int argc , char** argv){
    int cnt;
    int wall1x = 0 , wall1y = 0;
    int wall2x = 0 , wall2y = 0;
    int wall3x = 0 , wall3y = 0;
    int max = -1;
    int t1x ,t2x, t3x , t1y, t2y ,t3y;

    cin >> N >> M ;

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < M ; ++j){
            cin >> for_copy[i][j];

            if(for_copy[i][j]==2) two.push_back(make_pair(i,j));
        }
    }

    for(wall3y = 0 ; wall3y < N ; ++ wall3y){
        for(wall3x = 0 ; wall3x < M ; ++wall3x){
            for(wall2y = 0 ; wall2y < N ; ++wall2y){
                for(wall2x = 0 ; wall2x < M ; ++wall2x){
                    for(wall1y = 0 ; wall1y < N ; ++ wall1y){
                        for(wall1x = 0 ; wall1x < M ; ++wall1x){

                                if(wall1x == wall2x && wall1y == wall2y) continue;
                                else if(wall2x == wall3x && wall2y == wall3y) continue;
                                else if(wall1x == wall3x && wall1y == wall3y) continue;

                                if(for_copy[wall1y][wall1x] == 0 && for_copy[wall2y][wall2x] == 0 && for_copy[wall3y][wall3x] == 0){
                                
                                cnt = 0 ;

                                for(int i = 0 ; i < N ; ++i){
                                    for(int j = 0 ; j < M ;++j){
                                        laboratory[i][j] = for_copy[i][j];
                                    }
                                }

                                laboratory[wall1y][wall1x] = 1;
                                laboratory[wall2y][wall2x] = 1;
                                laboratory[wall3y][wall3x] = 1;
                                

                                spread();   

                                for(int i = 0 ; i < N ; ++i){
                                    for(int j = 0 ; j < M ;++j){
                                        if(laboratory[i][j]==0) cnt++;
                                    }
                                }              

                                if(max < cnt){
                                  max = cnt;
                                  t1x = wall1x;
                                  t2x = wall2x;
                                  t3x = wall3x;
                                  t1y = wall1y;
                                  t2y = wall2y;
                                  t3y = wall3y;  
                                } 

                                }
                            }
                        }
                }
            }
        }
    }

    cout << max << endl;

}