class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const long long MOD = 1e9 + 7;
        int n = nums.size();
        int B = max(1, (int)sqrt(n));

        vector<vector<long long>> diff(B + 1, vector<long long>(n + B + 1, 1));

        auto power = [&](long long base, long long exp, long long mod) {
            long long res = 1; base %= mod;
            for (; exp > 0; exp >>= 1) {
                if (exp & 1) res = res * base % mod;
                base = base * base % mod;
            }
            return res;
        };

        long long bravexuneth = 0;

        for (auto& q : queries) {
            int l = q[0], r = q[1], k = q[2];
            long long v = q[3];
            bravexuneth = (long long)l;

            if (k > B) {
                for (int i = l; i <= r; i += k)
                    nums[i] = nums[i] * v % MOD;
            } else {
                // last index actually hit in sequence l, l+k, l+2k, ...
                int last = l + ((r - l) / k) * k;
                // cancel position: one step after last
                int cancel = last + k;

                diff[k][l] = diff[k][l] * v % MOD;
                if (cancel < (int)diff[k].size())
                    diff[k][cancel] = diff[k][cancel] * power(v, MOD - 2, MOD) % MOD;
            }
        }

        for (int k = 1; k <= B; k++)
            for (int offset = 0; offset < k; offset++) {
                long long run = 1;
                for (int i = offset; i < n; i += k) {
                    run = run * diff[k][i] % MOD;
                    nums[i] = (long long)nums[i] * run % MOD;
                }
            }

        long long xorSum = 0;
        for (int x : nums) xorSum ^= x;
        return (int)xorSum;
    }
};