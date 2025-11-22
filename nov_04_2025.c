/*
 */

/* 0058 - length of last word (forward iteration)
 *      - from https://github.com/qianjunfan 
 */

#include <string.h>

int lengthOfLastWord(char *s)
{
        int flag = 0;
        int cur  = 0;
        int pass = 0;
        for (int i = 0; i < strlen(s); i++) {
                char chr = s[i];
                if (chr == ' ') {
                        flag = 0;
                        pass = cur;
                        cur  = 0;
                        while (i + 1 < strlen(s) && s[i+1] == ' ')
                                i++;
                } else {
                        flag = 1;
                        cur += 1;
                }
        }

        if (flag == 0)
                return pass;
        else 
                return cur;
}


/* 0058 - length of last word (backward iteration)
 *      - from https://github.com/qianjunfan
 */

#include <string.h>

int lengthOfLastWord(char *s)
{
        int len  = 0;
        int i    = (int)strlen(s) - 1;
        while (i >= 0 && s[i] == ' ')
                i--;

        while (i >= 0) {
                if (s[i] != ' ')
                        len++;
                else
                        return len;
                i--;
        }


        return len;
}


/* 0028 - find the index of the first occurrence in a string (brute force)
 *      - from https://github.com/qianjunfan
 */

#include <string.h>

int strStr(char *str, char *target)
{
        int len = strlen(target);

        for (int i = 0; i < strlen(str); i++) {
                char cur = str[i];
                
                if (cur == target[0]) {
                        char tmp[len + 1];
                        strncpy(tmp, &str[i], len);
                        tmp[len] = '\0';

                        if (strcmp(tmp, target) == 0)
                                return i;
                }
        }

        return -1;
}


/* 0035 - search insert position (binary search)
 *      - from https://github.com/qianjunfan
 */

int searchInsert(int* nums, int size, int target)
{
        int l = 0;
        int r = size - 1;

        while (l <= r) {
                int mid = l + (r - l) / 2;
                if (nums[mid] == target)
                        return mid;
                else if (nums[mid] < target)
                        l = mid + 1;
                else if (nums[mid] > target)
                        r = mid - 1;
        }


        return l;
}

/* 0066 - plus one
 *      - from https://github.com/qianjunfan 
 */

int *plusOne(int *digits, int size, int *r_size)
{
        int *result = (int *)malloc((size + 1) * sizeof(int));
        *r_size     = 0;

        for (int i = size - 1; i >= 0; i--) {
                digits[i]++;

                if (digits[i] <= 9) {
                        *r_size = size;
                        return digits;
                }

                digits[i] = 0;
        }


        result[0] = 1;
        *r_size = size + 1;
        for (int i = 1; i < *r_size; i++)
                result[i] = 0;
        return result;
}

/* 0067 - add binary
 *      - from https://github.com/qianjunfan 
 */

#include <string.h>
#define MAX(x, y) ((x) < (y) ? (y) : (x))

char *addBinary(char *a, char *b)
{
        int len_a   = strlen(a);
        int len_b   = strlen(b);
        int max_len = MAX(len_a, len_b);
        int carry   = 0;
        char *result = (char *)malloc((max_len + 2) * sizeof(char));
        int k = max_len + 1;
        result[k--] = '\0';

        int i = len_a - 1;
        int j = len_b - 1;

        while (i >= 0 || j >= 0 || carry == 1) {
                int sum = carry;
                
                if (i >= 0)
                        sum += a[i--] - '0';
                if (j >= 0)
                        sum += b[j--] - '0';

                result[k--] = (sum % 2) + '0';
                carry = sum / 2;
        }

        return result + k + 1;
}



/* 0069 - sqrtx (brute force)
 *      - from https://github.com/qianjunfan
 */

int mySqrt(int x)
{
        if (x == 0)
                return 0;
        if (x == 1)
                return 1;

        for (long long i = 1; i <= x; i++) {
                long long sqrt = i * i;
                if (sqrt == x)
                        return i;
                else if (sqrt > x)
                        return i - 1;
        }

        return 1;
}



/* 0069 - sqrtx
 *      - from https://github.com/qianjunfan
 */

int mySqrt(int x)
{
        if (x == 0)
                return 0;

        if (x == 1)
                return 1;

        long long l   = 1;
        long long r   = x;
        long long ans = 1;
        while (l <= r) {
                long long mid = (l + r) / 2;
                long long cur = mid * mid;
                if (cur == x)
                        return (int)mid;

                if (cur < x) {
                        ans = mid;
                        l = mid + 1;
                }
                else if (cur > x) {
                        r = mid - 1;
                }

        }

        return (int)ans;

}


/* 0083 - remove duplicates from sorted list
 *      - from https://github.com/qianjunfan
 */

struct ListNode *deleteDuplicates(struct ListNode *head) 
{
        struct ListNode dummy;
        struct ListNode *cur = head;
        dummy.next = cur;
        while (cur != NULL) {
                if (cur->next != NULL && cur->val == cur->next->val) {
                        cur->next = cur->next->next;
                        continue;
            }
                cur = cur->next;
        }
        return dummy.next;
}


/* 0100 - same tree (recursion)
 *      - from https://github.com/qianjunfan
 */

#include <stdbool.h>

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
        if (p == NULL & q == NULL)
                return true;

        if (p == NULL || q == NULL || p->val != q->val)
                return false;
        
        return isSameTree(p->left,  q->left) &&
               isSameTree(p->right, q->right);
}


/* 0101 - symmetric tree
 *      - from https://github.com/qianjunfan
 */

#include <stdbool.h>

bool recursion(struct TreeNode *l, struct TreeNode *r)
{
        if (l == NULL & r == NULL)
                return true;

        if (l == NULL || r == NULL || l->val != r->val)
                return false;

        return recursion(l->left,  r->right) &&
               recursion(l->right, r->left);


}

bool isSymmetric(struct TreeNode *root) 
{
        if (root == NULL)
                return true;

        return recursion(root->left, root->right);
}


/* 0104 - maximum depth of binary tree (stupid)
 *      - from https://github.com/qianjunfan
 */

void rdepth(int *max, int cur, struct TreeNode *t)
{
        if (t == NULL)
                return;

        int new = cur + 1;
        if (new > (*max))
                *max = new;

        rdepth(max, new, t->left);
        rdepth(max, new, t->right);
}


int maxDepth(struct TreeNode *root) 
{
        if (root == NULL)
                return 0;
        int cur = 0;
        int max = 0;
        
        rdepth(&max, cur, root);

        return max;
}


/* 0104 - maximum depth of binary tree (better)
 *      - from https://github.com/qianjunfan
 */

#define MAX(x, y) ((x) < (y) ? (y) : (x))

int maxDepth(struct TreeNode *root)
{
        if (root == NULL)
                return 0;

        int l = maxDepth(root->left);
        int r = maxDepth(root->right);

        return 1 + MAX(l, r);
}


/* 0108 - convert sorted array to binary search tree
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>

struct TreeNode *build(int *nums, int l, int r)
{       
        if (l > r)
                return NULL;
        
        int mid = (l + r) / 2;
        struct TreeNode *cur = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        cur->val = nums[mid];
        

        cur->left  = build(nums,  l,   mid - 1);
        cur->right = build(nums, mid + 1, r);

        return cur;
}



struct TreeNode *sortedArrayToBST(int *nums, int size)
{
        return build(nums, 0, size-1);
}



/* 0111 - minimum depth of binary tree
 *      - from https://github.com/qianjunfan
 */

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int minDepth(struct TreeNode *root)
{
        if (root == NULL)
                return 0;
        
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        
        if (root->left == NULL && root->right == NULL)
                return 1;

        if (root->left == NULL)
                return 1 + r;

        if (root->right == NULL)
                return 1+ l;

        return 1 + MIN(l, r);
}


/* 0111 - minimum depth of binary tree (breadth-first search)
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};


typedef struct {
        struct TreeNode *node;
        int depth;
} QueueItem;


#define MAX_SIZE 10000

typedef struct {
        QueueItem items[MAX_SIZE];
        int front;
        int rear;
        int size;
} Queue;


void initQueue(Queue *q)
{
        q->front = 0;
        q->rear  = 0;
        q->size  = 0;
}


void enqueue(Queue *q, struct TreeNode *node, int depth)
{
        if (q->size >= MAX_SIZE)
                return;

        q->items[q->rear].node  = node;
        q->items[q->rear].depth = depth;
        q->rear = (q->rear + 1) % MAX_SIZE;
        q->size++;
}


QueueItem dequeue(Queue *q)
{
        if (q->size <= 0)
                return (QueueItem){NULL, 0};

        QueueItem item = q->items[q->front];
        q->front = (q->front + 1) % MAX_SIZE;
        q->size--;

        return item;
}

int isQueueEmpty(Queue *q) {
        return q->size == 0;
}


int minDepth(struct TreeNode *root) {
        if (root == NULL)
                return 0;

        Queue q;
        initQueue(&q);

        enqueue(&q, root, 1);

        while (!isQueueEmpty(&q)) {
                QueueItem current = dequeue(&q);
                struct TreeNode *node = current.node;
                int depth = current.depth;

                if (node->left == NULL && node->right == NULL)
                        return depth;

                if (node->left != NULL)
                        enqueue(&q, node->left, depth + 1);
                if (node->right != NULL)
                        enqueue(&q, node->right, depth + 1);
        }

        return 0;
}












