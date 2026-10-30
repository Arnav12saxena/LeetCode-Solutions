class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        
        // Step 1: Store indices of each value
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }
        
        int ans = INT_MAX;
        
        // Step 2: Process each value group
        for (auto &it : mp) {
            vector<int> &indices = it.second;
            
            if (indices.size() < 3) continue;
            
            // Step 3: Check consecutive triplets
            for (int i = 0; i + 2 < indices.size(); i++) {
                int first = indices[i];
                int third = indices[i + 2];
                
                int distance = 2 * (third - first);
                ans = min(ans, distance);
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};