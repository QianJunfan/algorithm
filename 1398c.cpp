/* codeforces 1398c - good subarrays
 * Jan 18, 2026
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define _YES cout << "YES" << "\n"
#define _NO  cout << "NO"  << "\n"

void solve(void);

int main(void)
{
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        int t;
        cin >> t;

        while (t--)
                solve();

        return 0;
}

void solve(void)
{
        int n;
        cin >> n;

        string s;
        cin >> s;

        map<int, ll> m;

        m[0] = 1;

        ll p = 0;
        ll a = 0;

        for (int i = 1; i <= n; ++i) {
                int v = s[i-1] - '0';
                p += v;

                int t = p - i;

                a += m[t];

                m[t]++;
        }

        cout << a << "\n";
}
