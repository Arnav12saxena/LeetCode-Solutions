class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        // dp = number of distinct subsequences including empty
        long long dp = 1;

        // last[c] = dp value before the previous occurrence of c
        vector<long long> last(26, 0);

        for (char c : s) {
            int x = c - 'a';

            long long newDp = (2 * dp - last[x] + MOD) % MOD;

            // For the next occurrence of c, this is the
            // value that must be subtracted.
            last[x] = dp;

            dp = newDp;
        }

        // Remove the empty subsequence.
        return (dp - 1 + MOD) % MOD;
    }
};