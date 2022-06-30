#include <iostream>
#include <vector>

using namespace std;

// typedef struct tree{
//     int data;
//     tree_node* left_child;
//     tree_node* right_child;
// }tree_node;

vector<int> a{1,9,3,8,4,5,5,9,10,3,4,5};
vector<int> segment(32,-1);

int init(int start , int end , int index){
    
    if(start == end) return segment[index] = a[start];

    int mid = (start + end) / 2;

    return segment[index] = init(start , mid , index * 2) + init(mid + 1 , end , index* 2 + 1);
}

int sum(int start , int end , int index , int left , int right){

    // 범위 밖
    if(start > right || end < left) return 0;

    // 범위 안
    if(start <= left && end >= right) return segment[index];

    int mid = (start + end ) / 2;
    
    return segment[index] = sum(start , mid , index * 2 , left , right) + sum(mid+ 1 , end , index*2 + 1 , left , right);
    
}

void update(int start , int end, int index , int a_index ,int diff){

    // 범위 밖

    if(a_index < start || a_index > end) return;

    // 범위 안
    
    segment[index] += diff;

    int mid = (start + end) / 2;

    update(start , mid , index * 2 , a_index , diff);
    update(mid+1 , end , index*2 + 1 , a_index , diff);

}

void print(){
    for(auto x : segment) cout << x << ' ';
}

int main(int argc , char** argv){

    init(0,11,1);
    print();


}