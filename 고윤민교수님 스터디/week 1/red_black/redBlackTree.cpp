#include <iostream>

using namespace std;

#define MAXSIZE 50

struct Tree_node{
    int data;
    char color;

    Tree_node(){};
    Tree_node(int num){
        data = num;
        color = 'R';
    }
    ~Tree_node(){};
};

class redBlack{

private:
    Tree_node rBTree[MAXSIZE];
    int nodeNum = 0;
public:
    redBlack(){
        for(int i = 0 ; i < MAXSIZE ; ++i){
            rBTree[i].data = -1;
            rBTree[i].color = 'B';
        }
    };
    ~redBlack(){};

    int insert_find(Tree_node newNode);
    void modify(int child);
    void node_to_node(int a, int b);
    void insert(Tree_node newNode);
    void print();
};


// insert 될 알맞은 index를 return 해주는 함수
int redBlack::insert_find(Tree_node newNode){

    int find_index = 1;

    if(nodeNum == 0) return 1;

    while( rBTree[find_index].data != -1){
        // 이미 값 존재
        if(rBTree[find_index].data == newNode.data) return -1;
        
        else if(rBTree[find_index].data < newNode.data) find_index = find_index*2 + 1;
            
        else if(rBTree[find_index].data > newNode.data) find_index = find_index*2;
    }

    return find_index;

}

void redBlack::node_to_node(int a, int b){
    rBTree[b].color = rBTree[a].color;
    rBTree[b].data = rBTree[a].data;

    rBTree[a].color = 'N';
    rBTree[a].data = -1;
}

void redBlack::modify(int child){


    if(child == 1){
        rBTree[child].color = 'B';
    } 
    
    else if(child > 3){

        int parent = child / 2;

        if(rBTree[parent].color=='B') return;
        
        int gr_parent = parent / 2;


        if(parent == gr_parent * 2){
            int uncle = gr_parent * 2 + 1;

            if(rBTree[uncle].color=='R'){
                rBTree[uncle].color = 'B';
                rBTree[parent].color = 'B';
                rBTree[gr_parent].color = 'R';
                modify(gr_parent);
            }
            else if(rBTree[uncle].color =='B' && parent*2 + 1 == child){
                node_to_node(uncle , uncle * 2 + 1);
                node_to_node(gr_parent, uncle);
                rBTree[uncle].color = 'R';
                node_to_node(child,gr_parent);
                rBTree[gr_parent].color = 'B';
                if(nodeNum >= child * 2 ) node_to_node(child*2 ,child);
                if(nodeNum >= child * 2 + 1) node_to_node(child*2+1 , uncle*2);
            }
            else if(rBTree[uncle].color =='B' && parent*2 == child){
                node_to_node(uncle , uncle*2 + 1);
                node_to_node(gr_parent,uncle);
                rBTree[uncle].color = 'R';
                node_to_node(parent,gr_parent);
                rBTree[gr_parent].color = 'B';
                node_to_node(child , parent);
                if(nodeNum >= child + 1) node_to_node(parent*2 + 1, uncle * 2);

            }

        }
        else if(parent == gr_parent * 2 + 1){
            
            int uncle = gr_parent * 2;

            if(rBTree[uncle].color=='R'){
                rBTree[uncle].color = 'B';
                rBTree[parent].color = 'B';
                rBTree[gr_parent].color = 'R';
                modify(gr_parent);
            }
            else if(rBTree[uncle].color =='B' && parent*2 == child){
                node_to_node(uncle , uncle * 2);
                node_to_node(gr_parent, uncle);
                rBTree[uncle].color = 'R';
                node_to_node(child,gr_parent);
                rBTree[gr_parent].color = 'B';
                if(nodeNum >= child * 2 ) node_to_node(child*2 , uncle*2 + 1);
                if(nodeNum >= child * 2 + 1 ) node_to_node(child*2 + 1 ,child);
                
            }
            else if(rBTree[uncle].color =='B' && parent*2 +1== child){
                node_to_node(uncle , uncle*2);
                node_to_node(gr_parent,uncle);
                rBTree[uncle].color = 'R';
                node_to_node(parent,gr_parent);
                rBTree[gr_parent].color = 'B';
                node_to_node(child , parent);
                node_to_node(parent*2, uncle * 2 + 1);
            }
        }
    }
    
}

void redBlack::print(){
    for(int i = 0 ; i < MAXSIZE ; ++i){
        cout << rBTree[i].data << ' ';
    } 
}

void redBlack::insert(Tree_node newNode){
    
    int insert_index = insert_find(newNode);

    nodeNum++;
    
    rBTree[insert_index].data = newNode.data;
    rBTree[insert_index].color = newNode.color;

    modify(insert_index);

}

int main(int argc, char** argv){
    //  8, 7, 9, 3, 6, 4, 5, 12
    redBlack RBT;
    Tree_node a{8};
    Tree_node b{7};
    Tree_node c{9};
    Tree_node d{3};
    Tree_node e{6};
    Tree_node f{4};
    Tree_node g{5};
    Tree_node h{12};
    RBT.insert(a);
    
    RBT.insert(b);
    
    RBT.insert(c);
    RBT.insert(d);
    
    
    RBT.insert(e);
    
    RBT.insert(f);
    
    RBT.insert(g);
    
    
    RBT.insert(h);
    
    RBT.print();
    
}