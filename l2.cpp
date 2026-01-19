/* leetcode l2 - add two numbers
 * Jan 19, 2026
 */

/* bf */
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
        ListNode d(0);
        ListNode *p = &d;
        int f = 0;

        while (l1 || l2 || f) {
                int s = f;
                
                if (l1)
                        s += l1->val;
                if (l2)
                        s += l2->val;

                f = s / 10;
                p->next = new ListNode(s % 10);
                p = p->next;

                if (l1)
                        l1 = l1->next;
                if (l2)
                        l2 = l2->next;
        }

        return d.next;
}

/* recursion */
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2, int f = 0)
{
        if (!l1 && !l2 && !f)
                return nullptr;

        int s = f;

        if (l1)
                s += l1->val;
        if (l2)
                s += l2->val;

        ListNode *n = new ListNode(s % 10);
        
        n->next = addTwoNumbers(
                l1 ? l1->next : nullptr,
                l2 ? l2->next : nullptr,
                s / 10
        );

        return n;
}
