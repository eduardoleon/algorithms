#include <stdio.h>
#include <stdlib.h>

struct stack {
     int           state;
     void         *current;
     struct stack *next;
};

struct graph {
     int           value;
     int           state;
     struct stack *incoming;
     struct stack *outgoing;
};

void create(struct stack **stack)
{
     *stack = NULL;
}

void push(int state, void *value, struct stack **stack)
{
     struct stack *new = malloc(sizeof (struct stack));
     new->state   = state;
     new->current = value;
     new->next    = *stack;
     *stack       = new;
}

int pop(int *state, void **value, struct stack **stack)
{
     struct stack *old = *stack;
     if (!old)  return 0;
     if (state) *state = old->state;
     if (value) *value = old->current;
     
     *stack = old->next;
     free(old);
     return 1;
}

void destroy(struct stack **stack)
{
     while (pop(NULL, NULL, stack));
}

void connect(struct graph *source, struct graph *target)
{
     push(0, target, &source->outgoing);
     push(0, source, &target->incoming);
}

void paths(struct graph *nodes, int *offsets)
{
     int count, current;
     
     while (count = *offsets++)
          while (current = *offsets++, count--)
               connect(nodes + current, nodes + *offsets);
}

void visit(struct stack *neighbors, struct stack **visited)
{
     int           state;
     void         *current;
     struct graph *graph;
     struct stack *schedule;
     
     create(&schedule);
     push(0, neighbors, &schedule);
     
     while (pop(&state, &current, &schedule))
          if (!state && current) {
               neighbors = current;
               graph     = neighbors->current;
               push(0, neighbors->next, &schedule);
               
               if (!graph->state) {
                    graph->state = 1;
                    push(1, graph, &schedule);
                    push(0, graph->outgoing, &schedule);
               }
          }
          else if (state)
               push(0, current, visited);
}

void assign(struct stack *neighbors)
{
     struct graph *graph;
     struct stack *schedule;
     
     create(&schedule);
     push(0, neighbors, &schedule);
     
     while (pop(NULL, &neighbors, &schedule))
          if (neighbors) {
               graph = neighbors->current;
               push(0, neighbors->next, &schedule);
               
               if (graph->state) {
                    graph->state = 0;
                    push(0, graph->incoming, &schedule);
                    printf("%d ", graph->value);
               }
          }
}

void kosaraju(struct stack *neighbors)
{
     struct graph *graph;
     struct stack *visited;
     
     create(&visited);
     visit(neighbors, &visited);
     
     while (pop(NULL, &graph, &visited))
          if (graph->state) {
               graph->state = 0;
               assign(graph->incoming);
               printf("%d\n", graph->value);
          }
}

int main()
{
     struct graph graph[16];
     struct stack dummy = { 0, graph, NULL };
     
     int offsets[] = {
          6, 0, 1, 2, 0, 3, 4, 0,
          2, 1, 5, 7,
          6, 1, 9, 10, 11, 12, 9, 11,
          1, 2, 12,
          6, 3, 5, 6, 7, 8, 6, 15,
          4, 5, 13, 14, 13, 15,
          1, 8, 15,
          1, 10, 13,
          0
     };
     
     for (int i = 0; i < 16; i++) {
          graph[i].value = i;
          graph[i].state = 0;
          create(&graph[i].incoming);
          create(&graph[i].outgoing);
     }
     
     paths(graph, offsets);
     kosaraju(&dummy);
     
     for (int i = 0; i < 16; i++) {
          destroy(&graph[i].incoming);
          destroy(&graph[i].outgoing);
     }
}
