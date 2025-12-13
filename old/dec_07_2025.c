/* Dec 7, 2025 
 * I'm trying to complete all the string-related LeetCode problems, 
 * and this is day one. 
 * */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* lc0003 - longest substring without repeating characters (slide-win) */
int lengthOfLongestSubstring_sw(char *s)
{
	if (s == NULL || *s == '\0')
		return 0;	
	int map[128] = {0};
	int max = 0;
	int start = 0;
	for (int end = 0; s[end] != '\0'; end++) {
		char cur = s[end];

		if (map[cur] > start)
			start = map[cur];

		map[cur] = end + 1;

		int cur_len = end - start + 1;
		
		max = (max > cur_len) ? max : cur_len;
	}
	
	return max;
}


/* lc0005 - longest palindromic substring (expand around center failed) */
char *longestPalindrome_f(char *s)
{
	char *str  = s;
	int   cnt  = 1;

	for (int i = 0; s[i] != '\0'; i++) {
		int   tmp0 = 1;
		char *ptr0 = s + i;
		for (int j = 1; i - j >= 0 && s[i + j] != '\0'; j++) {
			if (s[i-j] == s[i+j]) {
				tmp0 += 2;
				ptr0 = s + i - j;
			} else {
				break;
			}
		}

		int   tmp1  = 0;
		char  *ptr1 = NULL;
		for (int j = 0; i - j >= 0 && s[i + j + 1] != '\0'; j++) {
			if (s[i-j] == s[i+j+1]) {
				tmp1 += 2;
				ptr1 = s + i - j;
			} else {
				break;
			}
		}
		
		int  tmp = (tmp0 > tmp1) ? tmp0 : tmp1;
		char *ptr = NULL;
		if (tmp == tmp0)
			ptr = ptr0;
		else
			ptr = ptr1;
		
		if (tmp > cnt) {
			cnt = tmp;
			str = ptr;
		}
	}

	*(str + cnt) = '\0';
	return str;
}

/* lc0005 - longest palindromic substring (expand around center) */
char *longestPalindrome_ec(char *s)
{
	char *left  = s;
	int   cnt   = 1;
	
	for (int i = 0; s[i] != '\0'; i++) {
		int r   = i;
		int l   = i;
		int len = 0;
		while (l >= 0 && s[r] != '\0'
			&& s[l] == s[r]) {
			r++;
			l--;	
		}
		
		len = r - l - 1;
		if (len > cnt) {
			cnt = len;
			left = &s[l+1];
		}

		r = i + 1;
		l = i;
		while (l >= 0 && s[r] != '\0'
			&& s[l] == s[r]) {
			r++;
			l--;
		}

		len = r - l - 1;
		if (len > cnt) {
			cnt = len;
			left = &s[l+1];
		}
	}

	*(left + cnt) = '\0';
	return left;
}


/* lc0005 - longest palindromic substring (manacher failed) */
char *longestPalindrome(char *s)
{
	int len = strlen(s);
	if (len < 1)
		return NULL;
	char *str = (char *)malloc((2 * len + 2) * sizeof(char));
	str[2*len+1] = '\0';
	str[2*len]   = '#';
	for (int i = 0; s[i] != '\0'; i++) {
		str[1+2*i] = s[i];
		str[2*i] = '#';
	}

	char *left = str;
	int   max  = 1;
	for (int c = 1; str[c] != '\0'; c++) {		
		int l = c-1;
		int r = c+1;
		while (l >= 0 && str[r] != '\0' && str[l] == str[r]) {
			l--;
			r++;
		}
	
		int len = r - l - 1;
		if (len > max) {
			max  = len;
			left = &str[l+1];
		}
		
	}
	*(left + max) = '\0';
	char *rlt = (char *)malloc((max/2+1));
	int idx = 0;
	for (int i = 0; left[i] != '\0'; i++) {
		if (left[i] == '#')
			continue;
		
		rlt[idx++] = left[i];
	}

	rlt[idx] = '\0';
	return rlt;
}


/* lc0006 - zigzag conversion (brute force, super slow) */
char* convert(char *s, int n)
{
	if (n == 1)
		return s;
	int   len = strlen(s);
	char *rlt = (char *)malloc(len + 1);
	char  map[n][1000];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1000; j++)
			map[i][j] = '#';
	}
	int y = 0;
	int x = 0;
	int d = 1;
	for (int i = 0; i < len; i++) {
		map[y][x] = s[i];

		if (y == n-1)
			d = -1;
		if (y == 0)
			d = 1;
		
		if (d == 1) {
			y++;
		} else {
			x++;
			y--;
		}
	}
	
	int idx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1000; j++) {
			if (map[i][j] == '#') {
				continue;
			}
			rlt[idx++] = map[i][j];	
		}
	}

	rlt[idx] = '\0';
	return rlt; 
}
