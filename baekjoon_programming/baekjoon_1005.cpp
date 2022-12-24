#include <iostream>
#include <vector>
#include <queue>


using namespace std;

vector<int> adj_list[1000];
int build[1000];
int dp[1000];
bool visit[1000];
int indegree[1000];
int T, N, K, buildtime_total;

void topologicalSort(int target){
    int start;
    queue<int> q;

    for(int i = 0 ; i < N ; ++i){
        if(indegree[i] == 0){
            q.push(i+1);
            dp[i] = build[i];
        }
    }

    while(!q.empty()){  

        int start = q.front();
        q.pop();

        for(int i = 0 ; i < adj_list[start-1].size() ; ++i){
            int end = adj_list[start-1][i];
            if(--indegree[end-1] == 0) q.push(end);
            dp[end-1] = max(dp[end-1] , build[end-1] + dp[start-1] );
        }
    }
    cout << dp[target-1] << "\n";
}

int main(int argc, char** argv){

    int first,end;
    int target;

    cin >> T;

    for(int i = 0 ; i < T ; ++i){

        for(int i = 0 ; i < 1000 ; ++i){
            indegree[i] = 0;
            build[i] = 0;
            visit[i] = false;
            adj_list[i].clear();
            dp[i] = 0;
        }

        cin >> N >> K;

        for(int i = 0; i < N ; ++i) cin >> build[i];

        for(int i =0 ; i < K ; ++i){
            cin >> first >> end;

            adj_list[first-1].push_back(end);
            indegree[end-1]++;
        }

        cin >> target;

        topologicalSort(target);

    }
}