#include <iostream>

using namespace std;

#define ALPHA 26

struct node{
    bool finish ;
    node* next[ALPHA];

    node(){
        finish = false;
        for(int i = 0 ; i < ALPHA ; ++i) next[i] = NULL;
    }
    ~node(){};
};

class Trie{

private:
    node* root[ALPHA] ;
public:
    
    Trie(){
        for(int i = 0 ; i < ALPHA ; ++i) root[i] = NULL;
    };
    ~Trie(){};


    void insert(const char* key, node* next[]){

        int index = *key -'A';
        
        if(!next[index]) next[index] = new node();
        if(*(key + 1) == '\0'){
            next[index]->finish = true;
            return;
        }
        insert( key+1 , next[index]->next);

    }
    
    void insert(const char* key){
        insert(key , root);
    }

    bool find(const char* key , node* next[]){
        
        int index = *key - 'A';
        
        if(!next[index]) return false;

        if(*(key+1)=='\0'){ 
            if(next[index]->finish) return true;
            else return false;
        }

        return find(key+1 , next[index]->next);
    }
    bool find(const char* key){
        return find(key, root);
    }
};

int main(int argc , char** argv){
    Trie* t = new Trie();
    t->insert("ABC");
    t->insert("ABCD");
    t->insert("ABBB");
    t->insert("ABAC");
    t->insert("ABDD");
    t->insert("ABEF");
    cout << t->find("ABC");
    cout << t->find("ABEF");
    cout << t->find("ABEFG");
    
}