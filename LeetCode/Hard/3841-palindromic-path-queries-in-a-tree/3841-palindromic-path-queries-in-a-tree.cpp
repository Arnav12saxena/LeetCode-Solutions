class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(n, vector<int>(20, 0));
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[u][0] = p;

            for (int j = 1; j < 20; j++)
                up[u][j] = up[up[u][j - 1]][j - 1];

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer++;
        };

        dfs(0, 0);

        auto isAncestor = [&](int u, int v) {
            return tin[u] <= tin[v] && tout[v] <= tout[u];
        };

        auto lca = [&](int u, int v) {
            if (isAncestor(u, v)) return u;
            if (isAncestor(v, u)) return v;

            for (int j = 19; j >= 0; j--) {
                if (!isAncestor(up[u][j], v))
                    u = up[u][j];
            }

            return up[u][0];
        };

        // Fenwick tree storing XOR masks over Euler entry positions.
        vector<int> bit(2 * n + 2, 0);

        auto add = [&](int i, int val) {
            for (i++; i < (int)bit.size(); i += i & -i)
                bit[i] ^= val;
        };

        auto prefix = [&](int i) {
            int res = 0;
            for (i++; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        vector<int> mask(n);

        for (int u = 0; u < n; u++) {
            mask[u] = 1 << (s[u] - 'a');
            add(tin[u], mask[u]);
            add(tout[u], mask[u]);
        }

        auto rootMask = [&](int u) {
            return prefix(tin[u]);
        };

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newMask = 1 << (c - 'a');
                int delta = mask[u] ^ newMask;

                add(tin[u], delta);
                add(tout[u], delta);

                mask[u] = newMask;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int pathMask = rootMask(u) ^ rootMask(v) ^ mask[w];

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};