#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <utility>

#define MAX 1000000000

using namespace std;

ifstream f("dijkstra.in");
ofstream g("dijkstra.out");

int N, M;
vector<int> dist, selected;
priority_queue<pair<int,int>> pq;               // first -> distance to node x ; second -> actual node x
vector<vector<pair<int, int>>> weightedNeighbours;          // first -> edge weight ; second -> 2nd node in edge

int main()
{
    f >> N >> M;
    dist = vector<int>(N + 1, MAX);
    selected = vector<int> (N + 1);
    weightedNeighbours = vector<vector<pair<int, int>>>(N + 1);

    int i, x, y, c;
    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        weightedNeighbours[x].push_back(make_pair(c, y));
    }

    dist[1] = 0;
    pq.push(make_pair(0, 1));

    pair<int, int> edg;
    while(!pq.empty())
    {
        x = pq.top().second;
        c = -pq.top().first;
        pq.pop();

        if(selected[x] == 0)
        {
            selected[x] = 1;

            for(i = 0; i < weightedNeighbours[x].size(); i++)
            {
                edg = weightedNeighbours[x][i];
                if(selected[edg.second] == 0)
                {
                    if(c + edg.first < dist[edg.second])
                    {
                        dist[edg.second] = c + edg.first;
                        pq.push(make_pair(-dist[edg.second], edg.second));
                    }
                }
            }
        }
    }

    for(i = 2; i <= N; i++)
    {
        if(dist[i] == MAX)
            g << 0 << ' ';
        else
            g << dist[i] << ' ';
    }
    return 0;
}