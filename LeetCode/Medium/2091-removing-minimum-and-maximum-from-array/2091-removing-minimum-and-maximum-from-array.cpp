class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int mn = 0, mx = 0;

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[mn]) mn = i;
            if (nums[i] > nums[mx]) mx = i;
        }

        int left = min(mn, mx);
        int right = max(mn, mx);

        return min({
            right + 1,              // both from front
            n - left,               // both from back
            left + 1 + n - right    // one from each side
        });
    }
};