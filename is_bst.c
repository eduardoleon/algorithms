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
     struct stack *new = malloc(sizeof (struct stack));
     new->state = state;
     new->current = tree;
     new->next = *stack;
     *stack = new;
}

void pop(int *state, struct tree **tree, struct stack **stack)
{
     struct stack *old = *stack;
     *state = old->state;
     *tree = old->current;
     *stack = old->next;
     free(old);
}

void destroy(struct stack *stack)
{
     while (stack) {
          struct stack *next = stack->next;
          free(stack);
          stack = next;
     }
}

int is_bst(struct tree *tree, int bound)
{
     struct stack *stack = NULL;
     push(0, tree, &stack);
     
     while (stack) {
          int state;
          pop(&state, &tree, &stack);
          
          if (!tree)
               ;
          else if (!state) {
               push(1, tree, &stack);
               push(0, tree->left, &stack);
          }
          else if (bound < tree->value) {
               push(0, tree->right, &stack);
               bound = tree->value;
          }
          else {
               destroy(stack);
               return 0;
          }
     }
     
     return 1;
}

int main()
{
     struct tree nodes[64];
     
     for (int i = 1; i < 32; i++) {
          nodes[i].value = i;
          nodes[i].left = &nodes[2*i];
          nodes[i].right = &nodes[2*i + 1];
     }
     
     for (int i = 32; i < 64; i++) {
          nodes[i].value = i;
          nodes[i].left = NULL;
          nodes[i].right = NULL;
     }
     
     if (is_bst(&nodes[1], 0))
          printf("We have a well-formed BST.\n");
     else
          printf("We have a non-well-formed BST.\n");
}
