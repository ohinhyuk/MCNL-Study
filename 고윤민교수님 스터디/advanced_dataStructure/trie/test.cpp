#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const pair<string,int> &v1, const pair<string,int> &v2){

    return v1.first == v2.first;
}

int main(int avgc , char** argv){
    
    vector<pair<string,int>> v;

    v.push_back(make_pair("AAA",2));
    v.push_back(make_pair("BBA",2));
    v.push_back(make_pair("CCA",3));
    v.push_back(make_pair("AAA",4));
    v.push_back(make_pair("BBA",5));

    for(auto x : v) cout << x.first << x.second << endl;
    cout << endl;
    v.erase(unique(v.begin(),v.end(),comp) , v.end());

    for(auto x : v) cout << x.first << x.second << endl;

}