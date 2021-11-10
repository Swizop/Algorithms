#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("havel.in");

int main()
{
    int i, x, n, j;
    f >> n;
    vector<int> degrees;
    for(i = 1; i <= n; i++)
    {
        f >> x;
        degrees.push_back(x);
    }

    while(true)
    {
        sort(degrees.begin(), degrees.end());
        i = degrees.size() - 1;
        if(degrees[i] == 0)     // every node has degree 0 so the graph can be made
        {
            cout << "Yes.";
            break;
        }
        j = i - 1;
        while(j >= 0 && degrees[i] > 0)
        {
            degrees[j]--;
            degrees[i]--;
            if(degrees[j] < 0)
            {
                cout << "No!";
                return 0;
            }
            j--;
        }
        if(j == -1 && degrees[i] > 0)
        {
            cout << "No!";
            break;
        }
        degrees.pop_back();
    }
    return 0;
}