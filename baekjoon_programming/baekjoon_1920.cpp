#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> arr;
vector<int> num;

int b_search(int first , int end , int target){
    int mid;
    
    while(first <= end){
        mid = (first + end) / 2;
        if(arr[mid] < target) first = mid + 1;
        else if(arr[mid] > target) end = mid - 1;
        else return 1;
    }
    
    return 0;
    
}

int main(int argc, char** argv){

    ios_base::sync_with_stdio(0); cin.tie(0);

    int N,M,temp;

    cin >> N;
    
    for(int i = 0 ; i < N ; ++i){
        cin >> temp;
        arr.push_back(temp);
    } 
    cin >> M;
    
    for(int i = 0 ; i < M ; ++i){
        cin >> temp;
        num.push_back(temp);
    } 
    
    sort(arr.begin() , arr.end());

    for(int i = 0 ; i < M ; ++i) cout << b_search(0,N-1,num[i]) << "\n";
    

}