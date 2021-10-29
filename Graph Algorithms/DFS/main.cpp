#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int n, m;
vector<vector<int>> v;
vector<int> visited;

void dfs(int curr)
{
    for(int i = 0; i < v[curr].size(); i++)
        if(visited[v[curr][i]] == 0)
        {
            visited[v[curr][i]] = 1;
            dfs(v[curr][i]);
        }
}

int main()
{
    ifstream f("dfs.in");
    ofstream g("dfs.out");
    
    int i, x, y;

    f >> n >> m;
    v = vector<vector<int>>(n + 1);
    visited = vector<int>(n + 1);
    
    for(i = 1; i <= m; i++)
    {
        f >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    int conexElements = 0;
    for(i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            visited[i] = 1;
            conexElements ++;
            dfs(i);
        }
    }
    g << conexElements;
    return 0;
}