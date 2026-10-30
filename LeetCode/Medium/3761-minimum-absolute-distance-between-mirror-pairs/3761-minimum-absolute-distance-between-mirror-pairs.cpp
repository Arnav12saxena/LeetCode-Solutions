#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reverseNum(int x) {
        int rev = 0;
        while (x > 0) {
            rev = rev * 10 + (x % 10);
            x /= 10;
        }
        return rev;
    }

    int minMirrorPairDistance(vector<int>& nums) {
        unordered_map<int, int> mp;
        int ans = INT_MAX;

        for (int j = 0; j < nums.size(); j++) {
            
            // ✅ Check if current number was seen as reverse before
            if (mp.find(nums[j]) != mp.end()) {
                ans = min(ans, j - mp[nums[j]]);
            }

            // ✅ Store reversed version
            int rev = reverseNum(nums[j]);
            mp[rev] = j;
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};