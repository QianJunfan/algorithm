/* codeforces 1940c_2p - sum of cubes (2p)
 * Jan 18, 2026
 */
#include <bits/stdc++.h>
using namespace std;

#define _YES cout << "YES" << "\n"
#define _NO  cout << "NO"  << "\n"

#define MAX 10001

typedef long long ll;

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
        ll x;
        cin >> x;

        ll l = 1, r = MAX;
        while (l <= r) {
                ll cur = l * l * l + r * r * r;
                if (cur == x) {
                        _YES;
                        return;
                } else if (cur > x) {
                        r--;
                } else {
                        l++;
                }
        }
        _NO;
}
