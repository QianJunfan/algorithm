/* Dec 13, 2025
 * */

/* lc0242 - valid anagram (brute force) */
#include <stdbool.h>
#include <string.h>

bool isAnagram_bf(char *s, char *t)
{
	if (strlen(s) != strlen(t))
		return false;

	int map_s[128] = {0};
	int map_t[128] = {0};
	
	while (*s != '\0') {
		map_s[*(s++)]++;
		map_t[*(t++)]++;
	}

	for (int i = 0; i < 128; i++) {
		if (map_s[i] != map_t[i])
			return false;
	}

	return true;
}


/* lc0010 - regular expression matching */
#include <stdbool.h>
#include <string.h>

bool matches(const char *s, const char *p, int i , int j )
{
	if (i == 0)
		return false;
	if (p[j-1] == '.')
		return true;
	
	return s[i-1] == p[j-1];
}

bool isMatch(const char *s, const char *p)
{
	int m = strlen(s);
	int n = strlen(p);
	
	bool **dp = (bool **)malloc((m+1) * sizeof(bool *));
	for (int i = 0; i <= m; i++)
		dp[i] = (bool *)calloc(n + 1, sizeof(bool));

	dp[0][0] = true;
	
	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (p[j-1] == '*') {
				dp[i][j] = dp[i][j-2];
				if (matches(s, p, i, j-1))
					dp[i][j] = dp[i][j] ||
						dp[i-1][j];
			}

			else if (matches(s, p, i, j))
				dp[i][j] = dp[i-1][j-1];
		}

	}

	bool r = dp[m][n];
	for (int i = 0; i <= m; i++)
		free(dp[i]);
	free(dp);

	return r;
}

/* this is a test */
/* this is yet another test */
