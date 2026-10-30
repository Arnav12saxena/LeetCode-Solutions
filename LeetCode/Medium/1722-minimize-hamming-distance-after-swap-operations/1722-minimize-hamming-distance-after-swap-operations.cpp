#include <vector>
#include <unordered_map>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } 
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        } 
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        DSU dsu(n);

        // Step 1: Build connected components
        for (auto& edge : allowedSwaps) {
            dsu.unite(edge[0], edge[1]);
        }

        // Step 2: Count source values inside each component
        unordered_map<int, unordered_map<int, int>> groupCount;

        for (int i = 0; i < n; i++) {
            int root = dsu.find(i);
            groupCount[root][source[i]]++;
        }

        // Step 3: Match target values from same component
        int ans = 0;

        for (int i = 0; i < n; i++) {
            int root = dsu.find(i);
            int val = target[i];

            if (groupCount[root][val] > 0) {
                groupCount[root][val]--;
            } else {
                ans++;
            }
        }

        return ans;
    }
};