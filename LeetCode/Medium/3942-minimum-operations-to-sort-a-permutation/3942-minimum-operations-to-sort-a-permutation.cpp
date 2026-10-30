class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int pos0 = 0;
        bool asc = true, desc = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) pos0 = i;
            int nx = nums[(i + 1) % n];
            if (nx != (nums[i] + 1) % n) asc = false;
            if (nx != (nums[i] - 1 + n) % n) desc = false;
        }
        if (!asc && !desc) return -1;

        int ans = INT_MAX;
        if (asc) {
            // rotate left pos0 times, or reverse + (n-pos0) left rotations + reverse
            int c = pos0;
            if (pos0 > 0) c = min(pos0, n - pos0 + 2);
            ans = min(ans, c);
        }
        if (desc) {
            // rotate left until descending ends at 0, then reverse
            int t = (pos0 + 1) % n;
            ans = min(ans, t + 1);
            // reverse first, then rotate left
            ans = min(ans, n - pos0);
        }
        return ans;
    }
};