/* codeforces 1490c - sum of cubes
 * Jan 18, 2026
 */
#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

unordered_set<long long> tab;

void pre()
{
        for (long long i = 1; i <= MAX; i++)
                tab.insert(i * i * i);
}

void solve()
{
        long long x;
        cin >> x;

        for (long long i = 1; i * i * i < x; ++i) {
                long long a = i * i * i;

                if (tab.count(x - a)) {
                        cout << "YES" << endl;
                        return;
                }
        }

        cout << "NO" << endl;
}

int main(void)
{
        ios::sync_with_stdio(false);
        cin.tie(NULL); 

        pre();

        int t;
        cin >> t;
        while (t--)
                solve();

        return 0;
}
