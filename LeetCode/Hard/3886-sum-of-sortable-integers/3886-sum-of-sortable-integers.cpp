class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;
            int prev = 0;
            bool hasPrev = false;

            for (int i = 0; i < n && ok; i += k) {
                int descents = 0;
                int start = i;

                // Count descents in the circular block.
                for (int j = 0; j < k; j++) {
                    int cur = i + j;
                    int nxt = i + (j + 1) % k;

                    if (nums[cur] > nums[nxt]) {
                        descents++;
                        start = nxt;
                    }
                }

                // More than one descent means no sorted rotation exists.
                if (descents > 1) {
                    ok = false;
                    break;
                }

                int first = nums[start];
                int last = nums[i + (start - i + k - 1) % k];

                // Ensure blocks join in non-decreasing order.
                if (hasPrev && prev > first) {
                    ok = false;
                    break;
                }

                prev = last;
                hasPrev = true;
            }

            if (ok) ans += k;
        }

        return ans;
    }
};