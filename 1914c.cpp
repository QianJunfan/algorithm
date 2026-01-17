/* codeforces 1914c - quests
 * Jan 18, 2026
 */
#include <bits/stdc++.h>

using namespace std;

void solve(void)
{
        int n;
        long long k;
        cin >> n >> k;

        vector<int> a(n), b(n);

        for (int& x : a) cin >> x;
        for (int& x : b) cin >> x;
 
        long long ans = 0;
        long long sum_a = 0;
        int max_b = 0;

        for (int i = 0; i < n && i < k; ++i) {
                sum_a += a[i];
                max_b = max(max_b, b[i]);

                long long tot = sum_a + (k - i - 1) * max_b;
                
                ans = max(ans, tot);
        }

        cout << ans << "\n";
}

int main(void)
{
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        
        int n;
        cin >> n;

        while (n--)
                solve();

        return 0;
}
