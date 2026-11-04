class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // Two multisets to maintain the sliding window median
        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            // Balance the two multisets
            if (low.size() > high.size() + 1) {
                int v = *low.rbegin();
                low.erase(prev(low.end()));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            } 
            else if (low.size() < high.size()) {
                int v = *high.begin();
                high.erase(high.begin());
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            // Rebalance
            if (low.size() > high.size() + 1) {
                int v = *low.rbegin();
                low.erase(prev(low.end()));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }
            else if (low.size() < high.size()) {
                int v = *high.begin();
                high.erase(high.begin());
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        // Cost of making the current window equal
        auto getCost = [&]() -> long long {
            long long median = *low.rbegin();

            long long leftCost =
                median * (long long)low.size() - sumLow;

            long long rightCost =
                sumHigh - median * (long long)high.size();

            return leftCost + rightCost;
        };

        // Calculate cost of every window of size x
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP: dp[j][i] = minimum cost to select j
        // non-overlapping windows using first i elements.

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = j * x; i <= n; i++) {

                // Do not select a window ending at i-1
                dp[j][i] = dp[j][i - 1];

                // Select window [i-x, i-1]
                dp[j][i] = min(
                    dp[j][i],
                    dp[j - 1][i - x] + cost[i - x]
                );
            }
        }

        return dp[k][n];
    }
};