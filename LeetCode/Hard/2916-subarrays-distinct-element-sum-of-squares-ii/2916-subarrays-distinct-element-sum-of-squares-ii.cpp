
class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum;
        long long sumSq;
        long long lazy;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;

        tree[node].sumSq =
            (tree[node].sumSq + 2 * val * tree[node].sum % MOD
             + len % MOD * val % MOD * val % MOD) % MOD;

        tree[node].sum = (tree[node].sum + len * val) % MOD;
        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr,
                long long val) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;

        tree[node].sumSq =
            (tree[node * 2].sumSq + tree[node * 2 + 1].sumSq) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, {0, 0, 0});

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];

            // Increase distinct counts of subarrays
            // starting after the previous occurrence.
            update(1, 0, n - 1, prev + 1, i, 1);

            last[nums[i]] = i;

            // Sum of squared distinct counts for subarrays
            // ending at index i.
            ans = (ans + tree[1].sumSq) % MOD;
        }

        return ans;
    }
};
