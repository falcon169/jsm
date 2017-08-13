#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ { int item; struct node_ *next; } node_t; 
typedef struct list_ { node_t *head; int num_nodes; } list_t; 

typedef enum err_ { ERR_SUCC = 0, ERR_NOMEM = -1, ERR_INVALID, } err_t;

err_t insert_list(list_t *list, int item)
{
   node_t *node;
   node = (node_t *)malloc(sizeof(node_t));
   if (!node) return ERR_NOMEM;
   list->num_nodes++;
   node->item = item;
   node->next = list->head;
   list->head = node;
   return ERR_SUCC;
}

err_t del_r(node_t **node, int item)
{
    node_t *temp;
    if (node == NULL || *node == NULL) 
        return ERR_INVALID;

    if ((*node)->item == item) {
         temp = *node;
         *node = temp->next;
         free(temp);
         return ERR_SUCC;
    }
    return del_r(&(*node)->next, item);
}

void prnt_list(list_t *list)
{
   node_t *node = list->head;
   printf ("Num of nodes is %d: in list is \n", list->num_nodes);
   while ( node != NULL) {
      printf("%d  ", node->item);
      node = node->next; 
   }; 
}
int main (int argc, char **argv)
{
   int num ; node_t *node, *n1;
   int del_num;
   list_t List;

    memset(&List, 0, sizeof(list_t));
    printf("\n\nNumber pls \n");
    scanf("%d", &num);
      
   while (num != 999) {
	 insert_list(&List, num);
	 printf("\nNumber pls \n");
	 scanf("%d", &num);
   }
   prnt_list(&List);


   while (List.head != NULL) {
	   printf("Enter number to be deleted");
	   scanf("%d", &del_num);
	   if (ERR_SUCC == del_r(&(List.head), del_num)) {
               List.num_nodes--;
           }

	   prnt_list(&List);
   }
   return 69;
}
