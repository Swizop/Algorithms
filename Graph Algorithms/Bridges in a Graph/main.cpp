class Solution {
public:
    void critical(int curr, int f, vector<vector<int>>& edges, vector<vector<int>>& sol, vector<int>& level, vector<int>& upwards)
    {
        int i, x;
        for(i = 0; i < edges[curr].size(); i++)
        {
            x = edges[curr][i];
            if (level[x] == 0)
            {
                level[x] = upwards[x] = level[curr] + 1;
                critical(x, curr, edges, sol, level, upwards);
                if(upwards[curr] > upwards[x])
                    upwards[curr] = upwards[x];
            }
            else
                if(x != f && f != -1)
                    if(upwards[curr] > level[x])
                        upwards[curr] = level[x];
        }
        if(level[curr] == upwards[curr] && f != -1)
            sol.push_back(vector<int> {f, curr});
            
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> level = vector<int> (n);
        vector<int> upwards = vector<int> (n);
        vector<vector<int>> edges = vector<vector<int>> (n);
        
        int i, j;
        for(i = 0; i < connections.size(); i++)
        {
            edges[connections[i][0]].push_back(connections[i][1]);
            edges[connections[i][1]].push_back(connections[i][0]);
        }
        vector<vector<int>> sol;
        level[0] = upwards[0] = 1;
        critical(0, -1, edges, sol, level, upwards);
        return sol;
    }
};