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

using namespace std;


// Node Structure   ---------------------------------------------------------------------------------------------------------------------
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


// ---------------------------------------------------------------------------------------------------------------------------------------


// Iterator Class Implementation for map -------------------------------------------------------------------------------------------------
// operator overloading : ++(prefix) , * , == , != 
 
template<typename T1, typename T2>
class MyIterator{

private:
    Tree_node<T1,T2>* cur;

public:
    
    // MyIterator Constructor

    MyIterator(Tree_node<T1,T2>*p = nullptr)
        :cur(p){}

    // operator++ overloading
    // Finding node having next min key

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

// ---------------------------------------------------------------------------------------------------------------------------------------

// MyMap Class ---------------------------------------------------------------------------------------------------------------------------
// STL Map implementation using Red - Black Tree

template <typename T1, typename T2>
class MyMap{    
private:

    Tree_node<T1,T2>* root;     // RB Tree
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
    void modify_erase(Tree_node<T1,T2>* p, char LR);
    
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


    // Print for Checking
    
    // void print();                            // Level Order(BFS) using Queue
    // void print(Tree_node<T1,T2>* temp);      // Inorder
};

// ---------------------------------------------------------------------------------------------------------------------------------------


/*

// Print for Checking----------------------------------------------------------------------------------------------------------------------


// Inorder Print

template<typename T1 , typename T2>
void MyMap<T1,T2>::print(Tree_node<T1,T2>* temp){

    if(!temp) return;
    
    print(temp->left);
    cout << temp->key << temp->value << endl;
    print(temp->right);
    
}

// Levelorder Print

template<typename T1 , typename T2>
void MyMap<T1,T2>::print(){

    
    // print(root); // Inorder

    Tree_node<T1,T2>* temp;
    queue<Tree_node<T1,T2>*> q;
    
    q.push(root);
 
    while(!q.empty()){
        temp = q.front();
        q.pop();
        
        cout << "Key : " << temp->key << " value : " << temp->value << " color :" << temp->color  ;
        if(temp-> parent) cout <<" parent : "<<  temp->parent->key << endl;

        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
    }

}

// ---------------------------------------------------------------------------------------------------------------------------------------

*/




// Print Map Function
// Print map function using MyIterator
// Acsending

template<typename T1 , typename T2>
void print_map(MyMap <T1,T2> m){
    MyMap<string,int>::iterator iter;

    for(iter = m.begin(); iter!=m.end(); ++iter){
        cout << (*iter)->key << ": " << (*iter)->value << '\n';
    }
}



// << Rotation >> ------------------------------------------------------------------------------------------------------------------------


// LR_Rotation for modify function
template<typename T1, typename T2>
void LR_Rotation(Tree_node<T1,T2>* node){

    // node == parent
    // node_r == parent->right child
    Tree_node<T1,T2>* node_r = node->right;

    //grand parent change
    node->parent->left = node_r;
	
    // parent->left child change
	node_r->parent = node->parent;
    
    // parent change
	node-> parent = node_r;
	
    // parent->left child -> right child change
    node->right = node_r->left;
	if(node->right) node->right->parent = node;
    
    // parent->left child change
	node_r->left = node;

}

// LL_Rotation for modify function

template<typename T1 , typename T2>
void LL_Rotation(Tree_node<T1,T2>* node){
    
    // node is parent
    
    //grand parent change
    node->parent->left = node ->right;

    // parent->right change
    if(node-> right) node->right->parent = node->parent;

    // parent change
    node->right = node->parent;
    node-> parent = node->parent->parent;
    if(node->parent){
        if(node->parent->right == node->right) node->parent->right = node;
        if(node->parent->left == node->right) node->parent->left = node;
    } 

    //grand parent change(rest part)
    node->right->parent = node;
}

// RL_Rotation Function for modify function

template<typename T1, typename T2>
void RL_Rotation(Tree_node<T1,T2>* node){

    // node == parent
    // node_l == parent->left child
    Tree_node<T1,T2>* node_l = node->left;

    //grand parent change
    node->parent->right = node_l;
	
    // parent->left child change
	node_l->parent = node->parent;
    
    // parent change
	node-> parent = node_l;
	
    // parent->left child -> right child change
    node->left = node_l->right;
	if(node->left) node->left->parent = node;
    
    // parent->left child change
	node_l->right = node;

}


// RR_Rotation for modify function

template<typename T1 , typename T2>
void RR_Rotation(Tree_node<T1,T2>* node){
    
    // node is parent

    //grand parent change
    node->parent->right = node ->left;
    // node->parent->color = 'R';
    // parent->right change
    if(node->left) node->left->parent = node->parent;

    // parent change
    // node->color = 'B';
    node->left = node->parent;
    node-> parent = node->parent->parent;
    if(node->parent){
        if(node->parent->right == node->left) node->parent->right = node;
        if(node->parent->left == node->left) node->parent->left = node;
    }
    
    
    //grand parent change(rest part)
    node->left->parent = node;

}

// ---------------------------------------------------------------------------------------------------------------------------------------------------






// << Insertion >> -----------------------------------------------------------------------------------------------------------------------------------



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
                    parent->parent->color = 'R';
                    parent->color = 'B';
                    LL_Rotation(parent);
                    
                    }

                // LR Case
                else if(modf == parent->right){
                    
                    LR_Rotation(parent);
                    
                    if(gr_parent == root) root = modf;
                    modf->parent->color='R';
                    modf->color='B';

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
                    parent->parent->color = 'R';
                    parent->color = 'B';
                    RR_Rotation(parent);
                }
                
                // RL Case
                else if(modf == parent->left){
                    
                    RL_Rotation(parent);

                    if(gr_parent == root) root = modf;
                    
                    modf->parent->color = 'R';
                    modf->color = 'B';
                    
                    RR_Rotation(modf);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// << Erase >> ---------------------------------------------------------------------------------------------------------------------------


// Erase Function
// [ modify_erase , RR_Rotation , LL_Rotation ] functions are used.
// Erase -> modify -> rotate

template<typename T1 , typename T2>
void MyMap<T1,T2>::erase (T1 out){
    
    Tree_node<T1,T2>* search = root;    // pointer searching delete node (having key 'out')
    Tree_node<T1,T2>* replace;          // pointing replace node
    Tree_node<T1,T2>* del_parent;       // parent of search pointer
    
    char del_color;                     // Color of delete node
    char LR;                            // Whether the delete node is left child or right child

    
    while(search){

        // Finding delete node
        if(out > search->key) search = search->right;
        else if(out < search->key) search = search->left;

        // Found
        else{

        // Delete

        // Case 1 : NO Child
        
            if(!search->left && !search->right){
                
                num--;

                del_color = search->color; // color information
                
                if(search==root) delete search; // if root
                else{
                    del_parent = search->parent;    // parent of delete node

                    // LR information
                    if(del_parent->right == search) { del_parent->right = NULL;  LR = 'R';}
                    else if(del_parent->left == search){ del_parent->left = NULL;  LR = 'L';}

                    delete search;
                    
                }

                
                // if delete node is Red -> Pass

                // if delete node is black -> Modify_erase   (Because replace node is NIL -> color is black)
                if(del_color == 'B') modify_erase(del_parent , LR); 


                break;
            }

        // Case 2-1 : 1 Child(left)
        
            else if(search->left && !search->right){

                num--;

                replace = search->left;     // replace node
                del_color = search->color;  // color information

                // if root
                if(search==root){
                    root = replace;
                    root->parent = nullptr;
                    delete search;
                }
                // Else
                else{
                    del_parent = search->parent;    // parent of delete node

                    // LR information
                    if(del_parent->left == search) {del_parent->left = replace; LR = 'L';}
                    else if(del_parent->right == search) {del_parent-> right = replace;  LR ='R';}

                    replace->parent = search->parent;

                    delete search;
                }

                
                // if color of delete node is Red -> Pass

                // if color of delete node is Black
                if(del_color == 'B'){
                    
                    // if replace node color is Red -> change to black
                    if(replace->color =='R') replace->color = 'B';
                    
                    // if replace node color is Black -> modify_erase
                    else if(replace->color == 'B') modify_erase(del_parent , LR);
                        
                    
                }

                break;
            }

        // Case 2-2 : 1 Child(right)
        
            else if(!search->left && search->right){
                
                num--;

                replace = search->right;        // replace of delete node
                del_color = search->color;      // color information

                // if root
                if(search==root){
                    root = replace;
                    root->parent = nullptr;
                    delete search;
                }
                // Else
                else{
                    del_parent = search->parent;    // Parent of delete node

                    // LR information
                    if(del_parent->left == search){ del_parent->left = replace;  LR = 'L';}         
                    else if(del_parent->right == search){ del_parent->right = replace; LR = 'R';} 

                    replace->parent = search->parent;

                    delete search;
                }

                
                // if color of delete node is Red -> Pass

                // if color of delete node is Black
                if(del_color == 'B'){

                    // if replace node color is Red -> change to black
                    if(replace->color =='R') replace->color ='B';
                    
                    // if replace node color is Black -> modify_erase
                    else if(replace ->color == 'B') modify_erase(del_parent , LR);

                }

                break;
            }

        // Case 3 : 2 Child (left & right)

            else{

                // replace node is maximum of left subtree                
                replace = search->right;
                while(replace->left) replace = replace->left;
                
                T1 key_temp = replace->key;
                T2 value_temp = replace->value;
                
                erase(replace->key);        // recursive erase

                // change delete node to replace node
                search->key = key_temp;
                search->value = value_temp;

            }

        }
    }
}

// Isblack Function
// For modify_erase function
// NIL or node->color =='B' -> True

template<typename T1, typename T2>
bool isblack(Tree_node<T1,T2>* node){
    return (!node || (node && node->color =='B') );
}

// Modify_Erase Function
// recoloring Nodes and modifying Tree After Delete
// p : parent of delete node
// s : sibling of delete node
// s_l : left child of sibling
// s_r : right child of sibling

// if LR is 'L' -> There are 5 cases
// if LR is 'R' -> There are 5 cases (Symmetric to the case above)

template<typename T1 , typename T2>
void MyMap<T1,T2>::modify_erase(Tree_node<T1,T2>* p, char LR){


// Delete node is left child of p
    if(LR =='L'){
    
// Case 1 :
    // p is Red 
    // s is black
    // s_l & s_r is black
    
    // << Solution >>
    // Recoloring

        if(p->color == 'R' && (p->right && isblack(p->right)) && isblack(p->right->left) && isblack(p->right->right) ){
            p->color = 'B';
            p->right->color = 'R';
        }

// Case 2 :
    // p is black
    // s is black
    // s_l & s_r & black

    // << Solution >>
    // Recoloring
    // recursive

        else if(p->color =='B' && (p->right && isblack(p->right)) && isblack(p->right->left) && isblack(p->right->right) ){
            p->right->color = 'R';
            if(p->parent){
                if(p->parent->left && p->parent->left == p) modify_erase(p->parent, 'L');
                else if(p->parent->right && p->parent->right == p) modify_erase(p->parent, 'R');
            }
            
        }
// Case 3 :
    // s is black
    // s_r is Red

    // << Solution >>
    // RR rotation + Recoloring

        else if( (p->right && isblack(p->right)) && (p->right->right && !isblack(p->right->right)) ){
            
            Tree_node<T1,T2>* s = p->right;
            
            if(p == root) root = s; // if p is root , root change


            s->color = p->color;
            p->color = 'B';
            s->right->color = 'B';

            RR_Rotation(s);

        }

// Case 4 :
    // s is Black
    // s_l is Red
    
    // << Solution >>
    // RL rotation + Recoloring

        else if( (p->right && isblack(p->right)) && (p->right->left && p->right->left->color =='R') ){
            
            Tree_node<T1,T2>* s = p->right;
            Tree_node<T1,T2>* s_l = s->left;

            if(p == root) root = s_l; // if p is root , root change

            // Step 1 : rotate to right

            s_l->color = 'B';
            s->color = 'R';
            
            RL_Rotation(s);

            // Step 2 : RR rotation(Case 3)

            s = s_l;

            s->color = p->color;
            p->color = 'B';
            s->right->color = 'B';

            RR_Rotation(s);

        }

// Case 5 :
    // s is Red

    // << Solution >>
    // RR rotation + Recursive
    
        else if( (p->right && p->right->color=='R') ){
            
            if(p == root) root = p->right;

            p->color = 'R';
            p->right->color = 'B';

            RR_Rotation(p->right);
            modify_erase(p,'L');
        }

    }
    
// Delete node is right child of p
    else if(LR = 'R'){

// Case 1 : Recoloring

        if(p->color == 'R' && (p->left && isblack(p->left)) && isblack(p->left->left) && isblack(p->left->right) ){
            p->color = 'B';
            p->left->color = 'R';
        }

// Case 2 : Recoloring + recursive

        else if(p->color =='B' && (p->left && isblack(p->left)) && isblack(p->left->left) && isblack(p->left->right) ){
            p->left->color = 'R';
            if(p->parent){
                if(p->parent->left && p->parent->left == p) modify_erase(p->parent, 'L');
                else if(p->parent->right && p->parent->right == p) modify_erase(p->parent, 'R');
            }
        }

// Case 3 : LL rotation

        else if( (p->left && isblack(p->left)) && (p->left->left && p->left->left->color =='R') ){
            
            Tree_node<T1,T2>* s = p->left;
            
            if(p==root) root = s;

            s->color = p->color;
            p->color = 'B';
            s->left->color = 'B';

            LL_Rotation(s);

        }

// Case 4 : LR rotation

        else if( (p->left && isblack(p->left)) && (p->left->right && p->left->right->color =='R') ){
            
            Tree_node<T1,T2>* s = p->left;
            Tree_node<T1,T2>* s_r = s->right;

            if(p == root) root = s_r;


            s_r->color = 'B';
            s->color = 'R';

            LR_Rotation(s);

        // Step 2 : LL rotate(Case 3)

            s = s_r;

            // recoloring

            s->color = p->color;
            p->color = 'B';
            s->left->color = 'B';
            
            LL_Rotation(s);

        }

// Case 5 : LL rotation + recursive

        else if( (p->left && p->left->color=='R') ){

            if(p == root ) root = p->left;
            
            p->color = 'R';
            p->left->color = 'B';
            LL_Rotation(p->left);
            modify_erase(p,'R');
        }

    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------


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
        cout << key << " does not exist! \n";
    }

    cout << "\n** Fifth Step **\n";
    key = "Yunmin";
    if (m.find(key) != m.end()){
        cout << key << " Exists! \n";
    } else{
        cout << key << " does not exist! \n";
    }
    

    return 0;
    
}