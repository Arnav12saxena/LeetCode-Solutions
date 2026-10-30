class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int, int>> a, b;

        // Store positions of 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j])
                    a.push_back({i, j});

                if (img2[i][j])
                    b.push_back({i, j});
            }
        }

        unordered_map<string, int> mp;
        int ans = 0;

        // Try matching every 1 in img1 with every 1 in img2
        for (auto [r1, c1] : a) {
            for (auto [r2, c2] : b) {

                int dr = r2 - r1;
                int dc = c2 - c1;

                string key = to_string(dr) + "," + to_string(dc);

                mp[key]++;
                ans = max(ans, mp[key]);
            }
        }

        return ans;
    }
};