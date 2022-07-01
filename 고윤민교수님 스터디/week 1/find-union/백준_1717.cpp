#include <iostream>

using namespace std;

class Set{

private :
    int* root;

public :    
    Set(int n){ 
        root = new int[n+1];
        for(int i = 0 ; i < n+1 ; ++i) root[i] = i;     
    }

    ~Set(){ delete[] root; };
    
    int find(int num);
    void union_(int num1 , int num2);
    void check_(int num1, int num2);

};

int Set::find(int num){
    if(root[num] == num) return num;

    return root[num]= find(root[num]);
}

void Set::union_(int num1 , int num2){
    num1 = find(num1);
    num2 = find(num2);

    root[num2] = num1;
}

void Set::check_(int num1 , int num2){
    if(find(num1) == find(num2)) cout << "YES\n";
    else cout << "NO\n";
}

int main(int argc, char** argv){
    
    cin.tie(NULL);cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int n , m , a , b , zero_or_one;

    cin >> n >> m ;

    Set set(n);


    for(int i = 0; i < m ; ++i){
        
        cin >> zero_or_one >> a >> b;

        if(zero_or_one == 0) set.union_(a,b);
        else if(zero_or_one == 1) set.check_(a,b);
    
    }

    return 0;
}