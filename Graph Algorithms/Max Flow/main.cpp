#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <queue>


#define MAXCAPACITY 200000
#define NMAX 1002
using namespace std;

ifstream f("maxflow.in");
ofstream g("maxflow.out");

int N, M;

    
    queue<int> Q;
    vector<vector<int>> edges;
    
    int flow[NMAX][NMAX];


int main()
{
    f >> N >> M;
    edges = vector<vector<int>> (N + 1);

    int i, x, y, c;

    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        edges[x].push_back(y);
        edges[y].push_back(x);

        flow[x][y] = c;
    }

    vector<int> nodesInfo = vector<int> (N + 1);
    vector<int> fathers = vector<int> (N + 1);

    int maxFlow = 0, iteration = 1, curr, following, mini;    
    while(true)
    {
        Q.push(1);
        nodesInfo[1] = iteration;
        mini = MAXCAPACITY;

        while(!Q.empty())
        {
            curr = Q.front();
            Q.pop();
            for(i = 0; i < edges[curr].size(); i++)
            {
                following = edges[curr][i];
                if(nodesInfo[following] != iteration && flow[curr][following] > 0)
                {
                    Q.push(following);
                    fathers[following] = curr;
                    nodesInfo[following] = iteration;
                    if(following == N)
                    {
                        Q = queue<int>();
                        break;
                    }
                }
            }
        }

        if(nodesInfo[N] != iteration)
            { g << maxFlow; return 0; }

        curr = N;
        while(curr != 1) 
        {       
            mini = min(mini, flow[fathers[curr]][curr]);
            curr = fathers[curr];
        }
        maxFlow += mini;
        curr = N;
        while(curr != 1)
        {
            flow[fathers[curr]][curr] -= mini;
            flow[curr][fathers[curr]] += mini;
            curr = fathers[curr];
        }
        
        iteration++;   
    }
    return 0;
}