#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Expand factory slots
        vector<int> slots;
        for (auto &f : factory) {
            int pos = f[0], limit = f[1];
            for (int i = 0; i < limit; i++) {
                slots.push_back(pos);
            }
        }

        int n = robot.size();
        int m = slots.size();

        const long long INF = 1e18;
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));

        // Base case
        for (int j = 0; j <= m; j++) {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Skip this slot
                dp[i][j] = dp[i][j - 1];

                // Assign robot i-1 to slot j-1
                dp[i][j] = min(dp[i][j],
                    dp[i - 1][j - 1] + abs(robot[i - 1] - slots[j - 1]));
            }
        }

        return dp[n][m];
    }
};