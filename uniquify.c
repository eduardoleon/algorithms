#include <stdio.h>

struct node {
     int          value;
     struct node *next;
};

void uniquify_head(struct node *head)
{
     struct node *node = head;
     while (node->next)
          if (node->next->value == head->value)
               node->next = node->next->next;
          else
               node = node->next;     
}

void uniquify_list(struct node *head)
{
     while (head) {
          uniquify_head(head);
          head = head->next;
     }
}

void print_nodes(struct node *head)
{
     while (head) {
          printf("%d -> ", head->value);
          head = head->next;
     }
     
     printf("NULL\n");
}

int main()
{
     struct node nodes[7];
     
     nodes[0].value = 12;
     nodes[1].value = 11;
     nodes[2].value = 12;
     nodes[3].value = 21;
     nodes[4].value = 41;
     nodes[5].value = 43;
     nodes[6].value = 21;
     
     nodes[0].next = &nodes[1];
     nodes[1].next = &nodes[2];
     nodes[2].next = &nodes[3];
     nodes[3].next = &nodes[4];
     nodes[4].next = &nodes[5];
     nodes[5].next = &nodes[6];
     nodes[6].next = NULL;
     
     uniquify_list(nodes);
     print_nodes(nodes);
}
