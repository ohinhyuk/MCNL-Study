#include <iostream>

using namespace std;

#define NUMBERS 10

struct union_find{

    int root[NUMBERS];
    
    union_find(){ for(int i = 0 ; i < NUMBERS ; ++i) root[i] = i;};
    ~union_find(){};

    int find(int num);
    void union_(int num1, int num2);
};

int union_find::find(int num){

    if(root[num]==num) return num;

    return find(root[num]);
}

void union_find::union_(int num1, int num2){
    
    num1 = find(num1);
    num2 = find(num2);

    root[num2] = num1;

}

int main(int argc , char** argv){

    
}