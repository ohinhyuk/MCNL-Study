#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<string> v;

int N,K ;
int ans = 0;

int check(vector<bool> alphabet){
    bool iscount ;
    int result =0 ;
    for(int i = 0 ; i < v.size(); ++i){
        iscount = true;
            for(int k = 0 ; k < v[i].size(); ++k){
                if(!alphabet[v[i][k] - 'a']){iscount = false;break;} 
            }
        if(iscount) result++;
    }
    return result;
}

void DFS(int idx ,vector<bool> alphabet,int true_num){
    
    if(true_num == K){     
        ans = max(check(alphabet) , ans);
        return ;
    }

    for(int i = idx; i < 26 ; ++i){
        if(alphabet[i] == true) continue;
        alphabet[i] = true;
        DFS(i+1,alphabet,true_num+1);
        alphabet[i] = false;
    }

}

int main(int argc, char** argv){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<bool> alphabet(26,false);
    
    alphabet[0] = true;
    alphabet[2] = true;
    alphabet[8] = true;
    alphabet[13] = true;
    alphabet[19] = true;
    

    string s;

    cin >> N >> K;

    if(K >= 5){
        for(int i = 0 ; i < N ; ++i){ 
            cin >> s;
            v.push_back(s);
        }

        DFS(0,alphabet,5);
    }
    cout << ans << "\n";
}