#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

int N, M;
// vector<vector<pair<int, int>>> edges;
vector<pair<int,pair<int, int>>> weightedEdges;
vector<int> father;
vector<int> height;
vector<pair<int, int>> solution;


int reprez(int curr)
{
    int f;
    if(father[curr] == 0)
        return curr;
    f = reprez(father[curr]);
    father[curr] = f;
    return f;
}


int main()
{
    int x, y, c, i;
    f >> N >> M;
    
    father = vector<int> (N + 1);
    height = vector<int> (N + 1);
    for(i = 1; i <= M; i++)
    {
        f >> x >> y >> c;
        weightedEdges.push_back(make_pair(c, make_pair(x, y)));
    }

    int totalCost = 0, j = 0;
    sort(weightedEdges.begin(), weightedEdges.end());
    for(i = 1; i <= N - 1; i++)
    {
        while(!(reprez(weightedEdges[j].second.first) != reprez(weightedEdges[j].second.second)))
            j++;
        totalCost += weightedEdges[j].first;
        solution.push_back(weightedEdges[j].second);


        x = reprez(weightedEdges[j].second.first);          //union operation
        y = reprez(weightedEdges[j].second.second);
        if(height[x] > height[y])
            father[y] = x;
        else
            father[x] = y;

        if(height[x] == height[y])
            height[y]++;
    }

    g << totalCost << '\n' << N - 1 << '\n';
    for(i = 0; i < solution.size(); i++)
        g << solution[i].first << ' ' << solution[i].second << '\n';
    return 0;
}