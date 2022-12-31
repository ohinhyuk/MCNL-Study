#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<pair<int,int> > p;

int sudoku[9][9];

bool check_all_b(){
    for(int i = 0 ; i < p.size() ; ++i){
        
        int x = p[i].first;
        int y = p[i].second;

        for(int i = 0 ; i < 9 ; ++i){
            if(i!= y && sudoku[x][y] == sudoku[x][i]) return false;
            if(i!= x && sudoku[x][y] == sudoku[i][y]) return false;
        }

        for(int i = (x/3)*3 ; i < (x/3)*3 +3; ++i ){
            for(int j = (y/3)*3 ; j < (y/3)*3 +3 ; ++j){
                if( (i != x || j!=y) && sudoku[x][y] == sudoku[i][j]) return false;
            }
        }

    }

    return true;
}

bool check(int x , int y , int num){
    for(int k = 0 ; k < 9 ; ++k){
        if(k != x && sudoku[k][y] == num) return false;
        if(k != y && sudoku[x][k] == num) return false;
    }

    for(int i = (x/3)*3 ; i < (x/3)*3 +3; ++i ){
            for(int j = (y/3)*3 ; j < (y/3)*3 +3 ; ++j){
                if( (i != x || j!=y) && num == sudoku[i][j]) return false;
            }
    }
    return true;
}

void DFS(int n){

    if(n == p.size()){
        if(check_all_b()){
            cout << endl;
            for(int i = 0 ; i < 9 ; ++i){
                for(int j = 0 ; j < 9 ; ++j){
                    cout << sudoku[i][j] << ' ';
                }
            cout << "\n";
            }
            exit(0);
        }
        return ;
    }
    
    int x = p[n].first;
    int y = p[n].second;

    for(int i = 1 ; i <= 9 ; ++i){
        if(check(x,y,i)){
            sudoku[x][y] = i;
            DFS(n+1);
            sudoku[x][y] = 0;
        }
    }

}

int main(int argc ,char** argv){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    for(int i = 0 ; i < 9 ; ++i){
        for(int j = 0 ; j < 9 ; ++j){
            cin >> sudoku[i][j];
        }
    }

    for(int i = 0 ; i < 9 ; ++i){
        for(int j = 0 ; j < 9 ; ++j){
            if(sudoku[i][j] == 0){
                p.push_back(make_pair(i,j));
            }
        }
    }

    DFS(0);

}