#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct tree {
     int value;
     struct tree *left;
     struct tree *right;
};

struct stack {
     int depth;
     struct tree *tree;
     struct stack *next;
};

struct tree *node(int value)
{
     struct tree *tree = malloc(sizeof (struct tree));
     tree->value = value;
     tree->left = NULL;
     tree->right = NULL;
     return tree;
}

void push(int depth, struct tree *tree, struct stack **stack)
{
     struct stack *new = malloc(sizeof (struct stack));
     new->depth = depth;
     new->tree = tree;
     new->next = *stack;
     *stack = new;
}

void pop(int *depth, struct tree **tree, struct stack **stack)
{
     struct stack *old = *stack;
     if (depth) *depth = old->depth;
     if (tree) *tree = old->tree;
     *stack = old->next;
     free(old);
}

struct tree *restore(int count, int *values)
{
     struct tree fake = { .value = INT_MAX };
     struct tree *tree = &fake;
     struct stack *stack = NULL;
     
     for (int i = 0; i < count; i++)
          if (values[i] < tree->value) {
               push(0, tree, &stack);
               tree = tree->left = node(values[i]);
          }
          else {
               while (values[i] > stack->tree->value)
                    pop(NULL, &tree, &stack);
               tree = tree->right = node(values[i]);
          }
     
     return fake.left;
}

int pretty(struct tree *tree)
{
     struct stack *stack = NULL;
     int depth;
     push(0, tree, &stack);
     
     while (stack) {
          pop(&depth, &tree, &stack);
          
          if (depth) {
               int count = depth;
               while (--count)
                    printf("| ");
               printf("|-");
          }
          
          if (tree) {
               printf("%d\n", tree->value);
               push(depth + 1, tree->right, &stack);
               push(depth + 1, tree->left, &stack);
               free(tree);
          }
          else
               printf("NULL\n");
     }
}

int main()
{
     //int values[] = {3,2,1,5,4,6};
     int values[] = {10, 9, 8, 6, 5, 7, 13, 11, 12, 14, 15, 16};
     int count = sizeof (values) / sizeof (int);
     struct tree *tree = restore(count, values);
     pretty(tree);
}
