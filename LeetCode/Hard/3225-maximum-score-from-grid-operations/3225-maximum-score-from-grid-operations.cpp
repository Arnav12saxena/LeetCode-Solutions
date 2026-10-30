class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // prefix[j][i] = grid[0][j] + ... + grid[i-1][j]
        vector<vector<long long>> pre(n, vector<long long>(n + 1, 0));
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                pre[j][i + 1] = pre[j][i] + grid[i][j];
        
        auto S = [&](int col, int lo, int hi) -> long long {
            if (lo >= hi) return 0LL;
            return pre[col][hi] - pre[col][lo];
        };
        
        // dp[h][t]:
        //   h = fill height of current column (0..n)
        //   t = 0: the white cells in col j below h have NOT yet scored
        //          (no right-neighbor confirmed yet)
        //   t = 1: col j's white cells that can see right-black have scored
        //          (right neighbor col j+1 was taller, so rows [h, col_j+1_height)
        //           of col j already got credit — but we fold that into the
        //           transition, so t=1 just means "prev col already got its score")
        //
        // Simpler restatement used in the editorial:
        // dp[h][0] = best score up to col j, col j has height h,
        //            and col j's white cells have NOT scored from a right neighbor
        // dp[h][1] = best score up to col j, col j has height h,
        //            and col j's white cells HAVE scored from a right neighbor
        //            (meaning we already added col j's contribution when
        //             transitioning from col j-1 to col j with col j-1 taller)
        
        const long long NEG = LLONG_MIN / 2;
        // [height 0..n][scored 0/1]
        vector<array<long long, 2>> dp(n + 1, {0LL, NEG});
        // Col 0: height h, no right neighbor yet → t=0, score=0
        //        t=1 impossible (no left neighbor to have scored us)
        
        for (int j = 0; j < n - 1; j++) {
            vector<array<long long, 2>> ndp(n + 1, {NEG, NEG});
            
            // Transition: prev = col j height, curr = col j+1 height
            // Case A: curr > prev
            //   - col j white cells at [prev, curr) NOW score from right-black neighbor
            //     But only if they haven't scored yet (t=0). If t=1 they already scored.
            //   - col j+1 gets no left-neighbor score (it's taller, so above prev is black in j)
            //     Wait — col j+1's rows [0,curr) are black. col j's rows [0,prev) are black.
            //     col j+1 white rows start at curr. None of them see col j as black at same row.
            //   → score added = S(j, prev, curr) if t==0, else 0
            //   → ndp[curr][0] = max over prev: dp[prev][t] + (t==0 ? S(j,prev,curr) : 0)
            //
            // Case B: curr <= prev
            //   - col j+1 white cells at [curr, prev) see col j as left-black neighbor → score!
            //   - col j's white cells at [prev, n) see nothing from right (curr<=prev means
            //     col j+1 is not black at those rows) — they remain unscored from right
            //   → score added = S(j+1, curr, prev)
            //   → ndp[curr][0]: col j+1 white cells scored from left, but their right unknown
            //                    → t=1 for col j+1 means "already got left-score"
            //   Wait, t tracks whether the CURRENT column's white cells scored.
            //   After transition, current column becomes j+1.
            //   ndp[curr][1] = col j+1's white cells at [curr,prev) scored (from left/col j)
            //   ndp[curr][0] = col j+1's white cells haven't scored yet (curr >= prev case)
            
            // Let's build prefix/suffix max arrays for O(n) transitions.
            
            // For Case A (curr > prev), ndp[curr][0]:
            //   from dp[prev][0]: dp[prev][0] + S(j, prev, curr)
            //                   = dp[prev][0] - S(j,0,prev) + S(j,0,curr)
            //   from dp[prev][1]: dp[prev][1] + 0  (already scored, no new score)
            //   Take max over prev in [0, curr]
            
            // For Case B (curr <= prev), ndp[curr][1]:
            //   from dp[prev][0] or dp[prev][1]: + S(j+1, curr, prev)
            //   = dp[prev][t] + S(j+1,0,prev) - S(j+1,0,curr)
            //   Take max over prev in [curr, n], for both t values
            
            // Precompute:
            // pA0[k] = max over prev in [0,k] of (dp[prev][0] - S(j, 0, prev))
            // pA1[k] = max over prev in [0,k] of (dp[prev][1])
            // sB[k]  = max over prev in [k,n] of max(dp[prev][0], dp[prev][1]) + S(j+1,0,prev)
            
            vector<long long> pA0(n + 1, NEG), pA1(n + 1, NEG), sB(n + 2, NEG);
            
            pA0[0] = (dp[0][0] == NEG) ? NEG : dp[0][0] - S(j, 0, 0);
            pA1[0] = dp[0][1];
            for (int h = 1; h <= n; h++) {
                long long a0 = (dp[h][0] == NEG) ? NEG : dp[h][0] - S(j, 0, h);
                long long a1 = dp[h][1];
                pA0[h] = max(pA0[h - 1], a0);
                pA1[h] = max(pA1[h - 1], a1);
            }
            
            for (int h = n; h >= 0; h--) {
                long long b = NEG;
                if (dp[h][0] != NEG) b = max(b, dp[h][0] + S(j + 1, 0, h));
                if (dp[h][1] != NEG) b = max(b, dp[h][1] + S(j + 1, 0, h));
                sB[h] = (h == n) ? b : max(sB[h + 1], b);
            }
            
            for (int curr = 0; curr <= n; curr++) {
                // Case A: prev in [0, curr] → ndp[curr][0]
                {
                    long long best = NEG;
                    long long sc = S(j, 0, curr);
                    if (pA0[curr] != NEG) best = max(best, pA0[curr] + sc);
                    if (pA1[curr] != NEG) best = max(best, pA1[curr]); // t=1: no extra score
                    ndp[curr][0] = max(ndp[curr][0], best);
                }
                // Case B: prev in [curr, n] → ndp[curr][1]
                {
                    long long best = NEG;
                    long long sc = S(j + 1, 0, curr);
                    if (sB[curr] != NEG) best = max(best, sB[curr] - sc);
                    ndp[curr][1] = max(ndp[curr][1], best);
                }
            }
            
            dp = ndp;
        }
        
        long long ans = 0;
        for (int h = 0; h <= n; h++) {
            if (dp[h][0] != NEG) ans = max(ans, dp[h][0]);
            if (dp[h][1] != NEG) ans = max(ans, dp[h][1]);
        }
        return ans;
    }
};