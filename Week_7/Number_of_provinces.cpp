#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
bool vis[205];
int ctr=0;
vector<int> adj[205];

void DFS(int u){
    vis[u]=true;
    for(int v:adj[u])
        if(!vis[v]){
            DFS(v);
        }
        
}
int findCircleNum(vector<vector<int>>& isConnected) {
        for(int i=0;i<isConnected.size();i++){
        for(int j=0;j<isConnected[i].size();j++){
            if(isConnected[i][j]==1&&i!=j){
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
        }
        for(int i=0;i<isConnected.size();i++){
            if(!vis[i]){
                ctr++; DFS(i);
            }
            
        }
        return ctr;
    }


int main()
{
    vector<vector<int>> isConnected={{1,1,0},{1,1,0},{0,0,1}};
    cout<<findCircleNum(isConnected);
    return 0;
}