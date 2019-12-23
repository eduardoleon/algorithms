#include <stdio.h>
#include <stdlib.h>

struct tree {
     int value;
     struct tree *left;
     struct tree *right;
};

struct stack {
     int state;
     struct tree *current;
     struct stack *next;
};

void push(int state, struct tree *tree, struct stack **stack)
{
     if (!tree) return;
     
     struct stack *new = malloc(sizeof (struct stack));
     new->state = state;
     new->current = tree;
     new->next = *stack;
     *stack = new;
}

void pop(struct tree **tree, struct stack **stack)
{
     struct stack *old = *stack;
     *tree = old->current;
     *stack = old->next;
     free(old);
}

void pop_inorder(struct tree **tree, struct stack **stack)
{
     while ((*stack)->state) {
          struct tree *tree;
          pop(&tree, stack);
          
          push(1, tree->right, stack);
          push(0, tree, stack);
          push(1, tree->left , stack);
     }
     
     pop(tree, stack);
}

void make_tree(struct tree *nodes, int bound)
{
     int half = bound / 2;
     
     for (int i = 1; i < half; i++) {
          nodes[i].left = &nodes[2*i];
          nodes[i].right = &nodes[2*i + 1];
     }
     
     for (int i = half; i < bound; i++) {
          nodes[i].left = NULL;
          nodes[i].right = NULL;
     }
}

void fill_tree(struct tree *tree, int start, int step)
{
     struct stack *stack = NULL;
     push(1, tree, &stack);
     
     while (stack) {
          pop_inorder(&tree, &stack);
          tree->value = start;
          start += step;
     }
}

void merge(struct tree *ltree, struct tree *rtree)
{
     struct stack *lstack = NULL;
     struct stack *rstack = NULL;
     push(1, ltree, &lstack);
     push(1, rtree, &rstack);
     
     while (lstack && rstack) {
          pop_inorder(&ltree, &lstack);
          pop_inorder(&rtree, &rstack);
          
          if (ltree->value <= rtree->value) {
               printf("%d ", ltree->value);
               push(0, rtree, &rstack);
          }
          else {
               printf("%d ", rtree->value);
               push(0, ltree, &lstack);
          }
     }
     
     while (lstack) {
          pop_inorder(&ltree, &lstack);
          printf("%d ", ltree->value);
     }
     
     while (rstack) {
          pop_inorder(&rtree, &rstack);
          printf("%d ", rtree->value);
     }
     
     printf("\n");
}

int main()
{
     struct tree left[72];
     struct tree right[54];
     
     make_tree(left, 72);
     make_tree(right, 54);
     
     fill_tree(&left[1], 2, 2);
     fill_tree(&right[1], 3, 2);
     
     merge(&left[1], &right[1]);
}
