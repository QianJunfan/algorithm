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
