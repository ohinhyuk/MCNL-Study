#include <iostream>

using namespace std;

struct node{
    int data;
    node* left ;
    node* right ;
};

class Tree{

private :
    node* root;
    int C=-1 ;
public:

    Tree(){};
    ~Tree(){ delete root; };

    void insert(int X , node* N){
        
        node* temp = new node{X,nullptr,nullptr};

        C++;
        
        if(C == 0){    
            root = temp;   
        }
        else{
            if(X < N->data){
                if(!N->left){
                    N->left = temp;
                }
                else insert(X, N->left);
            }
            else{
                if(!N->right){
                    N->right = temp;
                }
                else{
                    insert(X , N->right);
                } 
            }
        }
    }

    void insert(int X){
        insert(X,root);
    }
    
    int get_C(){
        return C;
    }

};


int main(int argc , char** argv){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N , insert_key;
    Tree t;

    cin >> N;

    for(int i = 0 ; i < N ; ++i){
        cin >> insert_key;
        t.insert(insert_key);
        cout << t.get_C() << "\n";
    }
}