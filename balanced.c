#include <stdio.h>
#include <stdlib.h>

struct tree {
     struct tree *left;
     struct tree *right;
};

struct stack {
     int state;
     struct tree *current;
     struct stack *next;
};

void create(struct stack **stack)
{
     *stack = NULL;
}

void push(int state, struct tree *tree, struct stack **stack)
{
     struct stack *new = malloc(sizeof (struct stack));
     new->state = state;
     new->current = tree;
     new->next = *stack;
     *stack = new;
}

int pop(int *state, struct tree **tree, struct stack **stack)
{
     struct stack *old = *stack;
     if (!old) return 0;
     if (state) *state = old->state;
     if (tree) *tree = old->current;
     
     *stack = old->next;
     free(old);
     return 1;
}

void destroy(struct stack **stack)
{
     while (pop(NULL, NULL, stack));
}

void make_tree(struct tree *nodes, int bound)
{
     int twice = 2 * bound;
     
     for (int i = 1; i < bound; i++) {
          nodes[i].left = &nodes[2*i];
          nodes[i].right = &nodes[2*i + 1];
     }
     
     for (int i = bound; i < twice; i++) {
          nodes[i].left = NULL;
          nodes[i].right = NULL;
     }
}

int balanced(struct tree *tree)
{
     int state;
     struct stack *schedule;
     struct stack *heights;
     
     create(&heights);
     create(&schedule);
     push(0, tree, &schedule);
     
     while (pop(&state, &tree, &schedule))
          if (state) {
               int m, n, p, q;
               pop(&m, NULL, &heights);
               pop(&n, NULL, &heights);
               p = (m < n) ? m : n;
               q = (m > n) ? m : n;
               
               if (q - p > 1) {
                    destroy(&heights);
                    destroy(&schedule);
                    return 0;
               }
               
               push(q + 1, NULL, &heights);
          }
          else if (tree) {
               push(1, NULL, &schedule);
               push(0, tree->left, &schedule);
               push(0, tree->right, &schedule);
          }
          else
               push(0, NULL, &heights);
     
     return 1;
}

void test(struct tree *tree)
{
     if (balanced(tree))
          printf("The tree is balanced.\n");
     else
          printf("The tree is not balanced.\n");
}

int main()
{
     struct tree small[16];
     struct tree large[64];
     struct tree unbal;
     
     make_tree(small, 8);
     make_tree(large, 32);
     
     unbal.left = &small[1];
     unbal.right = &large[1];
     
     test(unbal.left);
     test(unbal.right);
     test(&unbal);
}
