/* Dec 11, 2025 
 * I've spent too much time writing my window manager 
 * and haven't gotten around to doing any algorithmic problems.
 * That's a sin...
 * */

/* lc0013 - roman to integer */
int val(char r)
{
	switch(r) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		default: return 0;
	}
}
int romanToInt (char *s)
{
	int r = 0;
	int len = strlen(s);

	for (int i = 0; i < len; i++) {
		int s1 = val(s[i]);

		if (i + 1 < len) {
			int s2 = val(s[i+1]);
			if (s1 < s2)
				r -= s1;
			else
				r += s1;
		} else {
			r += s1;
		}
	}

	return r;
}


/* lc0014 - longest common prefix */
#include <stdlib.h>
#include <string.h>
char *longestCommonPrefix(char **s, int size)
{
	char *r = strdup(s[0]); 	

	for (int i = 1; i < size; i++) {
		char *c = s[i];
		char *m = r;
		while (*m != '\0') {
			if (*c == *m) {
				c++;
				m++;
			} else {
				*m = '\0';
				break;
			}
		}
	}

	return r;
}


/* lc0020 - valid parentheses */
#include <stdbool.h>

bool isValid(char *s)
{
	char st[10000];
	int  p = 0;
	
	while (*s != '\0') {
		if (*s == '(' || *s == '[' || *s == '{') 
			st[p++] = *s;
		else if ((*s == ')' || *s == ']' || *s == '}') 
			&& p == 0)
			break;
		else if (*s == st[p-1] + 2 || *s == st[p-1] + 1) 
			p--;
		else
			return false;
		s++;
	}
	
	return p == 0 ? true : false;
}


/* lc0028 - find the index of the first occurrence in a string */
int strStr(char *heystack, char *n) 
{
	if (*n == '\0')
		return 0;

	char *h = heystack;
	int idx = 0;

	while (*h != '\0') {
		char *th = h;
		char *tn = n;

		while (*th != '\0' && *tn != '\0' && *th == *tn) {
			th++;
			tn++;
		}

		if (*tn == '\0')
			return idx;

		h++;
		idx++;
	}

	return -1;
}


/* lc0028 - find the index of the ... (faster) */
#include <stdint.h>

int strStr(char *h, char *n)
{
	int idx[10000];	
	int cnt = 0;
	int lh = strlen(h);
	int ln = strlen(n);
	
	if (ln == 0)
		return 0;
	if (lh < ln)
		return -1;

	for (int i = 0; i <= lh - ln; i++) {
		if (h[i] == n[0] && h[i + ln - 1] == n[ln - 1])
			idx[cnt++] = i;
	}

	for (int i = 0; i < cnt; i++) {
		int start = idx[i];
		int j = 0;
		while (j < ln && h[start + j] == n[j])
			j++;

		if (j == ln)
			return start;
	}

	return -1;
}

