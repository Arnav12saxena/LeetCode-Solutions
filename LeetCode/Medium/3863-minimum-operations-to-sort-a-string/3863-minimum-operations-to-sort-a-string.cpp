
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Check if the string is already sorted.
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        // A string of length 2 cannot be changed because
        // sorting a single character does not change anything.
        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        bool firstMin = (s[0] == mn);
        bool lastMax = (s[n - 1] == mx);
        bool firstMax = (s[0] == mx);
        bool lastMin = (s[n - 1] == mn);

        // One operation is enough if the first character is
        // the minimum or the last character is the maximum.
        if (firstMin || lastMax) {
            return 1;
        }

        // Three operations are needed only when the first
        // character is the unique maximum and the last
        // character is the unique minimum.
        if (firstMax && lastMin &&
            count(s.begin(), s.end(), mx) == 1 &&
            count(s.begin(), s.end(), mn) == 1) {
            return 3;
        }

        // All other unsorted strings need two operations.
        return 2;
    }
};
