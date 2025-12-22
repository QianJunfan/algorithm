/* Solve Problems & Study Algorithms
 * Dec 22, 2025
 */

/* $ LeetCode 0071 $ simplify path (in-place two-pointer) */
#include <string.h>
#include <stdlib.h>

char *simplifyPath(char *path)
{
	int l = strlen(path);
	char *s = malloc((l + 1) * sizeof(char));
	int c = 0;
	int i = 0;

	while (i < l) {
		while (i < l && path[i] == '/')
			i++;

		int start = i;

		while (i < l && path[i] != '/')
			i++;

		int len = i - start;

		if (len == 0)
			continue;

		if (len == 1 && path[start] == '.') {
			// do nothing
		} else if (len == 2 && path[start] == '.' 
			   && path[start+1] == '.') {
			if (c > 0) {
				c--;
				while (c > 0 && s[c] != '/')
					c--;
			}
		} else {
			s[c++] = '/';
			memcpy(&s[c], &path[start], len);
			c += len;
		}
	}

	if (c == 0)
		s[c++] = '/';

	s[c] = '\0';

	return s;
};



/* $ LeetCode 0071 $ simplify path (stack) */
#include <string.h>
#include <stdlib.h>

char *simplifyPath(char *path)
{
	int  n = strlen(path);
	int  t = 0;
	char **st = malloc(sizeof(char *) * n);
	
	char *s = strtok(path, "/");
	while (s != NULL) {
		if (!strcmp(s, "..")) {
			if (t > 0)
				t--;
		} else if (!strcmp(s, ".")) {
			// do nothing
		} else {
			st[t++] =s;
		}
		s = strtok(NULL, "/");
	}

	char *r = malloc(n + 1);

	if (t == 0) {
		strcpy(r, "/");
	} else {
		char *cur = r;
		for (int i = 0; i < t; i++) {
			*cur++ = '/';
			int l = strlen(st[i]);
			memcpy(cur, st[i], l);
			cur += l;
		}
		*cur = '\0';
	}
	free(st);

	return r;
}



