#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("sortaret.in");
ofstream g("sortaret.out");

int N, M;
vector<vector<int>> edges;
vector<int> topSort;
vector<int> visited;

void top_sort(int curr)
{
    visited[curr] = 1;
    int x;
    for(int i = 0; i < edges[curr].size(); i++)
    {
        x = edges[curr][i];
        if(visited[x] == 0)
            top_sort(x);
    }
    topSort.push_back(curr);
}


int main()
{
    f >> N >> M;
    int i, x, y;

    edges = vector<vector<int>> (N + 1);
    visited = vector<int> (N + 1);
    for(i = 1; i <= M; i++)
    {
        f >> x >> y;
        edges[x].push_back(y);
    }

    for(i = 1; i <= N; i++)
    {
        if(visited[i] == 0)
            top_sort(i);
    }

    for(i = topSort.size() - 1; i >= 0; i --)
    {
        g << topSort[i] << ' ';
    }
    return 0;
}