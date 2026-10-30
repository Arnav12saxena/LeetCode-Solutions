class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {

        if (n == 0)
            return true;

        for (int i = 0; i < flowerbed.size(); i++) {

            if (flowerbed[i] == 0) {

                bool leftempty = (i == 0 || flowerbed[i - 1] == 0);
                bool rightempty = (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0);

                if (leftempty && rightempty) {
                    flowerbed[i] = 1;
                    n--;

                    if (n == 0)
                        return true;
                }
            }
        }

        return false;
    }
};