#include <iostream>

using namespace std;

// template <typename T1, typename T2>
struct Treenode{

    // T1 data;
    Treenode* left;
    Treenode* right;

};

template <typename T1, typename T2>
class MyMap{
private:
    T1 key;
    T2 value;
    Treenode* map;


public:

    void print();

};

template <typename T1, typename T2>
void MyMap<T1,T2>:: print(){
    
    map->left.print();
    //cout <<;
    map->right.print();
}

int main(int argc, char** argv){

}