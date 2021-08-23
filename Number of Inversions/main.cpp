#include <iostream>
#include <fstream>

using namespace std;


int merge(int* w, int l, int m, int r)
{
    int k = m + 1, x = l;
    int* aux = new int[r - l + 1];
    int end = 0, s = 0;
    while(l <= m && k <= r)
    {
        if(w[l] <= w[k])
            aux[end++] = w[l++];
        else
        {
            s += m - l + 1;                     //the number on the right is smaller than the entire left sequence
            aux[end++] = w[k++];
        }
    }

    while(l <= m)
        aux[end++] = w[l++];
    while(k <= r)
        aux[end++] = w[k++];

    end = 0;
    for(k = x; k <= r; k++)
        w[k] = aux[end++];

    return s;
}


int merge_inversions(int* w, int l, int r)
{
    if(l >= r)
        return 0;
    int m = l + (r - l) / 2;
    return merge_inversions(w, l, m) + merge_inversions(w, m + 1, r) + merge(w, l, m, r);
}


int main()
{
    ifstream f("in.txt");
    int n;
    int *v;
    f >> n;
    v = new int[n + 1];
    for(int i = 1; i <= n; i++)
        f >> v[i];
    
    
    int *w = new int[n + 1];
    for(int i = 1; i <= n; i++)
        w[i] = v[i];
    cout << merge_inversions(w, 1, n);
    return 0;
}