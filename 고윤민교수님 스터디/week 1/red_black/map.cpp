#include <iostream>
#include <vector>
#include <queue>

using namespace std;


template <typename T1, typename T2>
struct Tree_node{
    T1 key;
    T2 value;
    char color;

    Tree_node<T1,T2>* left;
    Tree_node<T1,T2>* right;
    Tree_node<T1,T2>* parent;
    Tree_node(){color='R';left = nullptr;right=nullptr;parent=nullptr;}
    Tree_node(T1 k , T2 v , char c , Tree_node* l , Tree_node* r , Tree_node* p){key = k;value = v;color = c; left =l; right =r;parent=p;}
    ~Tree_node(){}
};

template<typename T1, typename T2>
class MyIterator{
private:
    Tree_node<T1,T2>* cur;
public:
    MyIterator(Tree_node<T1,T2>*p = nullptr)
        :cur(p){}
    MyIterator& operator++(){
        
        if(cur->right){
            Tree_node<T1,T2>* search = cur->right;
            while(search -> left) search = search ->left;
            cur = search;
        }
        else{
            if(!cur->parent) cur = nullptr;
            else{
                Tree_node<T1,T2>* search= cur->parent;
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
        return *this;
    }   

    Tree_node<T1,T2>* operator*(){
        return cur; 
    }
    bool operator==(const MyIterator &ref){
        return cur == ref.cur;
    }
    bool operator!=(const MyIterator &ref){
        return cur != ref.cur;
    }
};

template <typename T1, typename T2>
class MyMap{    
private:

    Tree_node<T1,T2>* root;
    T1 key;
    int num;
    // vector<Tree_node> myMap;

public:
    MyMap(){root= new Tree_node<T1,T2>(); num=0;};
    ~MyMap(){};

    T2& operator[](T1 key){
        MyMap<T1,T2>::iterator iter;
    
        iter = find(key);
        
        // if(iter != end()) cout << (*iter) << endl;
        // else { cout << "deabak";}

        T2 value;

        if(iter != end()){
            // return (*iter)->value;
        }
        else{
            insert(make_pair(key,value));
           
            iter = find(key);
            
            //modify
        }
        return (*iter)->value;
        
    }

   

    // void operator=(T2 value){
    //     this->insert(make_pair(this->key , value));
    // }

    void insert(const pair<T1,T2> & in);
    // int find_insert_index(Tree_node in)

    void erase(T1 out);
    //begin
    //end
    //find
    void modify(Tree_node<T1,T2>* modf);
    // void print(Tree_node<T1,T2>* temp);
    // void print();

    // Iterator
    typedef MyIterator<T1,T2> iterator;

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
};

template<typename T1 , typename T2>
void print_map(MyMap <T1,T2> m){
    MyMap<string,int>::iterator iter;

    for(iter = m.begin(); iter!=m.end(); ++iter){
        cout << (*iter)->key << ": " << (*iter)->value << '\n';
    }
}

template<typename T1 , typename T2>
void LL_Rotation(Tree_node<T1,T2>* node){
    
    //node == parent
    // if(node->parent == root) root = node;
    
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

template<typename T1 , typename T2>
void RR_Rotation(Tree_node<T1,T2>* node){
    
    //node == parent
    // if(node->parent == root) root = node;

    //grand parent change
    node->parent->right = node ->left;
    node->parent->color = 'R';
    // parent->right change
    if(node->left) node->left->parent = node->parent;

    // parent change
    node->color = 'B';
    node->left = node->parent;
    // cout << node->parent->key << endl;
    node-> parent = node->parent->parent;
    if(node->parent) node->parent->right = node;
    // else node->parent = nullptr;
    
    //grand parent change(rest part)
    node->left->parent = node;

}



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

template<typename T1, typename T2>
void MyMap<T1,T2>::modify(Tree_node<T1,T2>* modf){
    
    // cout << root->key << " " << modf->key <<endl;
    if(root == modf) modf->color = 'B';
    else{

        Tree_node<T1,T2>* parent = modf->parent;
        if(parent->color =='B') return;
        
        Tree_node<T1,T2>* gr_parent = parent->parent;
        if(parent == gr_parent->left){
            
            if(gr_parent->right && gr_parent->right->color=='R'){
                gr_parent->right->color = 'B';
                gr_parent->color = 'R';
                parent->color = 'B';
                // cout << "Wait" << gr_parent->key << parent->key << modf->key<< endl;
                modify(gr_parent);
            }
            else{
                if(modf == parent->left){ 
                    if(gr_parent == root) root = parent;
                    LL_Rotation(parent);
                    }
                
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

        else if(parent == gr_parent ->right){
            if(gr_parent->left && gr_parent->left->color =='R'){
                gr_parent->left->color = 'B';
                gr_parent->color = 'R';
                parent->color = 'B';
                modify(gr_parent);
            }

            else{
                if(modf == parent->right) {
                    if(gr_parent == root) root = parent;
                    RR_Rotation(parent);
                }
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

    // cout << "Debuuu";
}


template<typename T1 , typename T2>
void MyMap<T1,T2>::insert (const pair<T1,T2> & in){
    
    if(num == 0){
        root->key = in.first; root->value = in.second;
        num++;
        modify(root);
    }
    else{
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
    // cout << "Debug";
        
    num++;
        
    if(search->left && in.first == search->left->key) modify(search->left);
    else if(search->right && in.first == search->right->key) modify(search->right);

    }



}



template<typename T1 , typename T2>
void MyMap<T1,T2>::erase (T1 out){

}

// template <typename T1, typename T2>
// void MyMap<T1,T2>:: print(){
    
//     map->left.print();
//     //cout <<;
//     map->right.print();
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