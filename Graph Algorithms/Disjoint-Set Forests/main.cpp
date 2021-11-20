#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("disjoint.in");
ofstream g("disjoint.out");

int N, M;
vector<int> father;
vector<int> height;


int represents(int curr)
{
    if(father[curr] == 0)
        return curr;
    
    int f = represents(father[curr]);
    father[curr] = f;
    return f;
}


void unite(int x, int y)
{
    if(height[x] < height[y])
        father[x] = y;
    else
        father[y] = x;

    if(height[x] == height[y])
        height[x] ++;
}


int main()
{
    f >> N >> M;
    father = vector<int> (N + 1);
    height = vector<int> (N + 1);

    int i, op, x, y;
    for(i = 1; i <= M; i++)
    {
        f >> op >> x >> y;
        if(op == 1)
        {
            unite(represents(x), represents(y));
        }
        else
            if(represents(x) == represents(y))
                g << "DA\n";
            else
                g << "NU\n";
    }
    return 0;
}