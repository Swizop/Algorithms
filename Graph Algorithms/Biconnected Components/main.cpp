#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream f("biconex.in");
ofstream g("biconex.out");

int N, M, K;
vector<vector<int>> v;
vector<int> discovered;         // time when nodes were discovered
vector<int> earliest;           // the earliest time of a node to which a node can go back to
stack<int> nodes;
vector<vector<int>> solution;


void biconnected(int curr)
{
    int subComponents = 0, following;

    for(int i = 0; i < v[curr].size(); i++)
    {
        following = v[curr][i];
        if(discovered[following] == 0)
        {
            subComponents += 1;

            nodes.push(following);
            discovered[following] = discovered[curr] + 1;
            earliest[following] = discovered[curr];

            biconnected(following);

            if(subComponents > 1 && discovered[curr] == 1)       // the only link between {{v[curr][i] and the nodes that follow it}} and {{the nodes already visited}}
                                    // is through curr => curr is a critical point => from v[curr][i] onwards we have a new biconnected component
            {
                solution.push_back(vector<int>());
                while(!(nodes.top() == following))
                {
                    solution[K].push_back(nodes.top());
                    nodes.pop();
                }
                solution[K].push_back(nodes.top());
                nodes.pop();
                solution[K].push_back(curr);        // curr (the top level node) was part of the biconnected component which was just visited in the recursion, but it will
                                                // also be in the biconnected component with the nodes previous to that, so we keep curr in the stack, adding it sepparately
                K++;
            }

            if(discovered[curr] <= earliest[following] && discovered[curr] > 1)
            {
                solution.push_back(vector<int>());
                while(!(nodes.top() == following))
                {
                    solution[K].push_back(nodes.top());
                    nodes.pop();
                }
                solution[K].push_back(nodes.top());
                nodes.pop();
                solution[K].push_back(curr);
                K++;
            }
            else
                earliest[curr] = min(earliest[following], earliest[curr]);
            // if curr is the first node, the last biconnected component will remain in the stack bc the program won't go to line 30 again, and we'll empty it in main()
        }
        else
        {
            earliest[curr] = min(earliest[curr], discovered[following]);
        }
    }
}


int main()
{
    f >> N >> M;
    int x, y, i;

    v = vector<vector<int>>(N + 1);
    discovered = vector<int> (N + 1);
    earliest = vector<int> (N + 1);
    
    for(i = 1; i <= M; i++)
    {
        f >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    
    for(i = 1; i <= N; i++)
    {
        if (discovered[i] == 0)
        {
            discovered[i] = earliest[i] = 1;
            nodes.push(i);
            biconnected(i);
        }
        if(!nodes.empty())
        {
            solution.push_back(vector<int>());
            while(!nodes.empty())
            {
                solution[K].push_back(nodes.top());
                nodes.pop();
            }
            K++;
        }
    }

    g << K << '\n';
    for(i = 0; i < K; i++)
    {
        for (int j = 0; j < solution[i].size(); j++)
        {
            g << solution[i][j] << ' ';
        }
        g << '\n';
    }
    return 0;
}