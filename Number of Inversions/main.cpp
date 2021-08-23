#include <iostream>
#include <fstream>

using namespace std;


int main()
{
    ifstream f("in.txt");
    int n;
    int *v;
    f >> n;
    v = new int[n + 1];
    for(int i = 1; i <= n; i++)
        f >> v[i];
    
    return 0;
}