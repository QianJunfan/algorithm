/* codeforces 58a - chat room
 * Jan 18, 2026
 */
#include <bits/stdc++.h>
using namespace std;

int main(void)
{
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        string s;
        string t = "hello";

        if (!(cin >> s))
                return 0;
 
        int j = 0;

        for (int i = 0; i < s.length(); ++i) {
                if (s[i] == t[j])
                        ++j;

                if (j == 5)
                        break;
        }

        if (j == 5)
                cout << "YES" << endl;
        else
                cout << "NO" << endl;

        return 0;
}
