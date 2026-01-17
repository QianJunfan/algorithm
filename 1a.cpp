/* codeforces 1a - theatre square
 * Jan 18, 2026
 */

#include <iostream>

using namespace std;

int main(void)
{
        // Optimize standard stream performance
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        long long n, m, a;

        if (!(cin >> n >> m >> a))
                return 0;

        long long tn = (n + a - 1) / a;
        long long tm = (m + a - 1) / a;

        cout << tn * tm << endl;

        return 0;
}
