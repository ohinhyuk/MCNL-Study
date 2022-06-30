#include <iostream>

using namespace std;

#define ALPHA 26

struct Trie{
    bool finish;
    Trie* next[ALPHA];

    Trie(){
        finish = false;
        for(int i = 0 ; i < ALPHA ; ++i) next[i] = NULL;
    }
    ~Trie(){
        // delete next;
    };

    void insert(const char* key);
    bool find(const char* key);

};

void Trie::insert(const char* key){
    
    if(*key=='\0'){
        finish = true;
        return;
    } 

    int index = *key - 'A';

    if(!next[index]) next[index] = new Trie();
    next[index]->insert(key+1);

}

bool Trie::find(const char* key){

    if(*key == '\0'){
        if(finish) return true;
        return false;
    }
    
    int index = *key - 'A';

    if(!next[index]) return false;
    return next[index]->find(key+1);

}


int main(int argc , char ** argv){

}