/* Nov 23, 2025:
 *	"I've been very busy with other things, so I haven't done any leetcode
 *	problems for almost two weeks.
 *	
 *	Also, my girl friend used to study with me, But since she stopped,
 *	I've lost my drive..."
 *
 */


/* 0019 - remove nth node from end of list
 *      - from https://github.com/qianjunfan
 */
struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
	struct ListNode  dummy = {0, head};
	struct ListNode *tmp   = head;
	struct ListNode *map[31];
	int cnt = 0;

	while (tmp != NULL) {
		map[cnt + 1] = tmp;
		cnt++;
		tmp = tmp->next;
	}

	map[cnt - n]->next = map[cnt - n]->next->next;

	return dummy.next;
}


/* 0022 - generate parentheses
 *	- from https://github.com/qianjunfan
 */

char **resize_result(char **result, int *capa)
{
	*capa *= 2;
	result = (char **)realloc(result, *capa * sizeof(char *));
	return result;
}

void backtrack(char ***result, int *cnt, int *capa, char *cur,
		int idx, int open_cnt, int close_cnt, int n)
{
	if (idx == 2 * n) {
		if (*cnt == *capa)
			*result = resize_result(*result, capa);
		
		(*result)[*cnt] = (char *)malloc((2 * n + 1) * sizeof(char));
		strcpy((*result)[*cnt], cur);
		(*cnt)++;
		return;
	}

	if (open_cnt < n) {
		cur[idx] = '(';
		backtrack(result, cnt, capa, cur, idx + 1, open_cnt + 1,
				close_cnt, n);
	}

	if (close_cnt < open_cnt) {
		cur[idx] = ')';
		backtrack(result, cnt, capa, cur, idx + 1, open_cnt,
				close_cnt + 1, n);

	}
}

char **generateParenthesis(int n, int *return_size)
{
	if (n < 1) {
		*return_size = 0;
		return NULL;
	}

	int capa = 8;

	char **result = (char **)malloc(capa * sizeof(char *));
	*return_size  = 0;
	
	char *cur_buf = (char *)malloc((2 * n + 1) * sizeof(char));
	cur_buf[2 * n] = '\0';
	backtrack(&result, return_size, &capa, cur_buf, 0, 0, 0, n);
	free(cur_buf);

	return result;
}
