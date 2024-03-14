#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool DFS(int u,int st,vector<vector<int>>& graph,int vis[]){
    vis[u]=st;
    for(int v:graph[u]){
        if(vis[v]==-1){
            if(!DFS(v,!st,graph,vis)){
                return false;
            }
        }
        else if(vis[v]==st)
          return false;
    }
    return true;
}
bool isBipartite(vector<vector<int>>& graph) {
    int vis[100];
    for(int i=0;i<100;i++)  vis[i]=-1;
    for(int i=0;i<graph.size();i++){
        if(vis[i]==-1)
           { if(!DFS(i,0,graph,vis)) return false;}
    }
    return true;
}
int main()
{
    vector<vector<int>> graph={{1,2,3},{0,2},{0,1,3},{0,2}};
    cout<<isBipartite(graph);
    return 0;
}