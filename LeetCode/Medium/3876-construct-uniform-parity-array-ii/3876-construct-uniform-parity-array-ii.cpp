class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        bool hasOdd= false;
        bool hasEven= false;

        int  mn= INT_MAX;

        for (int x: nums1){
            mn= min(mn, x);

            if (x%2==0)
            hasEven=true;
            else
            hasOdd=true;
        }
        if (!hasOdd || !hasEven)
            return true;
        return mn%2==1;
        
    }
};