class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        
        // Step 1: Store indices
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }
        
        int ans = INT_MAX;
        
        // Step 2: Process each value
        for (auto &p : mp) {
            vector<int> &idx = p.second;
            
            // Need at least 3 occurrences
            if (idx.size() < 3) continue;
            
            // Step 3: Check consecutive triplets
            for (int i = 0; i + 2 < idx.size(); i++) {
                int dist = 2 * (idx[i+2] - idx[i]);
                ans = min(ans, dist);
            }
        }
        
        // Step 4: If no valid triplet
        return (ans == INT_MAX) ? -1 : ans;
    }
};