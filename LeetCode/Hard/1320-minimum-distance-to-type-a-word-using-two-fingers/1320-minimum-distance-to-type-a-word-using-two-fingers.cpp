class Solution {
public:
    int minimumDistance(string word) {
        // distance between two characters
        auto dist = [](int a, int b) {
            if (a == -1) return 0;
            int x1 = a / 6, y1 = a % 6;
            int x2 = b / 6, y2 = b % 6;
            return abs(x1 - x2) + abs(y1 - y2);
        };

        int n = word.size();
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = word[i] - 'A';

        // dp[j] = max saved distance if second finger is at letter j
        vector<int> dp(26, 0);

        for (int i = 0; i < n - 1; i++) {
            int cur = arr[i];
            int nxt = arr[i + 1];

            vector<int> new_dp(dp);

            for (int j = 0; j < 26; j++) {
                int gain = dist(cur, nxt) - dist(j, nxt);
                new_dp[cur] = max(new_dp[cur], dp[j] + gain);
            }

            dp = new_dp;
        }

        // total distance using one finger
        int total = 0;
        for (int i = 0; i < n - 1; i++) {
            total += dist(arr[i], arr[i + 1]);
        }

        int max_saved = *max_element(dp.begin(), dp.end());
        return total - max_saved;
    }
};