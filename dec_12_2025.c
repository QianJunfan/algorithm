/* Dec 12, 2025
 *
 * */

/* lc0058 - length of last word */
#include <string.h>

int lengthOfLastWord(char *s)
{
	int l = strlen(s);
	int r = 0;
	for (int i = l - 1; i >= 0; i--) {
		while (i >= 0 && s[i] == ' ')
			i--;
		while (i >= 0 && s[i] != ' ') {
			i--;
			r++;
		}

		return r;
	}
	return 0;
}


/* lc0067 - add binary */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *addBinary(char *a, char *b)
{
	int l_a = strlen(a);
	int l_b = strlen(b);
	int l_r = (l_a > l_b ? l_a : l_b) + 1;
	char *r = (char *)malloc((l_r + 1) * sizeof(char));

	int i = l_a - 1;
	int j = l_b - 1;
	int k = l_r;
	r[k--] = '\0';
	int c = 0;
	while (i >= 0 || j >= 0 || c) {
		int sum = c;
		if (i >= 0) sum += a[i--] - '0';
		if (j >= 0) sum += b[j--] - '0';
		if (k < 0)
			break;
		r[k--] = (sum % 2) + '0';
		c = sum / 2;
	}

	if (k == -1) 
		return r;
	else 
		return r + 1;
}


/* lc0125 - valid palindrome */
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isPalindrome(char *s)
{
	if (s == NULL || *s == '\0')
		return true;

	char *l = s;
	char *r = s + strlen(s) - 1;
	
	while (l < r) {
		while (l < r && !isalnum(*l))
			l++;
		while (l < r && !isalnum(*r))
			r--;
		
		if (l >= r)
			break;

		if (tolower(*l) != tolower(*r))
			return false;
		l++;
		r--;
	}
	return true;
}
