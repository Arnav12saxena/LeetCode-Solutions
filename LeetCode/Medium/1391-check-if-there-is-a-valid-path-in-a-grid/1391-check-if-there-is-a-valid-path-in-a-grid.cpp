class Solution {
public:
    // Directions: left, right, up, down
    vector<vector<int>> dirs = {
        {0, -1},   // left
        {0, 1},    // right
        {-1, 0},   // up
        {1, 0}     // down
    };

    // For each street type, store allowed directions
    unordered_map<int, vector<int>> mp = {
        {1, {0, 1}}, // left, right
        {2, {2, 3}}, // up, down
        {3, {0, 3}}, // left, down
        {4, {1, 3}}, // right, down
        {5, {0, 2}}, // left, up
        {6, {1, 2}}  // right, up
    };

    // Opposite direction mapping
    vector<int> opposite = {1, 0, 3, 2};

    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        queue<pair<int, int>> q;
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            // Reached destination
            if (x == m - 1 && y == n - 1)
                return true;

            int type = grid[x][y];

            // Try all possible directions from current cell
            for (int d : mp[type]) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];

                // Boundary check
                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                if (vis[nx][ny])
                    continue;

                int nextType = grid[nx][ny];

                // Check if next cell connects back
                bool valid = false;
                for (int nd : mp[nextType]) {
                    if (nd == opposite[d]) {
                        valid = true;
                        break;
                    }
                }

                if (valid) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        return false;
    }
};