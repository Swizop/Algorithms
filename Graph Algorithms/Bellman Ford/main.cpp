#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

#define MAX 1000000000
using namespace std;


class Graph
{
    int N, M;

    vector<int> nodesInfo;
    vector<pair<int, pair<int, int>>> weightedEdges;            //first -> edge cost, second -> nodes in edge
    vector<int> distances;

    public:
        Graph() = default;

        void set_nodesInfo(int);
        void set_distances();

        void read_weighted(string);
        void print_message(string, string);
        void print_solution(string, vector<int>, int);
        void bellman_ford();
};


void Graph :: set_nodesInfo(int value) { nodesInfo = vector<int> (N + 1, value); }
void Graph :: set_distances() { distances = vector<int> (N + 1, MAX); }


void Graph :: read_weighted(string file)
{
    ifstream f(file);
    f >> N >> M;

    int i, x, y, c;
    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        weightedEdges.push_back(make_pair(c, make_pair(x, y)));
    }
}


void Graph :: print_message(string file, string m)
{
    ofstream g(file);
    g << m;
}


void Graph :: print_solution(string file, vector<int> solution, int start)
{
    ofstream g(file);
    for(int i = start; i < solution.size(); i ++)
    {
        g << solution[i] << ' ';
    }
}


void Graph :: bellman_ford()
{
    read_weighted("bellmanford.in");
    set_distances();
    set_nodesInfo(0);

    nodesInfo[1] = 1;
    distances[1] = 0;

    int i, j, change, c, u, v;
    for(i = 1; i <= N; i++)
    {
        change = 0;
        for(j = 0; j < weightedEdges.size(); j++)
        {
            c = weightedEdges[j].first;
            u = weightedEdges[j].second.first;
            v = weightedEdges[j].second.second;

            if(nodesInfo[u] >= i)
            {
                if(distances[u] + c < distances[v])
                {
                    change = 1;
                    distances[v] = distances[u] + c;
                    nodesInfo[v] = i + 1;
                }
            }
        }
    }

    if(change == 1)
        print_message("bellmanford.out", "Ciclu negativ!");
    else
        print_solution("bellmanford.out", distances, 1);
}


int main()
{
    Graph g;
    g.bellman_ford();
    return 0;
}