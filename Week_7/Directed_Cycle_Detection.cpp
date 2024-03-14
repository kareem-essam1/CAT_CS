#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool DFS(int u,int vis[],vector<int> adj[]) {
    vis[u]=1;
    for(int v:adj[u]){
        if(vis[v]==1) return true;
        else if(vis[v]==0)
            if(DFS(v,vis,adj)) return true;
    }
    vis[u]=2;
    return false;
}
bool isCyclic(vector<vector<int>>& edges, int v, int e) {
    int vis[v]={0};
    vector<int> adj[v];
	for (int i = 0; i < edges.size(); i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        adj[from].push_back(to);
    }
    for(int i=0;i<v;i++) {
        if(vis[i]==0) {
            if(DFS(i,vis,adj)) return true;
        }
    }
    return false;
}

int main()
{
    

    return 0;
}