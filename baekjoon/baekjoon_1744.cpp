#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc ,char**argv){
    int N;
    int temp;
    bool zero = false;
    int sum = 0;

    cin >> N;

    vector<int> pos;
    vector<int> neg;


    for(int i = 0 ; i < N ; ++i){
        cin >> temp;

        if(temp > 0) pos.push_back(temp);
        else if(temp < 0) neg.push_back(temp);
        else if(temp == 0) zero = true;

    }

    int N_pos = pos.size();
    int N_neg = neg.size();

    sort(pos.rbegin(),pos.rend());
    sort(neg.begin(),neg.end());

    if(zero){
        if(N_pos % 2 ==0 && N_neg % 2== 1){
            neg.pop_back();
            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
        else if(N_pos % 2 == 1 && N_neg % 2 ==0){
            sum += pos.back();
            pos.pop_back();
            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
        else if(N_pos % 2 ==0&& N_neg % 2 ==0){
            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
        else{
            neg.pop_back();
            sum += pos.back();
            pos.pop_back();
            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
    }
    else{
        if(N_pos % 2 ==0 && N_neg % 2== 1){
            sum += neg.back();
            neg.pop_back();

            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }

        }
        else if(N_pos % 2 == 1 && N_neg % 2 ==0){
            
            sum += pos.back();
            pos.pop_back();

            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }

        }
        else if(N_pos % 2 ==0&& N_neg % 2 ==0){
            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
        else{
            sum += pos.back();
            pos.pop_back();
            sum += neg.back();
            neg.pop_back();

            for(int i = 0 ; i < pos.size() ; i+=2){
                if((pos[i] * pos[i+1]) > (pos[i] + pos[i+1])) sum += pos[i] * pos[i+1];
                else sum += pos[i] + pos[i+1];
            }
            for(int i = 0 ; i < neg.size(); i+=2){
                if( (neg[i]* neg[i+1]) > (neg[i] + neg[i+1])) sum += neg[i] * neg[i+1];
                else sum += neg[i] + neg[i+1];
            }
        }
    }

    cout << sum;
}