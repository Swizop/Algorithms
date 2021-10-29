#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream f("bfs.in");
    ofstream g("bfs.out");

    int n, m, s, x, y, i, j, curr, val;
    f >> n >> m >> s;

    vector<vector<int>> v = vector<vector<int>>(n + 1);
    queue<int> q;
    vector<int> dist = vector<int>(n + 1, -1);

    for(i = 1; i <= m; i++)
    {
        f >> x >> y;
        v[x].push_back(y);
    }

    q.push(s);
    dist[s] = 0;
    while(!q.empty())
    {
        curr = q.front();
        for(j = 0; j < v[curr].size(); j++)
        {   
            val = v[curr][j];
            if(dist[val] == -1)
            {
                dist[val] = dist[curr] + 1;
                q.push(val);
            }
        }
        q.pop();
    }

    for(i = 1; i <= n; i++)
        g << dist[i] << " ";
    return 0;
}