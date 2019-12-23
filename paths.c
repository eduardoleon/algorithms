#include <stdio.h>
#include <stdlib.h>

struct tree {
     int          value;
     struct tree *left;
     struct tree *right;
};

struct stack {
     int           state;
     struct tree  *current;
     struct stack *next;
};

void create(struct stack **stack)
{
     *stack = NULL;
}

void push(int state, struct tree *tree, struct stack **stack)
{
     struct stack *new = malloc(sizeof (struct stack));
     new->state   = state;
     new->current = tree;
     new->next    = *stack;
     *stack       = new;
}

int pop(int *state, struct tree **tree, struct stack **stack)
{
     struct stack *old = *stack;
     if (!old)  return 0;
     if (state) *state = old->state;
     if (tree)  *tree  = old->current;
     
     *stack = old->next;
     free(old);
     return 1;
}

void print_path(struct stack *stack)
{
     struct tree  *tree;
     struct stack *aux;
     create(&aux);
     
     while (stack) {
          push(0, stack->current, &aux);
          stack = stack->next;
     }
     
     while (pop(NULL, &tree, &aux))
          printf("%d ", tree->value);
     
     printf("\n");
}

void find_paths(struct tree *tree, int sum)
{
     int           state;
     struct stack *stack;
     create(&stack);
     push(0, tree, &stack);
     
     while (pop(&state, &tree, &stack))
          if (tree)
               switch (state) {
                    case 0:
                         sum -= tree->value;
                         push(1, tree, &stack);
                         push(0, tree->left, &stack);
                         break;
                         
                    case 1:
                         push(2, tree, &stack);
                         push(0, tree->right, &stack);
                         break;
                         
                    case 2:
                         if (!tree->left && !tree->right && !sum) {
                              push(0, tree, &stack);
                              print_path(stack);
                              pop(NULL, NULL, &stack);
                         }
                         sum += tree->value;
                         break;
               }
}

int main()
{
     struct tree nodes[64];
     
     for (int i = 1; i < 32; i++) {
          nodes[i].value = i % 2;
          nodes[i].left  = &nodes[2*i];
          nodes[i].right = &nodes[2*i + 1];
     }
     
     for (int i = 32; i < 64; i++) {
          nodes[i].value = i % 2;
          nodes[i].left  = NULL;
          nodes[i].right = NULL;
     }
     
     find_paths(&nodes[1], 3);
}
