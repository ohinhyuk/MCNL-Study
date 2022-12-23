// <방법 1>

// #include <iostream>
// #include <cmath>
// #include <algorithm>

// using namespace std;

// int main(int argc , char** argv){

//     int N , H;
//     long long int total = 0;
//     cin >> N >> H;
//     int tree[N];
    
//     for(int i = 0 ; i < N ; ++i){
//         cin >> tree[i];
//         total += tree[i];
//     } 

//     long long int treetops = 0;
//     sort(tree , tree + N, greater<int>());
    
//     if(H < total - ((long long int)N*tree[N-1]) ){
//         for(int i = 0 ; i < N-1 ; ++i){
//             treetops += (i+1) * (tree[i] - tree[i+1]);
//             if(treetops >= H){
//                 int diff = (treetops - H) / (i+1);
//                 cout << tree[i+1] + diff;
//                 break;
//             } 
//         }
//     }
//     else{
//         int rest = H - (total - (N*tree[N-1]));
//         int diff = ceil((double)rest / N);
//         cout << tree[N-1] - diff;
//     }

// }

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long int> tree;

long long int treetops(long long int mid){
    long long int sum = 0;
    for(int i = 0 ; i < tree.size(); ++i){
        if(tree[i] < mid) break;
        sum += tree[i]-mid;
    }
    return sum;
}

int main(int argc , char** argv){

    int N , H ,temp;
    long long int total = 0;
    cin >> N >> H;
    
    for(int i = 0 ; i < N ; ++i){
        cin >> temp;
        tree.push_back(temp);
        total += temp;
    } 

    long long int first = 0;
    long long int end = 1000000000;
    long long int mid;

    sort(tree.begin(),tree.end(),greater<int>());

    while(first <= end){
        mid = (first + end) / 2;
        if(treetops(mid) < H ) end = mid - 1;
        else if(treetops(mid) > H) first = mid + 1;
        else break;
    }
    if(treetops(mid) < H) mid--;
    cout << mid << "\n";
}