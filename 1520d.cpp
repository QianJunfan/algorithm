/* codeforces 1520d - same differences
 * Jan 18, 2026
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define _yes cout << "yes" << "\n"
#define _no  cout << "no"  << "\n"

void solve(void)
{
        int n;
        cin >> n;

        map<int, ll> c;
        ll a = 0;

        for (int i = 0; i < n; ++i) {
                int b;
                cin >> b;
                int t = b - i;

                a += c[t];
                c[t]++;
        }
        
        cout << a << "\n";
}

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
