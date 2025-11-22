/*
 */

/* 0100 - same tree (review)
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

bool isSameTree_r(struct TreeNode *q, struct TreeNode *p)
{
        if (q == NULL && p == NULL)
                return true;
        
        if ((q != NULL && p == NULL) || (q == NULL && p != NULL))
                return false;

        if (q->val != p->val)
                return false;
        
        return (isSameTree_r(q->left, p->left) && isSameTree_r(q->right, p->right));
}


/* 0100 - same tree (no recursion, and it's extremely slow)
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>
#include <stdbool.h>

struct pair {
        struct TreeNode *p;
        struct TreeNode *q;
};

struct stack {
        struct pair *array;
        int capa;
        int top;
};

struct stack *create(int capa)
{
        struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
        stack->capa  = capa;
        stack->top   = -1;
        stack->array = (struct pair *)malloc(capa * sizeof(struct pair));

        return stack;
}

bool is_empty(struct stack *stack) {
        return stack->top == -1;
}

void push(struct stack *stack, struct TreeNode *p, struct TreeNode *q)
{
        if (stack->top < stack->capa - 1) {
                stack->array[++stack->top].p = p;
                stack->array[stack->top].q   = q;
        }
}


struct pair pop(struct stack *stack)
{
        struct pair pair = {NULL, NULL};
        if (!is_empty(stack))
                pair = stack->array[stack->top--];
        
        return pair;
}

bool isSameTree_nr(struct TreeNode *q, struct TreeNode *p)
{
        struct stack *stack = create(20000);

        push(stack, p, q);

        while (!is_empty(stack)) {
                struct pair cur = pop(stack);
                struct TreeNode *nq = cur.q;
                struct TreeNode *np = cur.p;

                if (nq == NULL && np == NULL)
                        continue;

                if (nq == NULL || np == NULL) 
                        goto is_false;

                if (nq->val != np->val)
                        goto is_false;

                push(stack, nq->right, np->right);
                push(stack, nq->left,  np->left);
        }

is_true:
        free(stack->array);
        free(stack);
        return true;

is_false:
        free(stack->array);
        free(stack);
        return false;
}


/* 0101 - symmetric tree (review)
 *      - from https://github.com/qianjunfan
 */

#include <stdlib.h>
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

bool isSymmetric(struct TreeNode *r) 
{
        if (r == NULL)
                return true;

        return recursion(r->left, r->right);
}


/* 0104 - maximum depth of binary tree (review)
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
