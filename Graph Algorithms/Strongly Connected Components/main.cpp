#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream f("ctc.in");
ofstream g("ctc.out");

int N, M;
vector<vector<int>> edges;
stack<int> nodes;
vector<int> visited;
vector<vector<int>> reversed;
vector<vector<int>> solution;
vector<int> aux;


void DFS(int curr)
{
    visited[curr] = 0;
    int x;
    for(int j = 0; j < edges[curr].size(); j++)
    {
        x = edges[curr][j];
        if(visited[x] == -1)
        {
            DFS(x);
        }
    }
    nodes.push(curr);
}


void DFSkosaraju(int curr)
{
    visited[curr] = 1;
    int x;
    for(int j = 0; j < reversed[curr].size(); j++)
    {
        x = reversed[curr][j];
        if(visited[x] == 0)
        {
            DFSkosaraju(x);
        }
    }
    aux.push_back(curr);
}


int main()
{

    f >> N >> M;
    edges = vector<vector<int>>(N + 1);
    reversed = vector<vector<int>>(N + 1);
    visited = vector<int> (N + 1, -1);

    int i, x, y;

    for(i = 1 ; i <= M; i++)
    {
        f >> x >> y;
        edges[x].push_back(y);
        reversed[y].push_back(x);
    }
    
    // kosaraju
    for(i = 1 ; i <= N; i++)
    {
        if(visited[i] == -1)
            DFS(i);
    }

    int scc = 0;
    while(!nodes.empty())
    {
        if(visited[nodes.top()] == 0)
        {
            aux = vector<int>();
            DFSkosaraju(nodes.top());
            solution.push_back(aux);
            scc ++;
        }
        nodes.pop();
    }
    g << scc << '\n';

    for(i = 0; i < solution.size(); i++)
    {
        for(int j = 0; j < solution[i].size(); j++)
            g << solution[i][j] << ' ';
        g << '\n';
    }
    return 0;
}