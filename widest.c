#include <stdio.h>
#include <stdlib.h>

struct tree {
     struct tree *left;
     struct tree *right;
};

struct stack {
     struct tree *current;
     struct stack *next;
};

void push(struct tree *tree, struct stack **stack)
{
     if (!tree) return;
     
     struct stack *new = malloc(sizeof (struct stack));
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

void widest_1(int *depth, int *width, struct tree *tree)
{
     struct stack *current = NULL;
     struct stack *next = NULL;
     push(tree, &current);
     
     *depth = 0;
     *width = 0;
     
     for (int level = 0; current; level++) {
          int count = 0;
          
          while (current) {
               pop(&tree, &current);
               push(tree->left, &next);
               push(tree->right, &next);
               count++;
          }
          
          if (count > *width) {
               *depth = level;
               *width = count;
          }
          
          current = next;
          next = NULL;
     }
}

void widest_2(int *depth, int *width, struct tree *tree)
{
     struct stack *current = NULL;
     struct stack *next = NULL;
     push(tree, &current);
     
     *depth = 0;
     *width = 0;
     
     for (int level = 0; current; level++) {
          int count = 0;
          
          while (current) {
               pop(&tree, &current);
               push(tree->left, &current);
               push(tree->right, &next);
               count++;
          }
          
          if (count > *width) {
               *depth = level;
               *width = count;
          }
          
          current = next;
          next = NULL;
     }
}

int main()
{
     struct tree nodes[72];
     int depth, width;
     
     for (int i = 1; i < 36; i++) {
          nodes[i].left = &nodes[2 * i];
          nodes[i].right = &nodes[2 * i + 1];
     }
     
     for (int i = 36; i < 72; i++) {
          nodes[i].left = NULL;
          nodes[i].right = NULL;
     }
     
     widest_1(&depth, &width, &nodes[1]);
     printf("Level %d is the widest, with %d elements.\n", depth, width);
     
     widest_2(&depth, &width, &nodes[1]);
     printf("Level %d is the widest, with %d elements.\n", depth, width);
}
