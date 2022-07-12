/* Map STL Inplementataion

#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################


I Implemented . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  ◼ insert(): Node(key, value) Insertion. ex) insert(pair) or m[key] = value
  ◼ erase(): Node Deletion using key.
  ◼ find(): Searching value using key.
  ◼ begin(): begin iterator
  ◼ end(): end iterator
  ◼ Print() : Using 

I Used . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  ◼ Template
  ◼ Operator Overloading
  ◼ Pair
  ◼ Iterator Implementation
  ◼ Red - Black Tree


#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################
*/

#include <iostream>
//#include <queue>

using namespace std;


// Node Structure
// {key, value} + color + {L,R,P}

template <typename T1, typename T2>     // Template for key, value
struct Tree_node{
    T1 key;         // Map key
    T2 value;       // Map value
    char color;     // Red-Black Color

    Tree_node<T1,T2>* left;         // pointer Left
    Tree_node<T1,T2>* right;        // pointer Right
    Tree_node<T1,T2>* parent;       // pointer Parent
    
    // Node Constructor
    Tree_node(){color='R';left = nullptr;right=nullptr;parent=nullptr;}     
    Tree_node(T1 k , T2 v , char c , Tree_node* l , Tree_node* r , Tree_node* p){key = k;value = v;color = c; left =l; right =r;parent=p;}
    
    // Node Destructor
    ~Tree_node(){}
};


// Iterator Class Implementation for map
// operator overloading : ++ , * , == , != 

template<typename T1, typename T2>
class MyIterator{

private:
    Tree_node<T1,T2>* cur;

public:
    
    // MyIterator Constructor

    MyIterator(Tree_node<T1,T2>*p = nullptr)
        :cur(p){}


    // operator++ overloading

    MyIterator& operator++(){
        // If it has right child
        if(cur->right){
            Tree_node<T1,T2>* search = cur->right;
            while(search -> left) search = search ->left; // find minimum in right subtree.
            cur = search;
        }

        // No Right child
        else{
            
            // cur == root + No right child (no parent)
            if(!cur->parent) cur = nullptr;

            // cur has parent
            else{
                Tree_node<T1,T2>* search= cur->parent;
                
                // Checking cur is either left child or right child
                while(cur == search->right){
                    cur = search;
                    if(search->parent) search = search->parent;
                    else{
                        cur = nullptr;
                        return *this;
                    }
                }
                cur = search;
            }
        }
        return *this;   // return iterator
    }   

    // Operator '*' overloading for Get cur
    Tree_node<T1,T2>* operator*(){
        return cur; 
    }

    // Operator '==' overloading for comparation.
    bool operator==(const MyIterator &ref){
        return cur == ref.cur;
    }

    //Operator '!=' overloading for comparation.
    bool operator!=(const MyIterator &ref){
        return cur != ref.cur;
    }
};


// MyMap Class 
// STL Map implementation using Red - Black Tree

template <typename T1, typename T2>
class MyMap{    
private:

    Tree_node<T1,T2>* root;     // RB Tree
    T1 key;                     // Key
    int num;                    // size of tree

public:
    MyMap(){root= new Tree_node<T1,T2>(); num=0;};          // Constructor
    ~MyMap(){};                                             // Destructor

    // Operator '[]' overloading for index access
    // m[key] = value   (==)    m.insert(make_pair(key,value))
    T2& operator[](T1 key){
    
        MyMap<T1,T2>::iterator iter;    // using iterator
    
        iter = find(key);               

        T2 value;                       // garbage value

        // There isn't Key in map , then insert
        if(iter == end()){
            insert(make_pair(key,value));
           
            iter = find(key);
            
        }

        return (*iter)->value;  // return iter's value for modification.
    }

    // Map Functions

    void insert(const pair<T1,T2> & in);
    void erase(T1 out);
    void modify(Tree_node<T1,T2>* modf);
    
    
    // Iterator for MyMap and it's Functions.
    
    // Iterator typedef
    typedef MyIterator<T1,T2> iterator;

    // Functions of Iterator

    iterator begin(){
        Tree_node<T1,T2>* search = root;
        while(search->left) search = search->left;
        
        return iterator(search);
    }

    iterator end(){
        return iterator(nullptr);
    }

    iterator find(T1 key){
        MyMap<string, int>::iterator iter;

        for(iter = begin(); iter!=end(); ++iter){
            if((*iter)->key == key) return iterator(*iter);
        }

        return end();
    }

    // void print(Tree_node<T1,T2>* temp);
    // void print();

};

// Print Map Function
// Print map function using MyIterator

template<typename T1 , typename T2>
void print_map(MyMap <T1,T2> m){
    MyMap<string,int>::iterator iter;

    for(iter = m.begin(); iter!=m.end(); ++iter){
        cout << (*iter)->key << ": " << (*iter)->value << '\n';
    }
}


// LL_Rotation for modify function
// Part of Insertion Function

template<typename T1 , typename T2>
void LL_Rotation(Tree_node<T1,T2>* node){
    
    //node == parent
    
    //grand parent change
    node->parent->left = node ->right;
    node->parent->color = 'R';

    // parent->right change
    if(node-> right) node->right->parent = node->parent;

    // parent change
    node->color = 'B';
    node->right = node->parent;
    node-> parent = node->parent->parent;
    if(node->parent) node->parent->left = node;

    //grand parent change(rest part)
    node->right->parent = node;
}


// RR_Rotation for modify function
// Part of Insertion Function

template<typename T1 , typename T2>
void RR_Rotation(Tree_node<T1,T2>* node){
    
    //node == parent

    //grand parent change
    node->parent->right = node ->left;
    node->parent->color = 'R';
    // parent->right change
    if(node->left) node->left->parent = node->parent;

    // parent change
    node->color = 'B';
    node->left = node->parent;
    node-> parent = node->parent->parent;
    if(node->parent) node->parent->right = node;
    
    
    //grand parent change(rest part)
    node->left->parent = node;

}

// Modify Function for Insert Function
// Part of Insertion Function

template<typename T1, typename T2>
void MyMap<T1,T2>::modify(Tree_node<T1,T2>* modf){
    
    // If root -> color = 'Black'
    if(root == modf) modf->color = 'B';

    // Else cases
    else{
        Tree_node<T1,T2>* parent = modf->parent;    // Parent
        if(parent->color =='B') return;             // If parent is Black Node
        
        Tree_node<T1,T2>* gr_parent = parent->parent;   // Grand Parent
        
        // If parent is Left child of Grand Parent
        if(parent == gr_parent->left){                  
            
            // If Uncle is Red Node
            // Color change + recursive
            if(gr_parent->right && gr_parent->right->color=='R'){
                gr_parent->right->color = 'B';
                gr_parent->color = 'R';
                parent->color = 'B';
                modify(gr_parent);
            }

            // If Uncle is Black Node
            else{

                // LL Case
                if(modf == parent->left){ 
                    if(gr_parent == root) root = parent;
                    LL_Rotation(parent);
                    }

                // LR Case
                else if(modf == parent->right){
                    // grand parent change
                    gr_parent->left = modf;

                    //parent change
                    parent->right = modf->left;
                    parent->parent = modf;

                    //child change
                    modf->left = parent;
                    modf->parent = gr_parent;
                    
                    if(gr_parent == root) root = modf;
                    LL_Rotation(modf);
                }
            }
        }

        // If parent is Right child of Grand Parent
        else if(parent == gr_parent ->right){
            
            // If Uncle is Red Node
            // Color change + recursive
            if(gr_parent->left && gr_parent->left->color =='R'){
                gr_parent->left->color = 'B';
                gr_parent->color = 'R';
                parent->color = 'B';
                modify(gr_parent);
            }
            
            // If Uncle is Black Node
            else{
                // RR Case
                if(modf == parent->right) {
                    if(gr_parent == root) root = parent;
                    RR_Rotation(parent);
                }
                
                // RL Case
                else if(modf == parent->left){
                    // grand parent change
                    gr_parent->right = modf;

                    //parent change
                    parent->left = modf->right;
                    parent->parent = modf;

                    //child change
                    modf->right = parent;
                    modf->parent = gr_parent;

                    if(gr_parent == root) root = modf;
                    RR_Rotation(modf);
                }
            }
        }
    }
}

// Insertion Function
// It is supported by Modify Function , RR_rotation Function , LL_rotation Function.
// Insertion -> Modification -> Rotation

template<typename T1 , typename T2>
void MyMap<T1,T2>::insert (const pair<T1,T2> & in){
    
    // First Node
    if(num == 0){
        root->key = in.first; root->value = in.second;
        num++;
        modify(root);
    }
    // Else Nodes
    else{

        // Finding location + Insertion
        Tree_node<T1,T2>* search = root;
        
        while(search){
        
        if(search->key == in.first) return;

        else if( search->key < in.first){
            if(!search->right){ search->right = new Tree_node<T1,T2>(in.first,in.second,'R',nullptr,nullptr,search); break;}
            search = search-> right;
        } 
        else if(search->key > in.first){
            
            if(!search->left){ search->left = new Tree_node<T1,T2> (in.first,in.second,'R',nullptr,nullptr,search); break;}
            search = search->left;
        }
        
        }
        
        // Num Increase
        num++; 
        
        // Modification
        if(search->left && in.first == search->left->key) modify(search->left);
        else if(search->right && in.first == search->right->key) modify(search->right);

    }

}

// Erase Function

template<typename T1 , typename T2>
void MyMap<T1,T2>::erase (T1 out){

}

// template <typename T1, typename T2>
// void MyMap<T1,T2>:: print(){
    
//     map->left.print();
//     //cout <<;
//     map->right.print();
// }


// template<typename T1 , typename T2>
// void MyMap<T1,T2>::print(Tree_node<T1,T2>* temp){

//     if(!temp) return;
    
//     print(temp->left);
//     cout << temp->key << temp->value << endl;
//     print(temp->right);
    
// }
// template<typename T1 , typename T2>
// void MyMap<T1,T2>::print(){
//     Tree_node<T1,T2>* temp;
//     queue<Tree_node<T1,T2>*> q;
    
//     q.push(root);
 
//     while(!q.empty()){
//         temp = q.front();
//         q.pop();
        
//         cout << temp->key << "  " << temp->value << " " << temp->color << endl;
//         if(temp-> parent) cout <<"parent : "<<  temp->parent->key << endl;

//         if(temp->left) q.push(temp->left);
//         if(temp->right) q.push(temp->right);
//     }

//     // print(root);
// }


int main(int argc, char** argv){
    
    MyMap <string,int> m;
    
    cout << "** First Step **\n";
    m.insert(make_pair("Global",10));
    m.insert(make_pair("Handong",30));
    m.insert(make_pair("CSEE",20));
    m.insert(make_pair("MCNL",15));
    print_map(m);

    cout << "\n** Second Step ** \n";
    m["Pohang"] = 50;
    m["Korea"] = 60;
    print_map(m);

    cout << "\n** Third Step ** \n";
    m["CSEE"] = 100;
    m.erase("Global");
    print_map(m);

    cout << "\n** Fourth Step **\n";
    string key = "MCNL";
    if(m.find(key) != m.end()){
        cout<< key << " Exists! \n";
    } else{
        cout << key << " des not exist! \n";
    }

    cout << "\n** Fifth Step **\n";
    key = "Yunmin";
    if (m.find(key) != m.end()){
        cout << key << " Exists! \n";
    } else{
        cout << key << " does not exist! \n";
    }

    return 0;
    // my.insert(make_pair(10,"AA" ));
    // my.insert(make_pair(20,"AA"));
    // my.insert(make_pair(30 ,"AA"));
    // my.insert(make_pair(40,"AA" ));
    // my.insert(make_pair(50,"AA"));
    // my.insert(make_pair(60 ,"AA"));
    // my.insert(make_pair(70,"AA" ));
    // my.insert(make_pair(80,"AA"));
    // my.insert(make_pair(90 ,"AA"));
    // my.insert(make_pair(100,"AA" ));
    // my.insert(make_pair(15,"AA"));
    // my.insert(make_pair(25 ,"AA"));
    // my.insert(make_pair(35,"AA" ));
    // my.insert(make_pair(45,"AA"));
    // my.insert(make_pair(55 ,"AA"));
    // my.insert(make_pair(65,"AA"));
    // my.insert(make_pair(75 ,"AA"));
    // my.insert(make_pair(85,"AA" ));
    // my.insert(make_pair(95,"AA"));
    
    // my["AB"]= 20;
    // my["AA"]= 100;
    // MyMap<int,string>::iterator iter;

    // print_map();

}