
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int minDist = INT_MAX;
        int first = -1;
        int prevCritical = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next = curr->next;

        int index = 1;

        while (next != nullptr) {
            // Check if curr is a critical point
            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (isCritical) {
                if (first == -1) {
                    // First critical point
                    first = index;
                    prevCritical = index;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, index - prevCritical);
                    prevCritical = index;
                }
            }

            prev = curr;
            curr = next;
            next = next->next;
            index++;
        }

        // Fewer than two critical points
        if (first == -1 || first == prevCritical) {
            return {-1, -1};
        }

        int maxDist = prevCritical - first;

        return {minDist, maxDist};
    }
};