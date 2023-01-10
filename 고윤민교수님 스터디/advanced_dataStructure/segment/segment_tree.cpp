#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct tree_node{
    int data = 0;
    tree_node* left_child = nullptr ;
    tree_node* right_child = nullptr ;

    // tree_node(int k, tree_node* l , tree_node* r){
    //     data = k;
    //     left_child = l;
    //     right_child = r;
    // }
    // tree_node(int k) : data(k), left_child(nullptr), right_child(nullptr){}
    // tree_node(){ data = 0; left_child=nullptr;right_child=nullptr;}
    // ~tree_node(){}
};

class segment_sum{

private:
    tree_node* root = nullptr;
    int length;

public:
    
    tree_node* init(const vector<int>& a , tree_node* node , int start , int end){
        
        
        if(!node) node = new tree_node;
        
        
        // node->left_child = new tree_node;
        // node->right_child = new tree_node;
        
        if(start == end){
            node->data = a[start];
            return node;
        }

        int mid = (start + end)/2;
        
        node->left_child = init(a,node->left_child , start , mid);
        node->right_child = init(a,node->right_child, mid+1,end);
        node->data = node->left_child->data + node->right_child->data;
        
        // node->data = (init(a,node->left_child,start,mid)->data + init(a,node->right_child,mid+1,end)->data);
        return node;

    }

    void init(const vector<int> & a){
        length = a.size();
        root = init(a,root,0,length-1);
    }

    int sum(int f_left , int f_right ,tree_node* node ,int start , int end ){

        if(f_left > end || f_right < start) return 0;

        if(f_left <= start && f_right >= end) return node->data;

        int mid = (start + end) / 2;

        return sum(f_left , f_right , node->left_child , start , mid) + sum(f_left , f_right , node->right_child , mid+1 , end);
    }


    int sum(int f_left , int f_right){
        return sum(f_left , f_right , root , 0 , length-1);
    }

    void update(int index , int diff , tree_node* node ,int start , int end){
        
        if(index < start || index > end) return ;

        int mid = (start + end)/2;

        node->data += diff;

        if(node->left_child) update(index , diff , node->left_child , start , mid);
        if(node->right_child) update(index , diff , node->right_child , mid+1 , end);
        
    }

    void update(int index , int newValue){
        int diff = newValue - sum(index,index);
        update(index , diff , root , 0 , length-1);
    }

    void print_tree_BFS(){

        tree_node* node;
        queue<tree_node*> que;

        que.push(root);

        cout << "Print : ";
        
        while(!que.empty()){
            node = que.front();
            que.pop();

            cout << node->data << ' ';

            if(node->left_child) que.push(node->left_child);
            if(node->right_child) que.push(node->right_child);
        }

        cout << endl;
    }
};


int main(int argc , char** argv){
    segment_sum segment;
    vector<int> a {1,9,3,8,4,5,5,9,10,3,4,5};
    
    segment.init(a);
    
    segment.print_tree_BFS();

    cout << segment.sum(4,8);
     
    segment.update(3,10);
    segment.print_tree_BFS();

}