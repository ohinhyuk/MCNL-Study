#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <set>

using namespace std;

struct possible{
    int x;
    int y;
    deque<int> v;
};

bool success = false;
int sudoku[9][9];
deque<possible> possible_v;

bool check_all_b(){

    for(int i = 0 ; i < possible_v.size() ; ++i){
        possible p = possible_v[i];
        
        int x = p.x;
        int y = p.y;

        for(int i = 0 ; i < 9 ; ++i){
            if( i!= y && sudoku[x][y] == sudoku[x][i]) return false;
            if( i!= x && sudoku[x][y] == sudoku[i][y]) return false;
        }

        for(int i = (x/3)*3 ; i < (x/3)*3 +3; ++i ){
            for(int j = (y/3)*3 ; j < (y/3)*3 +3 ; ++j){
                if( (i != x || j!=y) && sudoku[x][y] == sudoku[i][j]) return false;
            }
        }

    }

    return true;
    
}


void print_s(){
    for(int i = 0 ; i < 9 ; ++i){
        for(int j = 0 ; j < 9 ; ++j){
            cout << sudoku[i][j] << ' ';
        }
        cout << "\n";
    }
}

void DFS(int n){

    if(success) return;
    if(n == possible_v.size()){
        if(check_all_b()){
            for(int i = 0 ; i < 9 ; ++i){
                for(int j = 0 ; j < 9 ; ++j){
                    cout << sudoku[i][j] << ' ';
                }
            cout << "\n";
            }
            success = true;
            // exit(-1);
        }
        return ;
    }
    
    possible p = possible_v[n];
    
    int x = p.x;
    int y = p.y;

    for(int i = 0 ; i < p.v.size(); ++i){
        sudoku[x][y] = p.v[i];
        
        // print_s();
        // cout << x << y << n << endl;
        DFS(n+1);
    }
    sudoku[x][y] = 0;
}

void check(int x , int y){
    possible p;
    
    p.x = x;
    p.y = y;
    
    for(int num = 1 ; num <= 9 ; num++){
        bool exist = false;

        for(int i = 0 ; i < 9 ; ++i){
            if(sudoku[i][y] == num) exist = true;
            if(sudoku[x][i] == num) exist = true;
        }

        for(int i = (x/3) * 3 ; i < (x/3)*3+3 ; ++i){
            for(int j = (y/3) * 3 ; j < (y/3)*3 +3 ; ++j){
                if(sudoku[i][j]==num) exist = true;
            }
        }

        if(!exist) p.v.push_back(num);
    }
    
    if(!p.v.empty()) possible_v.push_back(p);
}

int main(int argc ,char** argv){
    
    for(int i = 0 ; i < 9 ; ++i){
        for(int j = 0 ; j < 9 ; ++j){
            cin >> sudoku[i][j];
        }
    }

    for(int i = 0 ; i < 9 ; ++i){
        for(int j = 0 ; j < 9 ; ++j){
            if(sudoku[i][j] == 0){
                check(i,j);
            }
        }
    }

    DFS(0);

}







bool check_all(){

    set<int> duplication;

    for(int fix = 0; fix < 9 ; ++fix){
        for(int j = 0 ; j < 9 ; ++j){
            duplication.insert(sudoku[fix][j]);
        }
        // cout << duplication.size() << endl;
        if(duplication.size() != 9) return false;

        duplication.clear();

        for(int i = 0 ; i < 9 ; ++i){
            duplication.insert(sudoku[i][fix]);
        }

        cout << duplication.size() << endl;
        if(duplication.size() != 9) return false;

        duplication.clear();

    }

    for(int jump_x = 0 ; jump_x < 9 ; jump_x+=3){
        for(int jump_y = 0 ; jump_y < 9 ; jump_y+=3){
            for(int i = 0 ; i < 3; ++i ){
                for(int j = 0 ; j < 3 ; ++j){
                    duplication.insert(sudoku[i+jump_x][j+jump_y]);
                }
            }
            if(duplication.size()!=9) return false;
            duplication.clear();
        }
    }
    
    return true;
}