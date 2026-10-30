#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    struct P {
        ll x, y;
        ll pos;   // position on perimeter in clockwise order
        ll s1;    // x + y
        ll s2;    // x - y
    };

    // map boundary point -> perimeter position [0 .. 4 * side)
    ll getPos(ll side, ll x, ll y) {
        if (y == 0) return x;                         // bottom
        if (x == side) return side + y;               // right
        if (y == side) return 3 * side - x;           // top
        return 4 * side - y;                          // left
    }

    // Manhattan distance on boundary points
    ll dist(const P& a, const P& b) {
        return llabs(a.x - b.x) + llabs(a.y - b.y);
    }

    bool canPick(vector<P>& pts, int k, ll need, ll side) {
        int n = pts.size();

        /*
           Important fact:

           After sorting points by perimeter order, for a fixed first point,
           greedily taking the next valid point works.

           For Manhattan distance on a square boundary, for a fixed point,
           the set of points violating distance < need behaves monotonically
           in perimeter order, so binary search + greedy is sufficient.
        */

        // duplicate array for circular handling
        vector<P> a = pts;
        for (int i = 0; i < n; ++i) {
            P t = pts[i];
            t.pos += 4LL * side;
            a.push_back(t);
        }

        // next[i] = first index j > i with perimeter gap >= need
        vector<int> nxt(2 * n, 2 * n);
        int j = 0;
        for (int i = 0; i < 2 * n; ++i) {
            j = max(j, i + 1);
            while (j < 2 * n && a[j].pos - a[i].pos < need) j++;
            nxt[i] = j;
        }

        for (int st = 0; st < n; ++st) {
            vector<int> chosen;
            chosen.push_back(st);

            int cur = st;
            while ((int)chosen.size() < k) {
                cur = nxt[cur];
                if (cur >= st + n) break; // exceeded one full cycle
                chosen.push_back(cur);
            }

            if ((int)chosen.size() < k) continue;

            // verify every selected pair with the first point
            // (greedy already guarantees local order constraints)
            bool ok = true;
            const P& first = a[chosen[0]];
            for (int idx = 1; idx < k; ++idx) {
                if (dist(first, a[chosen[idx]]) < need) {
                    ok = false;
                    break;
                }
            }

            if (ok) return true;
        }

        return false;
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<P> pts;
        for (auto &p : points) {
            ll x = p[0], y = p[1];
            pts.push_back({
                x,
                y,
                getPos(side, x, y),
                x + y,
                x - y
            });
        }

        sort(pts.begin(), pts.end(),
             [](const P& a, const P& b) {
                 return a.pos < b.pos;
             });

        ll lo = 0, hi = 2LL * side; // max Manhattan distance on boundary

        while (lo < hi) {
            ll mid = (lo + hi + 1) >> 1;
            if (canPick(pts, k, mid, side))
                lo = mid;
            else
                hi = mid - 1;
        }

        return (int)lo;
    }
};