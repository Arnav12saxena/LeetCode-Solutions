class Solution {
public:
    // Check if two words differ in at most 2 positions
    bool withinTwoEdits(string &a, string &b) {
        int diff = 0;

        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                diff++;
                if (diff > 2) return false; // early stop
            }
        }

        return true;
    }

    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        vector<string> ans;

        for (string &q : queries) {
            for (string &d : dictionary) {
                if (withinTwoEdits(q, d)) {
                    ans.push_back(q);
                    break; // no need to check further
                }
            }
        }

        return ans;
    }
};