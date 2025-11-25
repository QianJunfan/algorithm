/* Nov 25, 2025
 */

/* 0019 - remove nth node from end of list (review)
 *      - from https://github.com/qianjunfan
 */
#include <stdlib.h>

struct ListNode *removeNthFromEnd(struct ListNode* head, int n)
{
	struct ListNode dummy = {0, head};
	struct ListNode *tmp  = head;
	struct ListNode *map[31];

	map[0]  = &dummy;
	unsigned int cnt = 0;

	while (tmp != NULL) {
		map[++cnt] = tmp;
		tmp = tmp->next;
	}

	map[cnt-n]->next = map[cnt-n]->next->next;
	free(map[cnt-n+1]);

	return dummy.next;
}


/* 0024 - swap nodes in pairs (review)
 *	- from https://github.com/qianjunfan
 */

struct ListNode *swapPairs(struct ListNode *head)
{
	struct ListNode dummy = {0, head};
	struct ListNode *prev = dummy;
	while (prev->next != NULL && prev->next->next != NULL) {
		struct ListNode *n1 = prev->next;
		struct ListNode *n2 = n1->next;
		
		prev->next = n2;
		n1->next = n2->next;
		n2->next = n1;
		prev = n1;	
	}
	
	return dummy.next;
}


/* 0118	- pascals triangle (review)
 * 	- from https://github.com/qianjunfan
 */

void make(int *above, int*cur, int cur_size)
{
	// {1, 3, 3, 1} -> cur_size = 4, cur[3]
	cur[0] = 1;
	cur[cur_size - 1] = 1;
	
	for (int i = 1; i < cur_size - 1; i++)
		cur[i] = above[i-1] + above[i];
}

int **generate(int n, int *size, int **col_sizes)
{
	*size = n;
	*col_sizes = (int *)malloc(n * sizeof(int));
	int **answ = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		answ[i] = (int *)malloc((i+1) * sizeof(int));
	
	for (int i = 0; i < n; i++) {
		int cur_size  = i + 1;
		(*col_sizes)[i] = cur_size;
		
		if (i == 0)
			answ[0][0] = 1;
		else
			make(answ[i-1], answ[i], cur_size);
	}

	return answ;
}


/* 0119 - pascals triangle ii
 *	- from https://github.com/qianjunfan
 */

void make(int *above, int*cur, int cur_size)
{
	// {1, 3, 3, 1} -> cur_size = 4, cur[3]
	cur[0] = 1;
	cur[cur_size - 1] = 1;
	
	for (int i = 1; i < cur_size - 1; i++)
		cur[i] = above[i-1] + above[i];
}

int *getRow(int n, int *size)
{
	*size = n+1;
	int **answ = (int **)malloc((n+1) * sizeof(int *));
	for (int i = 0; i < n + 1; i++)
		answ[i] = (int *)malloc((i+1) * sizeof(int));
	
	for (int i = 0; i < n + 1; i++) {
		int cur_size  = i + 1;
		
		if (i == 0)
			answ[0][0] = 1;
		else
			make(answ[i-1], answ[i], cur_size);
	}

	return answ[n];
r


/* 0136 - single number
 * 	- from https://github.com/qianjunfan
 */

#include <stdint.h>

int caloff(int num)
{	
	return num + 30000;
}

int singleNumber(int* nums, int size)
{
	uint8_t map[60001] = {0};

	for (int i = 0; i < size; i++)
		map[nums[i] + 30000] += 1;
	
	for (int i = 0; i < 60001; i++) {
		if (map[i] == 1)
			return (i-30000);
	}

	return 0;
}


/* 0121 - best time to buy and sell stock
 *	- from https://github.com/qianjunfan
 */

int maxProfit(int *p, int s)
{
	int cur        = 0;
	int max        = 0;
	int left       = p[0];
	
	for (int i = 1; i < s; i++) {
		if (left > p[i])
			left = p[i];
		else if (left <= p[i])
			cur = p[i] - left;

		if (cur > max)
			max = cur;
	}

	return max;
}

/* 0141 - linked list cycle
 *	- from https://github.com/qianjunfan
 */

bool hasCycle(struct ListNode *head)
{
	struct ListNode *fast = head;
	struct ListNode *slow = head;
	
	while (fast != NULL) {
        	if (fast->next == NULL)
            		return false;
		
		fast = fast->next->next;
		slow = slow->next;

		if (fast == slow)
			return true;
	}
	
	return false;
}



/* 0141 - linked list cycle (hash)
 *	- from https://github.com/qianjunfan
 */

struct hashTable {
	struct ListNode* key;
    	UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(struct ListNode* ikey)
{
   	struct hashTable* tmp;
    	HASH_FIND_PTR(hashtable, &ikey, tmp);
    	return tmp;
}

void insert(struct ListNode* ikey)
{
    	struct hashTable* tmp = malloc(sizeof(struct hashTable));
    	tmp->key = ikey;
    	HASH_ADD_PTR(hashtable, key, tmp);
}

bool hasCycle(struct ListNode* head)
{
    	hashtable = NULL;
    	while (head != NULL) {
        	if (find(head) != NULL)
            	return true;

        insert(head);
        head = head->next;
    	}
    	return false;
}

