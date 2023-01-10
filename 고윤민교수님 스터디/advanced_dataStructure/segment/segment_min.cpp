#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INT_MAX = numeric_limits<int>::max();

struct RMQ{

    // length of array a
    int n;

    vector<int> rangeMin;

    RMQ(const vector<int>& array){
        n = array.size();
        rangeMin.resize(n*4);
        init(array , 0 , n-1 , 1);
    }

    int init(const vector<int>& array , int start , int end , int node){
        
        if(start == end) return rangeMin[node] = array[start];

        int mid = (start + end)/2;

        return rangeMin[node] = min(init(array , start , mid , node*2) , init(array , mid+1 , end , node*2 + 1));
    
    }

    int query(int left ,int right , int node , int start , int end){

        // 범위 밖
        if(start > right || left > end) return INT_MAX;

        // 범위 안
        if(start >= left && end <= right) return rangeMin[node];

        // 걸친 범위

        int mid = (start + end) / 2;
        return min(query(left,right,node*2 , start , mid) , query(left,right,node*2+1, mid+1 , end));

    }

    int query(int left, int right){
        return query(left,right,1,0,n-1);
    }

    int update(int index , int newValue , int node , int start , int end){
        
        // 범위 밖
        if(index < start || index > end) return rangeMin[node];

        if(start == index) return rangeMin[node] = min(rangeMin[node] , newValue);

        int mid = (start + end) / 2;

        return rangeMin[node] = min(update(index, newValue , node*2 , start , mid) , update(index, newValue , node*2 + 1 , mid+1 , end));

    }

    int update(int index , int newValue){
        return update(index , newValue , 1 , 0 , n-1);
    }


};



int main(int argc , char** argv){
    
    vector<int> a = {1,2,1,2,3,1,2,3,4};
    
    RMQ Min(a);

    cout << Min.query(7,8);
    cout << Min.update(3,-1);
}