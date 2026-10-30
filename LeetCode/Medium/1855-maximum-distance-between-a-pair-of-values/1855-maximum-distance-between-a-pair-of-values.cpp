class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        int n = nums1.size(), m = nums2.size();
        int ans = 0;

        // Two pointers approach
        while (i < n && j < m) {
            // valid pair condition
            if (nums1[i] <= nums2[j]) {
                ans = max(ans, j - i);
                j++; // try to increase distance
            } 
            else {
                i++; // move i forward to find smaller nums1[i]
            }
            // ensure i <= j
            if (i > j) j = i;
        }

        return ans;
    }
};