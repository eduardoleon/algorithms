#include <stdio.h>
#include <stdlib.h>

struct node {
     int          value;
     struct node *next;
};

struct queue {
     struct node *first;
     struct node *last;
};

void create(struct queue *queue)
{
     queue->first = NULL;
     queue->last  = NULL;
}

void enqueue(struct queue *queue, int value)
{
     struct node *node = malloc(sizeof (struct node));
     node->value = value;
     node->next  = NULL;
     
     if (queue->last)
          queue->last = queue->last->next = node;
     else
          queue->last = queue->first = node;
}

int dequeue(struct queue *queue)
{
     struct node *node  = queue->first;
     int          value = node->value;
     
     queue->first = queue->first->next;
     queue->last  = queue->first ? queue->last : NULL;
     free(node);
     return value;
}

void sort_two(int *min, int *max)
{
     if (*min > *max) {
          int aux = *min;
          *min = *max;
          *max = aux;
     }
}

int extract_min(struct queue *queue, int size)
{
     int min = dequeue(queue);
     
     while (--size) {
          int max = dequeue(queue);
          sort_two(&min, &max);
          enqueue(queue, max);
     }
     
     return min;
}

void sort_queue(struct queue *queue, int size)
{
     struct queue output;
     create(&output);
     
     while (size) {
          int value = extract_min(queue, size--);
          enqueue(&output, value);
     }
     
     *queue = output;
}

void print_queue(struct queue *queue, int size)
{
     while (--size) {
          int value = dequeue(queue);
          printf("%d <- ", value);
          enqueue(queue, value);
     }
     
     int value = dequeue(queue);
     printf("%d\n", value);
     enqueue(queue, value);
}

int main()
{
     struct queue queue;
     create(&queue);
     
     enqueue(&queue, 5);
     enqueue(&queue, 1);
     enqueue(&queue, 8);
     enqueue(&queue, 4);
     enqueue(&queue, 3);
     enqueue(&queue, 6);
     enqueue(&queue, 2);
     enqueue(&queue, 9);
     
     sort_queue(&queue, 8);
     print_queue(&queue, 8);
}
