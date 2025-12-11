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



/* lc0168 - excel sheet column title */
#include <string.h>
#include <stdlib.h>

char *convertToTitle(int n)
{
	char *r = (char *)malloc(8);
	int idx = 0;
	char tmp[8];

	while (n > 0) {
		n--;
		int m = n % 26;
		tmp[idx++] = 'A' + m;
		n /= 26;
	}

	r[idx] = '\0';
	for (int i = 0; i < idx; i++)
		r[i] = tmp[idx - i - 1];

	return r;
}



/* lc0168 - excel sheet column number */
int titleToNumber(char *s)
{
	long long r = 0;
	for (int i =0; s[i] != '\0'; i++)
		r = (r * 26) + s[i] - 'A' + 1;
	return (int)r;
}

/* lc0168 - excel sheet column number (recursion) */
int titleToNumber_r(char *s)
{
	if (*s == '\0')
		return 0;
	int rest = titleToNumber(s + 1);
	int cur = *s - 'A' + 1;
	return cur + 26 * rest;
}



/* lc0205 - isomorphic strings (failed) */
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isIsomorphic_f(char *s, char *t)
{
	int map[128] = {0};
	for (int i = 0; s[i] != '\0'; i++)
		map[s[i]] = t[i];
	while (*s != '\0') {
		printf("%c %c\n", *s, *t);
		*s = map[*s];
		printf("%c %c\n", *s, *t);
		if (*(s) != *(t))
			return false;
		s++;
		t++;
	}

	return true;
}


/* lc0205 - isomorphic strings */
bool isIsomorphic(char *s, char *t)
{
	int map_s[128] = {0};
	int map_t[128] = {0};
	
	while (*s != '\0') {
		char cs = *s;
		char ct = *t;
		
		if (map_s[cs] == 0) {
			if (map_t[ct] != 0)
				return false;

			map_s[cs] = ct;
			map_t[ct] = cs;
		} else if (map_s[cs] != ct) {
			return false;
		}

		s++;
		t++;
	}
	return true;
}
