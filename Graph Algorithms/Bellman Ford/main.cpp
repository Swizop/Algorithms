#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

#define MAX 1000000000
using namespace std;

ifstream f("bellmanford.in");
ofstream g("bellmanford.out");


class Graph
{
    int N, M;

    vector<int> nodesInfo;
    queue<int> Q;
    vector<pair<int, pair<int, int>>> weightedEdges;            //first -> edge cost, second -> nodes in edge
    vector<vector<pair<int, int>>> weightedNeighbours;          // first -> edge weight ; second -> 2nd node in edge
    vector<int> distances;

    public:
        Graph() = default;

        void set_nodesInfo(int);
        void set_distances();

        void read_weightedEdges();
        void read_weightedNeighbours();
        void print_message(string);
        void print_solution(vector<int>, int);


        void bellman_ford();
};


void Graph :: set_nodesInfo(int value) { nodesInfo = vector<int> (N + 1, value); }
void Graph :: set_distances() { distances = vector<int> (N + 1, MAX); }


void Graph :: read_weightedEdges()
{
    f >> N >> M;

    int i, x, y, c;
    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        weightedEdges.push_back(make_pair(c, make_pair(x, y)));
    }
}


void Graph :: read_weightedNeighbours()
{
    f >> N >> M;
    weightedNeighbours = vector<vector<pair<int, int>>> (N + 1);

    int i, x, y, c;
    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        weightedNeighbours[x].push_back(make_pair(c, y));
    }
}


void Graph :: print_message(string m) { g << m; }


void Graph :: print_solution(vector<int> solution, int start)
{
    for(int i = start; i < solution.size(); i ++)
    {
        g << solution[i] << ' ';
    }
}


void Graph :: bellman_ford()
{
    read_weightedNeighbours();
    set_distances();
    set_nodesInfo(0);

    distances[1] = 0;
    nodesInfo[1] = 1;
    Q.push(1);

    int j, c, u, v;
    while(!Q.empty())
    {
        
        u = Q.front();
        nodesInfo[u] = -nodesInfo[u];
        Q.pop();

        for(j = 0; j < weightedNeighbours[u].size(); j++)
        {
            c = weightedNeighbours[u][j].first;
            v = weightedNeighbours[u][j].second;
            if(distances[u] + c < distances[v])
            {
                distances[v] = distances[u] + c;
                if(nodesInfo[v] <= 0)
                {
                    Q.push(v);
                    nodesInfo[v] = -nodesInfo[v] + 1;
                    if(nodesInfo[v] == N)
                    {
                        print_message("Ciclu negativ!");
                        return;
                    }
                }
            }
        }
    }

    print_solution(distances, 2);
}


int main()
{
    Graph g;
    g.bellman_ford();
    return 0;
}