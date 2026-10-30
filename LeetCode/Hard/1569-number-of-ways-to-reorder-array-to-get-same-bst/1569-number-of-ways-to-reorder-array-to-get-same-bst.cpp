
class Solution {
public:
    static const int MOD = 1e9 + 7;
    long long choose[1001][1001];

    int solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;
        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long waysLeft = solve(left);
        long long waysRight = solve(right);

        long long ways = choose[n - 1][left.size()];
        ways = ways * waysLeft % MOD;
        ways = ways * waysRight % MOD;

        return ways;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i <= n; i++) {
            choose[i][0] = choose[i][i] = 1;

            for (int j = 1; j < i; j++) {
                choose[i][j] =
                    (choose[i - 1][j - 1] +
                     choose[i - 1][j]) % MOD;
            }
        }

        return (solve(nums) - 1 + MOD) % MOD;
    }
};
