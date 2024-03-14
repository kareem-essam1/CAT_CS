#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int drow[4]={0,-1,0,1};
int dcol[4]={1,0,-1,0};

void DFS(int i,int j,vector<vector<bool>>& vis,vector<vector<char>>& board){
    int n=board.size(),m=board[0].size();
    vis[i][j]=true;
    for(int s=0;s<4;s++){
        int row=i+drow[s];
        int col=j+dcol[s];
        if(row>=0&&row<n&&col>=0&&col<m&&!vis[row][col]&&board[row][col]=='O'){
            DFS(row,col,vis,board);
        }
    }
}

void solve(vector<vector<char>>& board) {
    int n=board.size(),m=board[0].size();
    vector<vector<bool>> vis(n,vector<bool>(m,false));
    for(int i=0;i<m;i++){
        if(!vis[0][i]&&board[0][i]=='O')
            DFS(0,i,vis,board);
        if(!vis[n-1][i]&&board[n-1][i]=='O')
            DFS(n-1,i,vis,board);
    }
    for(int i=0;i<n;i++){
        if(!vis[i][0]&&board[i][0]=='O')
            DFS(i,0,vis,board);
        if(!vis[i][m-1]&&board[i][m-1]=='O')
            DFS(i,m-1,vis,board);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
        if(board[i][j]=='O'&&!vis[i][j])
            board[i][j]='X';
    }
    }
}

int main()
{
    vector<vector<char>> board={{'X','X','X','X'},
                                {'X','O','O','X'},
                                {'X','X','O','X'},
                                {'X','O','X','X'}};
    solve(board);


    return 0;
}