#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> ans;
vector<int> height;

void DFS (int i , int total , vector<int> Nanjang ) {

    if(i == 9){
        if(total ==100 && Nanjang.size()==7){
            ans = Nanjang;
            return ;
        }
        return ;
    }
    else if(i < 9){
        DFS(i+1 , total , Nanjang);
        Nanjang.push_back(height[i]);
        DFS(i+1 , total + height[i] , Nanjang);
    }

}

int main(int argc , char** argv){
vector<int> Nanjang;
    int temp;

    for(int i = 0 ; i <9 ; ++i){
        cin >> temp;
        height.push_back(temp);
    }

    DFS(0,0,Nanjang);

    sort(ans.begin() , ans.end());

    for(int x : ans){
        cout << x << '\n';
    }

}