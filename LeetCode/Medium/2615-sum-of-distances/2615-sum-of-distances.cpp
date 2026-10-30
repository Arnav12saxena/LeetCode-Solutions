#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;

        // Store all indices for each value
        for (int i = 0; i < nums.size(); i++) {
            pos[nums[i]].push_back(i);
        }

        vector<long long> ans(nums.size(), 0);

        // Process each group of same values
        for (auto& entry : pos) {
            vector<int>& indices = entry.second;
            int n = indices.size();

            // Prefix sum of indices
            vector<long long> prefix(n + 1, 0);
            for (int i = 0; i < n; i++) {
                prefix[i + 1] = prefix[i] + indices[i];
            }

            for (int i = 0; i < n; i++) {
                int idx = indices[i];

                // Left contribution
                long long left = 1LL * idx * i - prefix[i];

                // Right contribution
                long long right =
                    (prefix[n] - prefix[i + 1]) -
                    1LL * idx * (n - i - 1);

                ans[idx] = left + right;
            }
        }

        return ans;
    }
};