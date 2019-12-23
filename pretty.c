struct tree {
     int value;
     struct tree *left;
     struct tree *right;
};

struct stack {
     struct tree *current;
     struct stack *next;
};


void push(struct tree *tree, struct stack **stack)
{
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

void transfer(struct stack *source, struct stack **target)
{
     while (source) {
          push(source->current, target);
          source = source->next;
     }
}

void pretty(struct tree *tree)
{
     
}
