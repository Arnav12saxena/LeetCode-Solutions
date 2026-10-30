class Solution {
public:
    int mirrorDistance(int n) {
        int rev=0;
        int num=n;

        while (num>0){
            int digit= num%10;
            rev=rev*10 +digit;
            num /=10;
        }
        return abs(n- rev);
    }
};