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
