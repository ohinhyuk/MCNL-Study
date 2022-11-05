#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int top[1001];

int find(int a){
    if(top[a] == a) return a;
    
    return top[a] = find(top[a]);
}

void union_(int a , int b){
    a = find(a);
    b = find(b);
    if(a < b){
        top[b] = a;
    }
    else{
        top[a] = b;
    }
}

int main(int argc , char** argv){

    int N , M ,start , end;
    int cnt = 0;

    cin >> N >> M;

    for(int i = 1 ; i <= N ; ++i){
        top[i] = i;
    }

    for(int i = 0 ; i < M ; ++i){
        cin >> start >> end;
        
        union_(start,end);
    }

    for(int i = 1 ; i <= N ; ++i){
        if( i == top[i]) cnt++;
    }
    cout << cnt;

}