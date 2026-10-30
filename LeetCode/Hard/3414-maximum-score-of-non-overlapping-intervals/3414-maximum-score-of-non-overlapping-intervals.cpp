class Solution {
public:
    struct Node {
        long long score = 0;
        vector<int> ids;
    };

    bool better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            return x[0] < y[0];
        });

        // rights[i] = right endpoint of sorted interval i
        vector<long long> rights(n);
        for (int i = 0; i < n; i++)
            rights[i] = a[i][1];

        /*
            prev[i] = number of intervals before i
                      whose right endpoint < a[i].left

            Therefore, if we take interval i,
            the previous DP state is dp[prev[i]][k-1].
        */
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            prev[i] =
                lower_bound(rights.begin(),
                            rights.begin() + i,
                            a[i][0])
                - rights.begin();
        }

        /*
            dp[i][k] =
            best answer using the first i intervals
            and choosing at most k intervals.

            i ranges from 0 to n.
            k ranges from 0 to 4.
        */
        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        for (int i = 1; i <= n; i++) {

            // Interval index in sorted array
            int j = i - 1;

            for (int k = 0; k <= 4; k++) {

                // Option 1: don't take interval j
                dp[i][k] = dp[i - 1][k];

                // Option 2: take interval j
                if (k > 0) {
                    Node candidate = dp[prev[j]][k - 1];

                    candidate.score += a[j][2];
                    candidate.ids.push_back((int)a[j][3]);

                    // IDs must be sorted for lexicographical comparison
                    sort(candidate.ids.begin(), candidate.ids.end());

                    if (better(candidate, dp[i][k])) {
                        dp[i][k] = candidate;
                    }
                }
            }
        }

        return dp[n][4].ids;
    }
};