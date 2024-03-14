#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
bool DFS(int u,int p,bool vis[],vector<int> adj[]) {
    vis[u]=true;
    for(int v:adj[u]){
        if(!vis[v]){
            if(DFS(v,u,vis,adj)) return true;
        }
        else if(vis[v]&&v!=p)
            return true;
    }
    return false;
}

bool detectCycle(int V, vector<int> adj[]) {
    bool vis[V]={0};
    for(int i=0;i<V;i++){
        if(!vis[i]){
            if(DFS(i,-1,vis,adj)) {return true;}
        }
    }
    return false;
}
int main()
{
    int V = 5;
    vector<int> adj[V];
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[3].push_back(4);
    adj[4].push_back(3);
    cout<<detectCycle(V,adj);
    return 0;
}