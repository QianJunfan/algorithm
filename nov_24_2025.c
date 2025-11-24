/* Nov 24, 2025
 *	"I need to push my self to solve more problems, even though the time
 *	 I can dedicate to coding each day is very limited.
 *
 *	 And I found my self having a tendency to solve those problems that
 *	 should be solved with much simpler logical algorithms, making my code
 *	 overly bloated. (which I need to correct)
 *
 *	 Oh, what's more, my girlfriend has started practicing coding problems
 *	 with me again."
 *
 */

/* 0019 - remove nth node from end of list (review)
 *      - from https://github.com/qianjunfan
 */

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
	struct ListNode  dummy = {0, head};
	struct ListNode *tmp   = head;   
	struct ListNode *map[31];

	int cnt = 0
	map[0] = &dummy;
	while (tmp != NULL) {
		map[++cnt] = tmp;
		tmp = tmp->next;
	}

	map[cnt-n]->next = map[cnt-n]->next->next;

	return dummy.next;
}


/* 0024 - swap nodes in pairs (cumbersome)
 *	- from https://github.com/qianjunfan
 */

void gen_arr(int *arr, int size)
{
        for (int i = 0; i < size; i++) {
                if (i % 2 == 0)
                        arr[i] = i + 1;
                else
                        arr[i] = i - 1;
        }
}

struct ListNode *swapPairs(struct ListNode *head)
{
        struct ListNode *map[101] = {NULL};
        int arr[101];
        gen_arr(arr, 101);
        int idx = 0;
        int max_map_idx = 0;
        while (head != NULL && idx < 101) {
                int new_idx = arr[idx];

                if (new_idx >= 101)
                        new_idx = idx;

                map[new_idx] = head;
                if (new_idx > max_map_idx)
                        max_map_idx = new_idx;

                head = head->next;
                idx++;
        }

        if (idx == 0)
                return NULL;

        if (idx == 1) {
                if (map[1] != NULL)
                        map[1]->next = NULL;
                return map[1];
        }

        int i = 0;
        while (i < max_map_idx) {
                int j = i + 1;
                while (j <= max_map_idx && map[j] == NULL) {
                        j++;
                }

                if (j <= max_map_idx) {
                        map[i]->next = map[j];
                        i = j;
		} else {
                        map[i]->next = NULL;
                        break;
                }
        }

        if (i == max_map_idx && map[i] != NULL) {
                map[i]->next = NULL;
        }


        return map[0];
}


/* 0024 - swap nodes in pairs (iterative swapping / simple and neet)
 *	- from https://github.com/qianjunfan
 */

struct ListNode *swapPairs(struct ListNode *head)
{
	struct ListNode dummy;
	dummy.next = head;
	struct ListNode *prev = &dummy;

	while (prev->next != NULL && prev->next->next != NULL) {
		struct ListNode *n1 = prev->next;
		struct ListNode *n2 = prev->next->next;

		prev->next = n2;
		n1->next = n2->next;
		n2->next = n1;
		prev = n1;
	}


	return dummy.next;
}



/* 0118 - pascals triangle
 * 	- from https://github.com/qianjunfan
 */

void make(int *above, int *cur, int cur_size)
{
	cur[0] = 1;
	cur[cur_size - 1] = 1;
	
	for (int i = 1; i < cur_size - 1; i++)
		cur[i] = above[i-1] + above[i];
}

int **generate(int num_rows, int *return_size, int **return_col_sizes)
{
	if (num_rows == 0) {
		*return_size = 0;
		*return_col_sizes = NULL;
		return NULL;
	}
	int result  = (int **)malloc(sizeof(int *) * n);
	*col = (int *)malloc(sizeof(int) * n);
	(*col)[0] = 1;
	result[0] = (int *)malloc(sizeof(int) * 1)
	result[0][0] = 1;
	if (n == 1)
		return result;

	for(int i = 1; i < n, i++) {
		result[i] = (int *)malloc(sizeof(int) * (i + 1));
		result[i][0] = 1;
		result[i][i] = 1;
		*col[i] = i + 1;
		

	}
}
	
	*return_size = num_rows;
	*return_col_sizes = (int *)malloc(num_rows * sizeof(int));
	int **result = (int **)malloc(num_rows * sizeof(int *));

	for (int i = 0; i < num_rows; i++) {
		int cur_row_size = i + 1;
		(*return_col_sizes)[i] = cur_row_size;
		result[i] = (int *)malloc(cur_row_size * sizeof(int));

		if (i == 0)
			result[0][0] = 1;
		else
			make(result[i-1], result[i], cur_row_size);
	}

	return result;
}
