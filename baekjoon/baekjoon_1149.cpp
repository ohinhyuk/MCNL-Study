#include <iostream>

using namespace std;

int main(int argc , char** argv){
    int N;
    int R , G , B;


    cin >> N;

    int house[N][3];

    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < 3 ; ++j){
            cin >> house[i][j];
        }
    }

    for(int i = 1 ; i < N ; ++i){

        for(int j = 0 ; j < 3 ; ++j){
            if(j == 0){
                house[i][j] = min(house[i-1][1] , house[i-1][2]) + house[i][j];
            }
            else if(j == 1){
                house[i][j] = min(house[i-1][0] , house[i-1][2]) + house[i][j];
            }
            else if(j == 2){
                house[i][j] = min(house[i-1][0] , house[i-1][1]) + house[i][j];
            }
        }

       
    }

    cout << min(house[N-1][0],min(house[N-1][1],house[N-1][2]));

}